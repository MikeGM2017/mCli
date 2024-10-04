using System;
using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_Module_Check : Cli_Module
    {
        protected Cli_Modules Modules;

        protected Dictionary<string, string> Values_Map;

        protected Str_Filter Str_Filter;

        protected Str_Get_Without_Commas Str_Without_Commas;

        protected Cli_Output_CS Cli_Output;

        protected Ref_Boolean Cmd_Script_Stop;

        protected Ref_String Script_Command_Str;
        protected Ref_String Script_Label_Str;

        protected Do_Abstract Do_Command_Object;

        protected int Count_Total = 0;
        protected int Count_Passed = 0;
        protected int Count_Failed = 0;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_check_map,
            CMD_ID_check_map_print,
            CMD_ID_check_map_print_by_filter,
            CMD_ID_check_map_clear,

            CMD_ID_check_modules_by_filter_to_map,
            //CMD_ID_check_modules_by_filter_from_map,

            CMD_ID_print_str, // CMD_ID_check_print_str
            CMD_ID_println_str, // CMD_ID_check_println_str

            CMD_ID_check_label_str,
            CMD_ID_check_goto_label,

            CMD_ID_check_if_var_exists_command,
            CMD_ID_check_if_var_exists_command1_else_command2,

            CMD_ID_check_if_var_compare_int_command, // compare: == / != / ... / & / | / && / ||
            CMD_ID_check_if_var_compare_int_command1_else_command2, // compare: == / != / ... / & / | / && / ||

            CMD_ID_check_if_var_compare_str_command, // compare: == / != / ... str: .v / int / "str"
            CMD_ID_check_if_var_compare_str_command1_else_command2, // compare: == / != / ... str: .v / int / "str"

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        enum Local_Compare_Result
        {
            CMP_FALSE,
            CMP_TRUE,
            CMP_ERROR
        };

        public Cli_Module_Check(Cli_Modules modules, Dictionary<string, string> values_map,
                Str_Filter str_filter,
                Str_Get_Without_Commas str_without_commas,
                Cli_Output_CS cli_output,
                Ref_Boolean cmd_script_stop,
                Ref_String script_command_str, Ref_String script_label_str,
                Do_Abstract do_command_object) : base("Check")
        {

            Version = "0.06";

            Modules = modules;
            Values_Map = values_map;
            Str_Filter = str_filter;
            Str_Without_Commas = str_without_commas;
            Cli_Output = cli_output;
            Cmd_Script_Stop = cmd_script_stop;
            Script_Command_Str = script_command_str;
            Script_Label_Str = script_label_str;
            Do_Command_Object = do_command_object;

            // <editor-fold defaultstate="collapsed" desc="Decl: cmp_int_str/words, cmp_str_str/words">
            string cmp_int_str = "== != < > <= >= & | && ||";
            List<string> cmp_int_words = new List<string>();
            cmp_int_words.Add("==");
            cmp_int_words.Add("!=");
            cmp_int_words.Add("<");
            cmp_int_words.Add(">");
            cmp_int_words.Add("<=");
            cmp_int_words.Add(">=");
            cmp_int_words.Add("&");
            cmp_int_words.Add("|");
            cmp_int_words.Add("&&");
            cmp_int_words.Add("||");

            string cmp_str_str = "== != < > <= >=";
            List<string> cmp_str_words = new List<string>();
            cmp_str_words.Add("==");
            cmp_str_words.Add("!=");
            cmp_str_words.Add("<");
            cmp_str_words.Add(">");
            cmp_str_words.Add("<=");
            cmp_str_words.Add(">=");
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">
            {
                // check map
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_map);
                cmd.Text_Set("check map");
                cmd.Help_Set("print values from map (all values)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("map", "check map"));

                Cmd_Add(cmd);
            }
            {
                // check map print
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_map_print);
                cmd.Text_Set("check map print");
                cmd.Help_Set("print values from map (all values)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("map", "check map"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check map print"));

                Cmd_Add(cmd);
            }
            {
                // check map print <.var>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_map_print_by_filter);
                cmd.Text_Set("check map print <.var>");
                cmd.Help_Set("print values from map (by filter)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("map", "check map"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check map print"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var>", "var name (by filter)"));

                Cmd_Add(cmd);
            }
            {
                // check map clear
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_map_clear);
                cmd.Text_Set("check map clear");
                cmd.Help_Set("clear map");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("map", "check map"));
                cmd.Item_Add(new Cmd_Item_Word("clear", "clear map print"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">
            {
                // check modules <module_name> to map
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_modules_by_filter_to_map);
                cmd.Text_Set("check modules <module_name> to map");
                cmd.Help_Set("vars from modules (modules by filter) to map");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
                cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
                cmd.Item_Add(new Cmd_Item_Word("to", "modules to"));
                cmd.Item_Add(new Cmd_Item_Word("map", "modules to map"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Print Str">
            {
                // check print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_print_str);
                cmd.Text_Set("print <str>");
                cmd.Help_Set("print <str>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("print", "print"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str"));

                Cmd_Add(cmd);
            }
            {
                // check println str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_println_str);
                cmd.Text_Set("println <str>");
                cmd.Help_Set("print <str> with newline");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("println", "print with newline"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
            {
                // check label str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_label_str);
                cmd.Text_Set("check label <label>");
                cmd.Help_Set("create label <label> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("label", "create label"));
                cmd.Item_Add(new Cmd_Item_Str("<label>", "label"));

                Cmd_Add(cmd);
            }

            {
                // check goto label
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_goto_label);
                cmd.Text_Set("check goto <label>");
                cmd.Help_Set("goto <label> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label>", "label"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: var exists do command">
            {
                // check if var exists <command>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_exists_command);
                cmd.Text_Set("check if <.var> exists <command>");
                cmd.Help_Set("check var exists and do command <command>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
                cmd.Item_Add(new Cmd_Item_Str("<command>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if var exists <command1> else <command2>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_exists_command1_else_command2);
                cmd.Text_Set("check if <.var> exists <command1> else <command2>");
                cmd.Help_Set("check var exists and do command1 or do command2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
                cmd.Item_Add(new Cmd_Item_Str("<command1>", "command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Str("<command2>", "command2"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: var compare var/int/str do command">
            {
                // check if <.var1> compare <int> <command>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_compare_int_command);
                cmd.Text_Set("check if <.var1> <compare: " + cmp_int_str + " > <int> <command>");
                cmd.Help_Set("check var1 by int and do command <command>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var1>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + " >", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int>", "int"));
                cmd.Item_Add(new Cmd_Item_Str("<command>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if <.var1> compare <int> <command1> else <command2>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_compare_int_command1_else_command2);
                cmd.Text_Set("check if <.var1> <compare: " + cmp_int_str + " > <int> <command1>> else <command2>");
                cmd.Help_Set("check var1 by int and do command <command1> or do >command2>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var1>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + " >", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int>", "int"));
                cmd.Item_Add(new Cmd_Item_Str("<command1>", "do command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Str("<command2>", "do command2"));

                Cmd_Add(cmd);
            }
            {
                // check if var1 compare var2/int/str <command>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_compare_str_command);
                cmd.Text_Set("check if <.var1> <compare: " + cmp_str_str + " > var2/int/str <command>");
                cmd.Help_Set("check var1 by var2/int/str and do command <command>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var1>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "var2/int/str"));
                cmd.Item_Add(new Cmd_Item_Str("<command>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if var1 compare var2/int/str <command1> else <command2>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_var_compare_str_command1_else_command2);
                cmd.Text_Set("check if <.var1> <compare: " + cmp_str_str + " > var2/int/str <command1>> else <command2>");
                cmd.Help_Set("check var1 by var2/int/str and do command <command1> or do >command2>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name("<.var1>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "var2/int/str"));
                cmd.Item_Add(new Cmd_Item_Str("<command1>", "do command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Str("<command2>", "do command2"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

        }

        string Var_Name_Without_Point_Get(string s)
        {
            if (s.Length > 0 && s[0] == '.')
            {
                return s.Substring(1);
            }
            return s;
        }

        int Str_To_Int(string s)
        {
            int v = 0;
            Int32.TryParse(s, out v);
            return v;
        }

        string Int_To_Str(int v)
        {
            return v.ToString();
        }

        bool Char_Is_Digit(char c)
        {
            if (c >= '0' && c <= '9') return true;
            return false;
        }

        bool Char_Is_Digit_Or_Plus_Or_Minus(char c)
        {
            if (c >= '0' && c <= '9') return true;
            if (c == '+') return true;
            if (c == '-') return true;
            return false;
        }

        bool Str_Is_Int(string s)
        {
            if (s.Length == 0) return false; // Case: empty string is not digit
            for (int i = 0; i < s.Length; i++)
            {
                char c = s[i];
                if (i == 0)
                {
                    if (!Char_Is_Digit_Or_Plus_Or_Minus(c)) return false;
                }
                else
                {
                    if (!Char_Is_Digit(c)) return false;
                }
            }
            return true;
        }

        Local_Compare_Result Compare_Values_Str_Or_Int(string var_left_value, string s_compare, string var_right_value)
        {
            Local_Compare_Result cmp_res = Local_Compare_Result.CMP_ERROR;

            if (Str_Is_Int(var_left_value) && Str_Is_Int(var_right_value))
            {
                int var_left_value_int = Str_To_Int(Str_Without_Commas.Get(var_left_value));
                int var_right_value_int = Str_To_Int(Str_Without_Commas.Get(var_right_value));
                cmp_res = Compare_Values_Int(var_left_value_int, s_compare, var_right_value_int);
            }
            else
            {
                cmp_res = Compare_Values_Str(Str_Without_Commas.Get(var_left_value), s_compare, Str_Without_Commas.Get(var_right_value));
            }

            return cmp_res;
        }

        // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">

        bool check_map_print(string var_filter, Str_Filter str_filter)
        {
            if (Values_Map.Count > 0)
            {
                Cli_Output.Output_Str("Values Map:");
                Cli_Output.Output_NewLine();
                bool found = false;
                foreach (var item in Values_Map)
                {
                    if (str_filter.Is_Match(var_filter, item.Key))
                    {
                        Cli_Output.Output_Str(item.Key + " = " + item.Value);
                        Cli_Output.Output_NewLine();
                        found = true;
                    }
                }
                if (!found)
                {
                    Cli_Output.Output_Str(var_filter);
                    Cli_Output.Output_Str(" - Not Found");
                    Cli_Output.Output_NewLine();
                }
            }
            else
            {
                Cli_Output.Output_Str("Values Map is empty");
                Cli_Output.Output_NewLine();
            }

            return true;
        }

        bool check_map_clear()
        {
            if (Values_Map.Count > 0)
            {
                Values_Map.Clear();
                Cli_Output.Output_Str("Values Map cleared");
                Cli_Output.Output_NewLine();
            }
            else
            {
                Cli_Output.Output_Str("Values Map is empty");
                Cli_Output.Output_NewLine();
            }

            return true;
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

        bool check_modules_to_map(string module_filter, Str_Filter str_filter)
        {
            bool found = false;
            for (int module = 0; module < Modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = Modules.Get(module);
                if (module_ptr != null)
                {
                    string module_name = module_ptr.Name_Get();
                    string module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                    if (str_filter.Is_Match(module_filter, module_name)
                            || str_filter.Is_Match(module_filter, module_name_with_commas))
                    {
                        module_ptr.To_Map(Values_Map);
                        Cli_Output.Output_Str(module_name + " . Values Map");
                        Cli_Output.Output_NewLine();
                        found = true;
                    }
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(module_filter);
                Cli_Output.Output_Str(" - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Compare_Values: int/str">

        Local_Compare_Result Compare_Values_Int(int var_left_value_int, string s_compare, int var_right_value_int)
        {
            Local_Compare_Result cmp_res = Local_Compare_Result.CMP_FALSE;
            if (s_compare == "==")
            {
                if (var_left_value_int == var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "!=")
            {
                if (var_left_value_int != var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "<")
            {
                if (var_left_value_int < var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == ">")
            {
                if (var_left_value_int > var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "<=")
            {
                if (var_left_value_int <= var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == ">=")
            {
                if (var_left_value_int >= var_right_value_int) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "&")
            {
                if ((var_left_value_int & var_right_value_int) != 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "|")
            {
                if ((var_left_value_int | var_right_value_int) != 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "&&")
            {
                if (var_left_value_int != 0 && var_right_value_int != 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "||")
            {
                if (var_left_value_int != 0 || var_right_value_int != 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else
            {
                cmp_res = Local_Compare_Result.CMP_ERROR;
            }
            return cmp_res;
        }

        Local_Compare_Result Compare_Values_Str(string var_left_value, string s_compare, string var_right_value)
        {
            Local_Compare_Result cmp_res = Local_Compare_Result.CMP_FALSE;
            if (s_compare == "==")
            {
                if (var_left_value == var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "!=")
            {
                if (var_left_value != var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "<")
            {
                //if (var_left_value < var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                if (String.Compare(var_left_value, var_right_value, comparisonType: StringComparison.Ordinal) < 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == ">")
            {
                //if (var_left_value > var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                if (String.Compare(var_left_value, var_right_value, comparisonType: StringComparison.Ordinal) > 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == "<=")
            {
                //if (var_left_value <= var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                if (String.Compare(var_left_value, var_right_value, comparisonType: StringComparison.Ordinal) <= 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else if (s_compare == ">=")
            {
                //if (var_left_value >= var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                if (String.Compare(var_left_value, var_right_value, comparisonType: StringComparison.Ordinal) >= 0) cmp_res = Local_Compare_Result.CMP_TRUE;
            }
            else
            {
                cmp_res = Local_Compare_Result.CMP_ERROR;
            }
            return cmp_res;
        }

        // </editor-fold>

        bool Do_Script_From_File(string filename, bool is_no_history)
        {
            bool is_filename_spaces = false;
            //if (filename.find(' ') != std::string::npos) is_filename_spaces = true;
            //if (filename.find('\t') != std::string::npos) is_filename_spaces = true;
            if (filename.Contains(" ")) is_filename_spaces = true;
            if (filename.Contains("\t")) is_filename_spaces = true;
            if (is_filename_spaces)
            {
                Script_Command_Str.Value = "do script \"" + filename + "\"";
            }
            else
            {
                Script_Command_Str.Value = "do script " + filename;
            }
            if (is_no_history)
            {
                Script_Command_Str.Value += " no history";
            }
            Do_Command_Object.Do();
            return true;
        }

        bool Do_Command(string command)
        {
            Script_Command_Str.Value = command;
            Do_Command_Object.Do();
            return true;
        }

        bool Do_Label(string label)
        {
            //@Warning: Command "check goto <label>" - special case: is moves file position
            // no action
            return true;
        }

        bool Do_Goto_Label(string label)
        {
            //Script_Command_Str = "check goto " + label;
            Script_Label_Str.Value = label;
            return true;
        }

        // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">

        bool check_label(string label)
        {
            return Do_Label(label);
        }

        bool check_goto_label(string label)
        {
            return Do_Goto_Label(label);
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Print Str">

        bool check_print_str(string s, bool is_newline)
        {
            Cli_Output.Output_Str(Str_Without_Commas.Get(s));
            if (is_newline)
            {
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: var exists do command">

        bool check_var_exists_do_command(string var_left, string command1, bool is_command2, string command2, Str_Filter str_filter)
        {
            string var_left_value_old = "";
            bool found = Values_Map.TryGetValue(var_left, out var_left_value_old);
            if (found)
            {
                Do_Command(command1);
            }
            else
            {
                if (is_command2)
                {
                    Do_Command(command2);
                }
            }
            return true;
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: var compare var/int/str do command">

        bool check_var_by_str_do_command(String var_left, String s_compare, String var_right, String command1, bool is_command2, String command2)
        {
            string var_left_value = "";
            bool var_left_found = Values_Map.TryGetValue(var_left, out var_left_value);

            String var_right_value = "";
            bool var_right_found = false;
            if (var_right.Length > 0 && var_right[0] == '.')
            {
                var_right_found = Values_Map.TryGetValue(Var_Name_Without_Point_Get(var_right), out var_right_value);
            }
            else
            {
                var_right_value = var_right;
                var_right_found = true; // Case: var_right . int/str
            }

            if (var_left_found && var_right_found)
            {
                Local_Compare_Result cmp_res = Compare_Values_Str_Or_Int(var_left_value, s_compare, var_right_value);

                if (cmp_res == Local_Compare_Result.CMP_TRUE)
                {
                    Do_Command(command1);
                }
                else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_command2)
                {
                    Do_Command(command2);
                }
                else if (cmp_res == Local_Compare_Result.CMP_ERROR)
                {
                    Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                    Cli_Output.Output_NewLine();
                }

            }
            else
            {
                if (!var_left_found)
                {
                    Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                    Cli_Output.Output_NewLine();
                }
                if (!var_right_found)
                {
                    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                    Cli_Output.Output_NewLine();
                }
            }
            return true;
        }

        // </editor-fold>

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {

                // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">

                case Local_Cmd_ID.CMD_ID_check_map:
                case Local_Cmd_ID.CMD_ID_check_map_print:
                    if (is_debug) return true;
                    {
                        string var_filter = "*";
                        return check_map_print(var_filter, Str_Filter);
                    }
                case Local_Cmd_ID.CMD_ID_check_map_print_by_filter:
                    if (is_debug) return true;
                    {
                        string var_filter = cmd.Items[3].Value_Str;
                        return check_map_print(var_filter, Str_Filter);
                    }
                case Local_Cmd_ID.CMD_ID_check_map_clear:
                    if (is_debug) return true;
                    return check_map_clear();

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

                case Local_Cmd_ID.CMD_ID_check_modules_by_filter_to_map:
                    if (is_debug) return true;
                    {
                        string module_filter = cmd.Items[2].Value_Str;
                        return check_modules_to_map(module_filter, Str_Filter);
                    }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Print Str">
                case Local_Cmd_ID.CMD_ID_print_str:
                    if (is_debug) return true;
                    {
                        string str = cmd.Items[1].Value_Str;
                        bool is_newline;
                        return check_print_str(str, is_newline = false);
                    }
                case Local_Cmd_ID.CMD_ID_println_str:
                    if (is_debug) return true;
                    {
                        string str = cmd.Items[1].Value_Str;
                        bool is_newline;
                        return check_print_str(str, is_newline = true);
                    }
                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">

                case Local_Cmd_ID.CMD_ID_check_label_str:
                    if (is_debug) return true;
                    {
                        string label = cmd.Items[2].Value_Str;
                        return check_label(label);
                    }
                case Local_Cmd_ID.CMD_ID_check_goto_label:
                    if (is_debug) return true;
                    {
                        string label = cmd.Items[2].Value_Str;
                        return check_goto_label(label);
                    }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: var exists do command">

                case Local_Cmd_ID.CMD_ID_check_if_var_exists_command:
                    if (is_debug) return true;
                    {
                        string var_left = Var_Name_Without_Point_Get(cmd.Items[2].Value_Str);
                        string command1 = cmd.Items[4].Value_Str;
                        bool is_command2;
                        string command2 = "";
                        return check_var_exists_do_command(var_left, command1, is_command2 = false, command2, Str_Filter);
                    }
                case Local_Cmd_ID.CMD_ID_check_if_var_exists_command1_else_command2:
                    if (is_debug) return true;
                    {
                        string var_left = Var_Name_Without_Point_Get(cmd.Items[2].Value_Str);
                        string command1 = cmd.Items[4].Value_Str;
                        bool is_command2;
                        string command2 = cmd.Items[6].Value_Str;
                        return check_var_exists_do_command(var_left, command1, is_command2 = true, command2, Str_Filter);
                    }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: var compare var/int/str do command">

                case Local_Cmd_ID.CMD_ID_check_if_var_compare_int_command:
                case Local_Cmd_ID.CMD_ID_check_if_var_compare_str_command:
                    if (is_debug) return true;
                    {
                        string var_left = Var_Name_Without_Point_Get(cmd.Items[2].Value_Str);
                        string s_compare = cmd.Items[3].Value_Str;
                        string var_right_value = cmd.Items[4].Value_Str;
                        string command1 = cmd.Items[5].Value_Str;
                        bool is_command2;
                        string command2 = "";
                        return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
                    }
                case Local_Cmd_ID.CMD_ID_check_if_var_compare_int_command1_else_command2:
                case Local_Cmd_ID.CMD_ID_check_if_var_compare_str_command1_else_command2:
                    if (is_debug) return true;
                    {
                        string var_left = Var_Name_Without_Point_Get(cmd.Items[2].Value_Str);
                        string s_compare = cmd.Items[3].Value_Str;
                        string var_right_value = cmd.Items[4].Value_Str; //@Warning: Without Var_Name_Without_Point_Get(...) - may be .var/int/str
                        string command1 = cmd.Items[5].Value_Str;
                        bool is_command2;
                        string command2 = cmd.Items[7].Value_Str;
                        return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
                    }

                // </editor-fold>

                default:
                    return false; // Not Implemented

            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            string Prefix = "Check";
            values_map[Prefix + ".Count_Total"] = Count_Total.ToString();
            values_map[Prefix + ".Count_Passed"] = Count_Passed.ToString();
            values_map[Prefix + ".Count_Failed"] = Count_Failed.ToString();
        }

    }
}
