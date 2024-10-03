using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Vars : Cli_Module
    {
        protected Cli_Modules Modules;
        protected Dictionary<string, string> Values_Map;
        protected Str_Filter Str_Filter;
        protected Str_Get_Without_Commas Str_Without_Commas;
        protected Cli_Output_CS Cli_Output;

        protected char C_Single;
        protected char C_Multy;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_point_var_name,
            CMD_ID_point_var_name_assign_str,
            CMD_ID_point_var_name_assign_point_var_name,

            CMD_ID_point_var_name_inc,

            CMD_ID_point_var_name_add_str,
            CMD_ID_point_var_name_stradd_str,

            CMD_ID_point_var_name_delete,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Vars(Cli_Modules modules, Dictionary<string, string> values_map, Str_Filter str_filter,
                Str_Get_Without_Commas str_without_commas,
                Cli_Output_CS cli_output,
                char c_single = '?', char c_multy = '*') : base("Vars")
        {

            Version = "0.06";

            Modules = modules;
            Values_Map = values_map;
            Str_Filter = str_filter;
            Str_Without_Commas = str_without_commas;
            Cli_Output = cli_output;
            C_Single = c_single;
            C_Multy = c_multy;

            {
                // get
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name);
                cmd.Text_Set(".<var_name>");
                cmd.Help_Set("get <var_name> value (by filter, .* - get all vars)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name (by filter)", C_Single, C_Multy));
                Cmd_Add(cmd);
            }

            {
                // assign int @Attention: Must be before Local_Cmd_ID.CMD_ID_point_var_name_assign_str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_assign_point_var_name);
                cmd.Text_Set(".<var_name> = .<var2_name>");
                cmd.Help_Set("set <var_name> value of <var2_name>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var2_name>", "var2 name", C_Single, C_Multy));
                Cmd_Add(cmd);
            }
            {
                // assign str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_assign_str);
                cmd.Text_Set(".<var_name> = <str>");
                cmd.Help_Set("set <var_name> to <str>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "new value"));
                Cmd_Add(cmd);
            }

            {
                // inc @Attention: increment as integer only (string converted to "0")
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_inc);
                cmd.Text_Set(".<var_name> inc");
                cmd.Help_Set("increment <var_name>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("inc", "increment"));
                Cmd_Add(cmd);
            }

            {
                // .<var_name> add <str>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_add_str);
                cmd.Text_Set(".<var_name> add <str>");
                cmd.Help_Set("<var_name> add int/var/str");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("add", "add"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "value to add")); // <str> . .v/int/str
                Cmd_Add(cmd);
            }
            {
                // .<var_name> stradd <str>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_stradd_str);
                cmd.Text_Set(".<var_name> stradd <str>");
                cmd.Help_Set("<var_name> add var/str as str");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("stradd", "add as str")); // <str> . .v/str
                cmd.Item_Add(new Cmd_Item_Str("<str>", "value to add as str"));
                Cmd_Add(cmd);
            }

            {
                // delete
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_delete);
                cmd.Text_Set(".<var_name> delete");
                cmd.Help_Set("delete <var_name> (by filter, .* - delete all vars)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("delete", "delete (by filter)"));
                Cmd_Add(cmd);
            }

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
            if (c >= '0' && c <= '9')
            {
                return true;
            }
            return false;
        }

        bool Char_Is_Digit_Or_Plus_Or_Minus(char c)
        {
            if (c >= '0' && c <= '9')
            {
                return true;
            }
            if (c == '+')
            {
                return true;
            }
            if (c == '-')
            {
                return true;
            }
            return false;
        }

        bool Str_Is_Int(string s)
        {
            if (s.Length == 0)
            {
                return false; // Case: empty string is not digit
            }
            for (int i = 0; i < s.Length; i++)
            {
                char c = s[i];
                if (i == 0)
                {
                    if (!Char_Is_Digit_Or_Plus_Or_Minus(c))
                    {
                        return false;
                    }
                }
                else if (!Char_Is_Digit(c))
                {
                    return false;
                }
            }
            return true;
        }

        bool var_get(string point_var_name_str)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (Str_Filter.Is_Match(var_name, item_var_name))
                {
                    Cli_Output.Output_Str(item_var_name + " = \"" + item.Value + "\"");
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        KeyValuePair<string, string> Values_Map_Find_By_Var_Name(string var_name_arg)
        {
            foreach (var item in Values_Map)
            {
                string item_var_name = "." + item.Key;
                if (var_name_arg == item_var_name)
                {
                    return item;
                }
            }
            return new KeyValuePair<string, string>();
        }

        bool var_set_str(string point_var_name_str, string value_str)
        {
            string var_name = point_var_name_str.Substring(1);
            string value_str_without_commas = Str_Without_Commas.Get(value_str);
            Values_Map[var_name] = value_str_without_commas;
            Cli_Output.Output_Str(var_name + " = \"" + value_str_without_commas + "\"");
            Cli_Output.Output_NewLine();
            return true;
        }

        bool var_set_var(string point_var1_name_str, string point_var2_name_str)
        {
            KeyValuePair<string, string> item = Values_Map_Find_By_Var_Name(point_var2_name_str);
            if (item.Key != null)
            {
                string var1_name = point_var1_name_str.Substring(1);
                string var2_value = item.Value;
                Values_Map[var1_name] = var2_value;
                Cli_Output.Output_Str(var1_name + " = \"" + var2_value + "\"");
                Cli_Output.Output_NewLine();
            }
            else
            {
                Cli_Output.Output_Str(point_var2_name_str + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        bool var_inc(string point_var_name_str)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (var_name == item_var_name)
                {
                    int item_var_value_int_new = Str_To_Int(item.Value) + 1;
                    Values_Map[item_var_name] = Int_To_Str(item_var_value_int_new);
                    found = true;
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        bool var_add(string point_var_name_str, string add_str, bool is_try_add_int)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (var_name == item_var_name)
                {
                    string item_var_value_old = item.Value;
                    if (is_try_add_int && Str_Is_Int(item_var_value_old) && Str_Is_Int(Str_Without_Commas.Get(add_str)))
                    { // Case 1: VAR_INT add VALUE_INT
                        int item_var_value_int_old = Str_To_Int(item_var_value_old);
                        int add_value_int = Str_To_Int(Str_Without_Commas.Get(add_str));
                        int item_var_value_int_new = item_var_value_int_old + add_value_int;
                        Values_Map[var_name] = Int_To_Str(item_var_value_int_new);
                    }
                    else if (add_str.Length > 0 && add_str[0] == '.')
                    { // Case 2: VAR add VAR
                        KeyValuePair<string, string> item_right = Values_Map_Find_By_Var_Name(add_str);
                        if (item_right.Key != null)
                        {
                            string add_var_value = item_right.Value;
                            if (is_try_add_int && Str_Is_Int(item_var_value_old) && Str_Is_Int(add_var_value))
                            { // Case 2.1: VAR_INT add VAR_INT
                                int item_var_value_int_old = Str_To_Int(item_var_value_old);
                                int add_value_int = Str_To_Int(add_var_value);
                                int item_var_value_int_new = item_var_value_int_old + add_value_int;
                                Values_Map[var_name] = Int_To_Str(item_var_value_int_new);
                            }
                            else
                            { // Case 2.2: VAR add VAR as str
                                string item_var_value_new = item_var_value_old + add_var_value;
                                Values_Map[var_name] = item_var_value_new;
                            }
                        }
                        else
                        {
                            Cli_Output.Output_Str(add_str + " - Not Found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                    else
                    { // Case 3: VAR add STR
                        string item_var_value_new = item_var_value_old + Str_Without_Commas.Get(add_str);
                        Values_Map[var_name] = item_var_value_new;
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
                if (add_str.Length > 0 && add_str[0] == '.')
                {
                    KeyValuePair<string, string> item_right = Values_Map_Find_By_Var_Name(add_str.Substring(1));
                    if (item_right.Key == null)
                    {
                        Cli_Output.Output_Str(add_str + " - Not Found");
                        Cli_Output.Output_NewLine();
                    }
                }
            }
            return true;
        }

        bool var_delete(string point_var_name_str)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (Str_Filter.Is_Match(var_name, item_var_name))
                {
                    found = true;
                }
            }
            if (found)
            {
                Dictionary<string, string> map_new = new Dictionary<string, string>();
                foreach (var item in Values_Map)
                {
                    string item_var_name = item.Key;
                    if (!Str_Filter.Is_Match(var_name, item_var_name))
                    {
                        map_new.Add(item.Key, item.Value);
                    }
                }
                Values_Map.Clear();
                foreach (var item in map_new)
                {
                    Values_Map.Add(item.Key, item.Value);
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {

                case Local_Cmd_ID.CMD_ID_point_var_name:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_get(point_var_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_assign_str:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        string value_str = cmd.Items[2].Value_Str;
                        return var_set_str(point_var_name_str, value_str);
                    }
                case Local_Cmd_ID.CMD_ID_point_var_name_assign_point_var_name:
                    if (is_debug) return true;
                    {
                        string point_var1_name_str = cmd.Items[0].Value_Str;
                        string point_var2_name_str = cmd.Items[2].Value_Str;
                        return var_set_var(point_var1_name_str, point_var2_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_inc:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_inc(point_var_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_add_str:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        string add_str = cmd.Items[2].Value_Str;
                        bool is_try_add_int;
                        return var_add(point_var_name_str, add_str, is_try_add_int = true);
                    }
                case Local_Cmd_ID.CMD_ID_point_var_name_stradd_str:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        string add_str = cmd.Items[2].Value_Str;
                        bool is_try_add_int;
                        return var_add(point_var_name_str, add_str, is_try_add_int = false);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_delete:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_delete(point_var_name_str);
                    }

            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }

    }
}
