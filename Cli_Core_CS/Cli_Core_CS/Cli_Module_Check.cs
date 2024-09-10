using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Check : Cli_Module
    {
        protected Cli_Modules Modules;

        protected Dictionary<string, string> Values_Map;

        protected Str_Filter Str_Filter;

        protected Cli_Output_CS Cli_Output;

        protected Ref_Boolean Cmd_Script_Stop;

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

            CMD_ID_check_var_str_set_str_as_value,
            CMD_ID_check_var_str_set_str_as_value_force,
            CMD_ID_check_var_str_set_str_as_var,
            CMD_ID_check_var_str_set_str_as_var_force,
            CMD_ID_check_var_str_set_str_as_expr,
            CMD_ID_check_var_str_set_str_as_expr_force,

            CMD_ID_check_var_str_inc,

            CMD_ID_check_if_str_compare_int_print_str,
            CMD_ID_check_if_str_compare_int_print_str_else_print_str,
            CMD_ID_check_if_str_compare_int_inc_str,
            CMD_ID_check_if_str_compare_int_inc_str_else_inc_str,
            CMD_ID_check_if_str_compare_int_do_script_stop,
            CMD_ID_check_if_str_compare_int_do_script_filename,
            CMD_ID_check_if_str_compare_int_do_script_filename_no_history,

            CMD_ID_check_if_str_compare_str_as_value_print_str,
            CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str,
            CMD_ID_check_if_str_compare_str_as_value_inc_str,
            CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str,
            CMD_ID_check_if_str_compare_str_as_value_do_script_stop,
            CMD_ID_check_if_str_compare_str_as_value_do_script_filename,
            CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history,

            CMD_ID_check_if_str_compare_str_as_var_print_str,
            CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str,
            CMD_ID_check_if_str_compare_str_as_var_inc_str,
            CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str,
            CMD_ID_check_if_str_compare_str_as_var_do_script_stop,
            CMD_ID_check_if_str_compare_str_as_var_do_script_filename,
            CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history,

            CMD_ID_check_if_str_compare_int_do_command_str,
            CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str,
            CMD_ID_check_if_str_compare_str_as_value_do_command_str,
            CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str,
            CMD_ID_check_if_str_compare_str_as_var_do_command_str,
            CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str,

            CMD_ID_check_label_str,
            CMD_ID_check_goto_label,

            CMD_ID_check_if_str_compare_int_goto_str,
            CMD_ID_check_if_str_compare_int_goto_str_else_goto_str,
            CMD_ID_check_if_str_compare_str_as_value_goto_str,
            CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str,
            CMD_ID_check_if_str_compare_str_as_var_goto_str,
            CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str,

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
            Str_Filter str_filter, Cli_Output_CS cli_output,
            Ref_Boolean cmd_script_stop) : base("Check")
        {
            Modules = modules;
            Values_Map = values_map;
            Str_Filter = str_filter;
            Cli_Output = cli_output;
            Cmd_Script_Stop = cmd_script_stop;

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
            cmp_str_words.Add("&");
            cmp_str_words.Add("|");
            cmp_str_words.Add("&&");
            cmp_str_words.Add("||");
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
                // check map print <var_name>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_map_print_by_filter);
                cmd.Text_Set("check map print <var_name>");
                cmd.Help_Set("print values from map (by filter)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("map", "check map"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check map print"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name (by filter)"));

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

            // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">
            {
                // check var str set str as value
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_value);
                cmd.Text_Set("check var <var_name> set <value> as value");
                cmd.Help_Set("set var to value");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<value>", "var new value"));
                cmd.Item_Add(new Cmd_Item_Word("as", "new value as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "new value as value"));

                Cmd_Add(cmd);
            }
            {
                // check var str set str as value force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_value_force);
                cmd.Text_Set("check var <var_name> set <value> as value force");
                cmd.Help_Set("set var to value (or create new var)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<value>", "var new value"));
                cmd.Item_Add(new Cmd_Item_Word("as", "new value as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "new value as value"));
                cmd.Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

                Cmd_Add(cmd);
            }

            {
                // check var str set str as var
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_var);
                cmd.Text_Set("check var <var1_name> set <var2_name> as var");
                cmd.Help_Set("set var1 to value of var2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "new value as var2 value"));

                Cmd_Add(cmd);
            }
            {
                // check var str set str as var force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_var_force);
                cmd.Text_Set("check var <var1_name> set <var2_name> as var force");
                cmd.Help_Set("set var1 to value of var2 (or create new var)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "new value as var2 value"));
                cmd.Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

                Cmd_Add(cmd);
            }

            {
                // check var str set str as expr
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_expr);
                cmd.Text_Set("check var <var_name> set <str> as expr");
                cmd.Help_Set("set var to value of expr (or create new var)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "expr"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("expr", "new value as expression value"));

                Cmd_Add(cmd);
            }
            {
                // check var str set str as expr force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_set_str_as_expr_force);
                cmd.Text_Set("check var <var_name> set <str> as expr force");
                cmd.Help_Set("set var to value of expr (or create new var)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("set", "var set"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "expr"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("expr", "new value as expression value"));
                cmd.Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Var: inc">
            {
                // check var str inc
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_var_str_inc);
                cmd.Text_Set("check var <var_name> inc");
                cmd.Help_Set("increment var value");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("var", "check var"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "increment var value"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: int print/inc/do script/do command">
            {
                // check if str compare INT print str // @Attention: Must be before check if str compare STR print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_print_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> print <msg>");
                cmd.Help_Set("check var by int and print msg");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare INT print str else print str // @Attention: Must be before check if str compare STR print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_print_str_else_print_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> print <msg1> else print <msg2>");
                cmd.Help_Set("check var by int and print msg1 or msg2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("print", "else print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare INT inc str // @Attention: Must be before check if str compare STR inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_int_str + "> <int_value> inc <var2_name>");
                cmd.Help_Set("check var1 by int and increment var2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare INT inc str else inc str // @Attention: Must be before check if str compare STR inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_inc_str_else_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_int_str + "> <int_value> inc <var2_name> else inc <var3_name>");
                cmd.Help_Set("check var1 by int and increment var2 or var3");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare INT do script stop // @Attention: Must be before check if str compare STR do script stop
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_do_script_stop);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script stop");
                cmd.Help_Set("check var by int and stop script");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Word("stop", "do script stop"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare INT do script str // @Attention: Must be before check if str compare STR do script str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_do_script_filename);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script <filename>");
                cmd.Help_Set("check var by int and do script from file");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare INT do script str no history // @Attention: Must be before check if str compare STR do script str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_do_script_filename_no_history);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script <filename> no history");
                cmd.Help_Set("check var by int and do script from file, not save to history");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
                cmd.Item_Add(new Cmd_Item_Word("no", "not save"));
                cmd.Item_Add(new Cmd_Item_Word("history", "not save to history"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: str as value print/inc/do script/do command">
            {
                // check if str compare STR as value print str // @Attention: Must be after check if str compare INT print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_print_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + " > <str> as value print <msg>");
                cmd.Help_Set("check var by str and print msg");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as value print str else print str // @Attention: Must be after check if str compare INT print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + " > <str> as value print <msg1> else print <msg2>");
                cmd.Help_Set("check var by str and print msg1 or msg2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("print", "else print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as value inc str // @Attention: Must be after check if str compare INT inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name>");
                cmd.Help_Set("check var1 by str and increment var2 or var3");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<str>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as value inc str else inc str // @Attention: Must be after check if str compare INT inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name> else inc <var3_name>");
                cmd.Help_Set("check var1 by str and increment var2 or var3");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<str>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as value do script stop // @Attention: Must be after check if str compare INT do script stop
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_do_script_stop);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value do script stop");
                cmd.Help_Set("check var by str and stop script");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "str as value"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Word("stop", "do script stop"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as value do script filename // @Attention: Must be after check if str compare INT do script filename
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_do_script_filename);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do script <filename>");
                cmd.Help_Set("check var by str and execute script from file");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "str as value"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as value do script str no history // @Attention: Must be after check if str compare INT do script str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do script <filename> no history");
                cmd.Help_Set("check var by str as value and do script from file, not save to history");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "str as value"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
                cmd.Item_Add(new Cmd_Item_Word("no", "not save"));
                cmd.Item_Add(new Cmd_Item_Str("history", "not save to history"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: str as var print/inc/do script/do command">
            {
                // check if str compare STR as var print str // @Attention: Must be after check if str compare INT print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_print_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var print <msg>");
                cmd.Help_Set("check var1 by var2 and print msg");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as var print str else print str // @Attention: Must be after check if str compare INT print str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var print <msg1> else print <msg2>");
                cmd.Help_Set("check var1 by var2 and print msg1 or msg2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("print", "check and print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("print", "else print"));
                cmd.Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as var inc str // @Attention: Must be after check if str compare INT inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name>");
                cmd.Help_Set("check var1 by var2 and increment var3");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = true)"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as var inc str else inc str // @Attention: Must be after check if str compare INT inc str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str);
                cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name> else inc <var4_name>");
                cmd.Help_Set("check var1 by var2 and increment var3 or var4");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = true)"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
                cmd.Item_Add(new Cmd_Item_Str("<var4_name>", "var4 name to increment (if compare result = false)"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as var do script stop // @Attention: Must be after check if str compare INT do script stop
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_do_script_stop);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script stop");
                cmd.Help_Set("check var1 by var2 and stop script");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Word("stop", "do script stop"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as var do script str // @Attention: Must be after check if str compare INT do script str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_do_script_filename);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script <filename>");
                cmd.Help_Set("check var1 by var2 and do script from file");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as var do script str no history // @Attention: Must be after check if str compare INT do script str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script <filename> no history");
                cmd.Help_Set("check var1 by var2 and do script from file, not save to history");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("script", "do script"));
                cmd.Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
                cmd.Item_Add(new Cmd_Item_Word("no", "not save"));
                cmd.Item_Add(new Cmd_Item_Str("history", "not save to history"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var do command">
            {
                // check if str compare INT do command str // @Attention: Must be before check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_do_command_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <int_value> do command <command_str>");
                cmd.Help_Set("check var by int and do command");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command_str>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare INT do command str else do command str // @Attention: Must be before check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <int_value> do command <command1_str> else do command <command2_str>");
                cmd.Help_Set("check var by int and do command1 or do command2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as value do command str // @Attention: Must be after check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_do_command_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do command <command_str>");
                cmd.Help_Set("check var by str and do command");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command_str>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as value do command str else do command str // @Attention: Must be after check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do command <command1_str> else do command <command2_str>");
                cmd.Help_Set("check var by str and do command1 or do command2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare STR as var do command str // @Attention: Must be after check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_do_command_str);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do command <command_str>");
                cmd.Help_Set("check var1 by var2 and do command");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command_str>", "command"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare STR as var do command str else do command str // @Attention: Must be after check if str compare INT do command str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do command <command1_str> else do command <command2_str>");
                cmd.Help_Set("check var1 by var2 and do command1 or do command2");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("do", "do"));
                cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
                cmd.Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
            {
                // check label str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_label_str);
                cmd.Text_Set("check label <label_name>");
                cmd.Help_Set("create label <label_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("label", "create label"));
                cmd.Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

                Cmd_Add(cmd);
            }

            {
                // check goto label
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_goto_label);
                cmd.Text_Set("check goto <label_name>");
                cmd.Help_Set("goto <label_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
            {
                // check if str compare INT goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_goto_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> goto <label_name>");
                cmd.Help_Set("check var by int and goto <label_name>(for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare INT goto str else goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_int_goto_str_else_goto_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> goto <label1_name> else goto <label2_name>");
                cmd.Help_Set("check var by int and goto <label1_name> or <label2_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare str as value goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_goto_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value goto <label1_name> else goto <label2_name>");
                cmd.Help_Set("check var by str and goto <label1_name> or <label2_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare str as value goto str else goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str);
                cmd.Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value goto <label1_name> else goto <label2_name>");
                cmd.Help_Set("check var by str and goto <label1_name> or <label2_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

                Cmd_Add(cmd);
            }

            {
                // check if str compare str as var goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_goto_str);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_int_str + "> <var2_name> as var goto <label_name>");
                cmd.Help_Set("check var1 by var2 and goto <label_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

                Cmd_Add(cmd);
            }
            {
                // check if str compare str as var goto str else goto str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str);
                cmd.Text_Set("check if <var1_name>  <compare: " + cmp_int_str + "> <var2_name> as var goto <label1_name> else goto <label2_name>");
                cmd.Help_Set("check var1 by var2 and goto <label1_name> or <label2_name> (for scripts only)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("check", "check"));
                cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
                cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
                cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
                cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
                cmd.Item_Add(new Cmd_Item_Word("as", "as"));
                cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
                cmd.Item_Add(new Cmd_Item_Word("else", "else"));
                cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
                cmd.Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

                Cmd_Add(cmd);
            }
            // </editor-fold>

        }

        // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">

        bool check_map_print(string var_filter, Str_Filter str_filter)
        {

            Cli_Output.Output_NewLine();

            if (Values_Map.Count != 0)
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

            Cli_Output.Output_NewLine();

            if (Values_Map.Count != 0)
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
            Cli_Output.Output_NewLine();
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

        override public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
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


            }
            return false; // Not Implemented
        }

        override public void To_Map(Dictionary<string, string> values_map)
        {
            string Prefix = "Check";
            values_map[Prefix + ".Count_Total"] = Count_Total.ToString();
            values_map[Prefix + ".Count_Passed"] = Count_Passed.ToString();
            values_map[Prefix + ".Count_Failed"] = Count_Failed.ToString();
        }

    }
}
