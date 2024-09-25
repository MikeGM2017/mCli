/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module_Check extends Cli_Module {

    protected Cli_Modules Modules;

    protected Map<String, String> Values_Map;

    protected Str_Filter Str_Filter;

    protected Str_Get_Without_Commas Str_Without_Commas;

    protected Cli_Output_JavaFX Cli_Output;

    protected Ref_Boolean Cmd_Script_Stop;

    protected Ref_String Script_Command_Str;
    protected Ref_String Script_Label_Str;

    protected Do_Abstract Do_Command_Object;

    protected int Count_Total = 0;
    protected int Count_Passed = 0;
    protected int Count_Failed = 0;

    //enum Local_Cmd_ID
    //{
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_check_map = 1;
    private final int CMD_ID_check_map_print = 2;
    private final int CMD_ID_check_map_print_by_filter = 3;
    private final int CMD_ID_check_map_clear = 4;

    private final int CMD_ID_check_modules_by_filter_to_map = 5;
    //private final int CMD_ID_check_modules_by_filter_from_map = ;

    private final int CMD_ID_check_var_str_set_str_as_value = 6;
    private final int CMD_ID_check_var_str_set_str_as_value_force = 7;
    private final int CMD_ID_check_var_str_set_str_as_var = 8;
    private final int CMD_ID_check_var_str_set_str_as_var_force = 9;
    private final int CMD_ID_check_var_str_set_str_as_expr = 10;
    private final int CMD_ID_check_var_str_set_str_as_expr_force = 11;

    private final int CMD_ID_check_var_str_inc = 12;

    private final int CMD_ID_check_if_str_compare_int_print_str = 13;
    private final int CMD_ID_check_if_str_compare_int_print_str_else_print_str = 14;
    private final int CMD_ID_check_if_str_compare_int_inc_str = 15;
    private final int CMD_ID_check_if_str_compare_int_inc_str_else_inc_str = 16;
    private final int CMD_ID_check_if_str_compare_int_do_script_stop = 17;
    private final int CMD_ID_check_if_str_compare_int_do_script_filename = 18;
    private final int CMD_ID_check_if_str_compare_int_do_script_filename_no_history = 19;

    private final int CMD_ID_check_if_str_compare_str_as_value_print_str = 20;
    private final int CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str = 21;
    private final int CMD_ID_check_if_str_compare_str_as_value_inc_str = 22;
    private final int CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str = 23;
    private final int CMD_ID_check_if_str_compare_str_as_value_do_script_stop = 24;
    private final int CMD_ID_check_if_str_compare_str_as_value_do_script_filename = 25;
    private final int CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history = 26;

    private final int CMD_ID_check_if_str_compare_str_as_var_print_str = 27;
    private final int CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str = 28;
    private final int CMD_ID_check_if_str_compare_str_as_var_inc_str = 29;
    private final int CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str = 30;
    private final int CMD_ID_check_if_str_compare_str_as_var_do_script_stop = 31;
    private final int CMD_ID_check_if_str_compare_str_as_var_do_script_filename = 32;
    private final int CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history = 33;

    private final int CMD_ID_check_if_str_compare_int_do_command_str = 34;
    private final int CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str = 35;
    private final int CMD_ID_check_if_str_compare_str_as_value_do_command_str = 36;
    private final int CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str = 37;
    private final int CMD_ID_check_if_str_compare_str_as_var_do_command_str = 38;
    private final int CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str = 39;

    private final int CMD_ID_check_if_str_exists_print_str = 40;
    private final int CMD_ID_check_if_str_exists_print_str_else_print_str = 41;
    private final int CMD_ID_check_if_str_exists_do_command_str = 42;
    private final int CMD_ID_check_if_str_exists_do_command_str_else_do_command_str = 43;

    private final int CMD_ID_check_label_str = 44;
    private final int CMD_ID_check_goto_label = 45;

    private final int CMD_ID_check_print_str = 46;

    private final int CMD_ID_check_if_str_compare_int_goto_str = 47;
    private final int CMD_ID_check_if_str_compare_int_goto_str_else_goto_str = 48;
    private final int CMD_ID_check_if_str_compare_str_as_value_goto_str = 49;
    private final int CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str = 50;
    private final int CMD_ID_check_if_str_compare_str_as_var_goto_str = 51;
    private final int CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str = 52;

    private final int CMD_ID_LAST = 53;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    enum Local_Compare_Result {
        CMP_FALSE,
        CMP_TRUE,
        CMP_ERROR
    };

    public Cli_Module_Check(Cli_Modules modules, Map<String, String> values_map,
            Str_Filter str_filter,
            Str_Get_Without_Commas str_without_commas,
            Cli_Output_JavaFX cli_output,
            Ref_Boolean cmd_script_stop,
            Ref_String script_command_str, Ref_String script_label_str,
            Do_Abstract do_command_object) {
        super("Check");

        Version = "0.04";

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
        String cmp_int_str = "== != < > <= >= & | && ||";
        List<String> cmp_int_words = new ArrayList<>();
        cmp_int_words.add("==");
        cmp_int_words.add("!=");
        cmp_int_words.add("<");
        cmp_int_words.add(">");
        cmp_int_words.add("<=");
        cmp_int_words.add(">=");
        cmp_int_words.add("&");
        cmp_int_words.add("|");
        cmp_int_words.add("&&");
        cmp_int_words.add("||");

        String cmp_str_str = "== != < > <= >=";
        List<String> cmp_str_words = new ArrayList<String>();
        cmp_str_words.add("==");
        cmp_str_words.add("!=");
        cmp_str_words.add("<");
        cmp_str_words.add(">");
        cmp_str_words.add("<=");
        cmp_str_words.add(">=");
        cmp_str_words.add("&");
        cmp_str_words.add("|");
        cmp_str_words.add("&&");
        cmp_str_words.add("||");
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">
        {
            // check map
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_map);
            cmd.Text_Set("check map");
            cmd.Help_Set("print values from map (all values)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("map", "check map"));

            Cmd_Add(cmd);
        }
        {
            // check map print
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_map_print);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_map_print_by_filter);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_map_clear);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_modules_by_filter_to_map);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_value);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_value_force);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_var);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_var_force);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_expr);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_set_str_as_expr_force);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_var_str_inc);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_print_str_else_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_inc_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_inc_str_else_inc_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_do_script_stop);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_do_script_filename);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_do_script_filename_no_history);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_inc_str);
            cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name>");
            cmd.Help_Set("check var1 by str and increment var2 or var3");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
            cmd.Item_Add(new Cmd_Item_Word("as", "as"));
            cmd.Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as value inc str else inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str);
            cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name> else inc <var3_name>");
            cmd.Help_Set("check var1 by str and increment var2 or var3");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_do_script_stop);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_do_script_filename);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_inc_str);
            cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name>");
            cmd.Help_Set("check var1 by var2 and increment var3");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd.Item_Add(new Cmd_Item_Word("as", "as"));
            cmd.Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd.Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd.Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = true)"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as var inc str else inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str);
            cmd.Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name> else inc <var4_name>");
            cmd.Help_Set("check var1 by var2 and increment var3 or var4");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd.Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd.Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_do_script_stop);
            cmd.Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script stop");
            cmd.Help_Set("check var1 by var2 and stop script");
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
            cmd.Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as var do script str // @Attention: Must be after check if str compare INT do script str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_do_script_filename);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_do_command_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_do_command_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_do_command_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str);
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

        // <editor-fold defaultstate="collapsed" desc="Check if: var exists print/do command">
        {
            // check if str exists print str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_exists_print_str);
            cmd.Text_Set("check if <var_name>  exists print <str>");
            cmd.Help_Set("check var exists and print str");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
            cmd.Item_Add(new Cmd_Item_Word("print", "print"));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "str"));

            Cmd_Add(cmd);
        }
        {
            // check if str exists print str else print str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_exists_print_str_else_print_str);
            cmd.Text_Set("check if <var_name>  exists print <str1> else print <str2>");
            cmd.Help_Set("check var exists and print str1 or str2");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
            cmd.Item_Add(new Cmd_Item_Word("print", "print"));
            cmd.Item_Add(new Cmd_Item_Str("<str1>", "str1"));
            cmd.Item_Add(new Cmd_Item_Word("else", "else"));
            cmd.Item_Add(new Cmd_Item_Word("print", "print"));
            cmd.Item_Add(new Cmd_Item_Str("<str2>", "str2"));

            Cmd_Add(cmd);
        }

        {
            // check if str exists do command str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_exists_do_command_str);
            cmd.Text_Set("check if <var_name>  exists do command <command_str>");
            cmd.Help_Set("check var exists and do command");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
            cmd.Item_Add(new Cmd_Item_Word("do", "do"));
            cmd.Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd.Item_Add(new Cmd_Item_Str("<command_str>", "command"));

            Cmd_Add(cmd);
        }
        {
            // check if str exists do command str else do command str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_exists_do_command_str_else_do_command_str);
            cmd.Text_Set("check if <var_name>  exists do command <command1_str> else do command <command2_str>");
            cmd.Help_Set("check var exists and do command1 or do command2");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd.Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd.Item_Add(new Cmd_Item_Word("exists", "var exists"));
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_label_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_goto_label);
            cmd.Text_Set("check goto <label_name>");
            cmd.Help_Set("goto <label_name> (for scripts only)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd.Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Print Str">
        {
            // check print str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_print_str);
            cmd.Text_Set("check print <str>");
            cmd.Help_Set("print <str>");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("check", "check"));
            cmd.Item_Add(new Cmd_Item_Word("print", "print"));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "str"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
        {
            // check if str compare INT goto str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_goto_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_int_goto_str_else_goto_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_goto_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_goto_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str);
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

    String Var_Name_Without_Point_Get(String s) {
        if (s.length() > 0 && s.charAt(0) == '.') {
            return s.substring(1);
        }
        return s;
    }

    int Str_To_Int(String s) {
        int v;
        try {
            v = Integer.parseInt(s);
        } catch (NumberFormatException e) {
            v = 0;
        }
        return v;
    }

    // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">
    boolean check_map_print(String var_filter, Str_Filter str_filter) {
        if (Values_Map.size() > 0) {
            Cli_Output.Output_Str("Values Map:");
            Cli_Output.Output_NewLine();
            boolean found = false;
            for (Map.Entry<String, String> item : Values_Map.entrySet()) {
                if (str_filter.Is_Match(var_filter, item.getKey())) {
                    Cli_Output.Output_Str(item.getKey() + " = " + item.getValue());
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
            if (!found) {
                Cli_Output.Output_Str(var_filter);
                Cli_Output.Output_Str(" - Not Found");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("Values Map is empty");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_map_clear() {
        if (Values_Map.size() > 0) {
            Values_Map.clear();
            Cli_Output.Output_Str("Values Map cleared");
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_Str("Values Map is empty");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">
    boolean check_modules_to_map(String module_filter, Str_Filter str_filter) {
        boolean found = false;
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module module_ptr = Modules.Get(module);
            if (module_ptr != null) {
                String module_name = module_ptr.Name_Get();
                String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                if (str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                    module_ptr.To_Map(Values_Map);
                    Cli_Output.Output_Str(module_name + " . Values Map");
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
        }
        if (!found) {
            Cli_Output.Output_Str(module_filter);
            Cli_Output.Output_Str(" - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">
    boolean check_var_set_str_as_value(String var_left, String value, boolean is_force) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //if (var_left_iter != Values_Map.end() || is_force)
        if (var_left_found || is_force) {
            Values_Map.put(var_left, value);
            Values_Map.put(var_left, value);
            //if (var_left_iter == Values_Map.end())
            if (!var_left_found) {
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_set_str_as_var(String var_left, String var_right, boolean is_force) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        //if ((var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) || is_force)
        if ((var_left_found && var_right_found) || (is_force && var_right_found)) {
            String value = var_right_value_old;
            Values_Map.put(var_left, value);
            if (!var_left_found) {
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    String Expr_Calc(Map<String, String> values_map, String expr) {
        return "<Expr_Calc(" + expr + ")>";
    }

    boolean check_var_set_str_as_expr(String var_left, String expr, boolean is_force) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //if (var_left_iter != Values_Map.end() || is_force)
        if (var_left_found || is_force) {
            String value = Expr_Calc(Values_Map, expr);
            Values_Map.put(var_left, value);
            if (!var_left_found) {
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Var: inc">
    boolean check_var_inc_value(String var_left) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            //int value = 0;
            //Int32.TryParse(var_left_value_old, out value);

            int value = Str_To_Int(var_left_value_old);
            value++;
            Values_Map.put(var_left, Integer.toString(value));
        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Compare_Values: int/str">
    Local_Compare_Result Compare_Values_Int(int var_left_value, String s_compare, int var_right_value) {
        Local_Compare_Result cmp_res = Local_Compare_Result.CMP_FALSE;
        if (null != s_compare) {
            switch (s_compare) {
                case "==":
                    if (var_left_value == var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "!=":
                    if (var_left_value != var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<":
                    if (var_left_value < var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">":
                    if (var_left_value > var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<=":
                    if (var_left_value <= var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">=":
                    if (var_left_value >= var_right_value) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "&":
                    if ((var_left_value & var_right_value) != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "|":
                    if ((var_left_value | var_right_value) != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "&&":
                    if (var_left_value != 0 && var_right_value != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "||":
                    if (var_left_value != 0 || var_right_value != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                default:
                    cmp_res = Local_Compare_Result.CMP_ERROR;
                    break;
            }
        }
        return cmp_res;
    }

    Local_Compare_Result Compare_Values_Str(String var_left_value, String s_compare, String var_right_value) {
        Local_Compare_Result cmp_res = Local_Compare_Result.CMP_FALSE;
        if (null != s_compare) {
            switch (s_compare) {
                case "==":
                    if (var_left_value.compareTo(var_right_value) == 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "!=":
                    if (var_left_value.compareTo(var_right_value) != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<":
                    //if (var_left_value < var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                    if (var_left_value.compareTo(var_right_value) < 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">":
                    //if (var_left_value > var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                    if (var_left_value.compareTo(var_right_value) > 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<=":
                    //if (var_left_value <= var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                    if (var_left_value.compareTo(var_right_value) <= 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">=":
                    //if (var_left_value >= var_right_value) cmp_res = Local_Compare_Result.CMP_TRUE;
                    if (var_left_value.compareTo(var_right_value) >= 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                default:
                    cmp_res = Local_Compare_Result.CMP_ERROR;
                    break;
            }
        }
        return cmp_res;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/as var print/inc">
    boolean check_var_by_int_print_msg1_or_msg2(String var_left, String s_compare, int var_right_value,
            String s_msg1, boolean is_msg2, String s_msg2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);

            int var_left_value = Str_To_Int(var_left_value_old);

            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Cli_Output.Output_Str(Str_Without_Commas.Get(s_msg1));
                Cli_Output.Output_NewLine();
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                if (is_msg2) {
                    Cli_Output.Output_Str(Str_Without_Commas.Get(s_msg2));
                    Cli_Output.Output_NewLine();
                }
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_str_print_msg1_or_msg2(String var_left, String s_compare, String var_right_value,
            String s_msg1, boolean is_msg2, String s_msg2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            String var_left_value = var_left_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Cli_Output.Output_Str(Str_Without_Commas.Get(s_msg1));
                Cli_Output.Output_NewLine();
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                if (is_msg2) {
                    Cli_Output.Output_Str(Str_Without_Commas.Get(s_msg2));
                    Cli_Output.Output_NewLine();
                }
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_var_print_msg1_or_msg2(String var_left, String s_compare, String var_right,
            String s_msg1, boolean is_msg2, String s_msg2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        if (var_left_found && var_right_found) {
            //int var_right_value = 0;
            //Int32.TryParse(var_right_value_old, out var_right_value);

            int var_right_value = Str_To_Int(var_right_value_old);

            return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2, s_msg2);
        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    boolean check_var_by_int_inc_var1_or_var2(String var_left, String s_compare, int var_right_value,
            String var1_inc, boolean is_var2_inc, String var2_inc) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        //map<String, String>::iterator var2_inc_iter = Values_Map.find(var2_inc);
        //String var_left_value_old = "";
        //String var1_inc_value_old = "";
        //String var2_inc_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var1_inc_found = Values_Map.TryGetValue(var1_inc, out var1_inc_value_old);
        boolean var1_inc_found = Values_Map.containsKey(var1_inc);
        String var1_inc_value_old = Values_Map.get(var1_inc);
        //boolean var2_inc_found = Values_Map.TryGetValue(var2_inc, out var2_inc_value_old);
        boolean var2_inc_found = Values_Map.containsKey(var2_inc);
        String var2_inc_value_old = Values_Map.get(var2_inc);
        if (var_left_found && var1_inc_found
                && (var2_inc_found || !is_var2_inc)) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            //int var1_value = Int32.TryParse(var1_inc_iter.second);
            //int var2_value = 0;
            //if (is_var2_inc)
            //{
            //    var2_value = Int32.TryParse(var2_inc_iter.second);
            //}

            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);
            int var_left_value = Str_To_Int(var_left_value_old);

            //int var1_value = 0;
            //Int32.TryParse(var1_inc_value_old, out var1_value);
            int var1_value = Str_To_Int(var1_inc_value_old);

            int var2_value = 0;
            if (is_var2_inc) {
                //Int32.TryParse(var2_inc_value_old, out var2_value);

                var2_value = Str_To_Int(var2_inc_value_old);

            }

            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                var1_value++;
                Values_Map.put(var1_inc, Integer.toString(var1_value));
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    Values_Map.put(var2_inc, Integer.toString(var2_value));
                }
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var1_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && !var2_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    boolean check_var_by_str_inc_var1_or_var2(String var_left, String s_compare, String var_right_value,
            String var1_inc, boolean is_var2_inc, String var2_inc) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        //map<String, String>::iterator var2_inc_iter = Values_Map.find(var2_inc);
        //String var_left_value_old = "";
        //String var1_inc_value_old = "";
        //String var2_inc_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var1_inc_found = Values_Map.TryGetValue(var1_inc, out var1_inc_value_old);
        boolean var1_inc_found = Values_Map.containsKey(var1_inc);
        String var1_inc_value_old = Values_Map.get(var1_inc);
        //boolean var2_inc_found = Values_Map.TryGetValue(var2_inc, out var2_inc_value_old);
        boolean var2_inc_found = Values_Map.containsKey(var2_inc);
        String var2_inc_value_old = Values_Map.get(var2_inc);
        if (var_left_found && var1_inc_found
                && (var2_inc_found || !is_var2_inc)) {
            //int var1_value = Int32.TryParse(var1_inc_iter.second);
            //int var2_value = 0;
            //if (is_var2_inc)
            //{
            //    var2_value = Int32.TryParse(var2_inc_iter.second);
            //}
            //int var1_value = 0;
            //Int32.TryParse(var1_inc_value_old, out var1_value);

            int var1_value = Str_To_Int(var1_inc_value_old);

            int var2_value = 0;
            if (is_var2_inc) {
                //Int32.TryParse(var2_inc_value_old, out var2_value);

                var2_value = Str_To_Int(var2_inc_value_old);

            }

            String var_left_value = var_left_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                var1_value++;
                Values_Map.put(var1_inc, Integer.toString(var1_value));
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    Values_Map.put(var2_inc, Integer.toString(var2_value));
                }
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var1_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && !var2_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    boolean check_var_by_var_inc_var1_or_var2(String var_left, String s_compare, String var_right,
            String var1_inc, boolean is_var2_inc, String var2_inc) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //map<String, String>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        //map<String, String>::iterator var2_inc_iter = Values_Map.find(var2_inc);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //String var1_inc_value_old = "";
        //String var2_inc_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        //boolean var1_inc_found = Values_Map.TryGetValue(var1_inc, out var1_inc_value_old);
        boolean var1_inc_found = Values_Map.containsKey(var1_inc);
        String var1_inc_value_old = Values_Map.get(var1_inc);
        //boolean var2_inc_found = Values_Map.TryGetValue(var2_inc, out var2_inc_value_old);
        boolean var2_inc_found = Values_Map.containsKey(var2_inc);
        String var2_inc_value_old = Values_Map.get(var2_inc);
        if (var_left_found
                && var_right_found
                && var1_inc_found
                && ((is_var2_inc && var2_inc_found) || !is_var2_inc)) {
            //int var1_value = Int32.TryParse(var1_inc_iter.second);
            //int var2_value = 0;
            //if (is_var2_inc)
            //{
            //    var2_value = Int32.TryParse(var2_inc_iter.second);
            //}
            //int var1_value = 0;
            //Int32.TryParse(var1_inc_value_old, out var1_value);

            int var1_value = Str_To_Int(var1_inc_value_old);

            int var2_value = 0;
            if (is_var2_inc) {
                //Int32.TryParse(var2_inc_value_old, out var2_value);

                var2_value = Str_To_Int(var2_inc_value_old);

            }

            String var_left_value = var_left_value_old;
            String var_right_value = var_right_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                var1_value++;
                Values_Map.put(var1_inc, Integer.toString(var1_value));
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    Values_Map.put(var2_inc, Integer.toString(var2_value));
                }
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var1_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && !var2_inc_found) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    // </editor-fold>
    boolean Do_Script_From_File(String filename, boolean is_no_history) {
        boolean is_filename_spaces = false;
        //if (filename.find(' ') != std::String::npos) is_filename_spaces = true;
        //if (filename.find('\t') != std::String::npos) is_filename_spaces = true;
        if (filename.contains(" ")) {
            is_filename_spaces = true;
        }
        if (filename.contains("\t")) {
            is_filename_spaces = true;
        }
        if (is_filename_spaces) {
            Script_Command_Str.Value = "do script \"" + filename + "\"";
        } else {
            Script_Command_Str.Value = "do script " + filename;
        }
        if (is_no_history) {
            Script_Command_Str.Value += " no history";
        }
        Do_Command_Object.Do();
        return true;
    }

    boolean Do_Command(String command) {
        Script_Command_Str.Value = command;
        Do_Command_Object.Do();
        return true;
    }

    boolean Do_Label(String label) {
        //@Warning: Command "check goto <label>" - special case: is moves file position
        // no action
        return true;
    }

    boolean Do_Goto_Label(String label) {
        //Script_Command_Str = "check goto " + label;
        Script_Label_Str.Value = label;
        return true;
    }

    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/as var do">
    boolean check_var_by_int_do_script_stop(String var_left, String s_compare, int var_right_value) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);

            int var_left_value = Str_To_Int(var_left_value_old);

            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Cmd_Script_Stop.Value = true;
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_int_do_script_from_file(String var_left, String s_compare, int var_right_value, String filename, boolean is_no_history) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);

            int var_left_value = Str_To_Int(var_left_value_old);

            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_str_do_script_stop(String var_left, String s_compare, String var_right_value) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            String var_left_value = var_left_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Cmd_Script_Stop.Value = true;
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_str_do_script_from_file(String var_left, String s_compare, String var_right_value, String filename, boolean is_no_history) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            //int var_left_value = 0;Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean check_var_by_var_do_script_stop(String var_left, String s_compare, String var_right) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        if (var_left_found && var_right_found) {
            String var_left_value = var_left_value_old;
            String var_right_value = var_right_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Cmd_Script_Stop.Value = true;
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    boolean check_var_by_var_do_script_from_file(String var_left, String s_compare, String var_right, String filename, boolean is_no_history) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        if (var_left_found && var_right_found) {
            //int var_left_value = 0;Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            String var_right_value = var_right_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE) {
                // Nothing
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    boolean check_var_by_int_do_command(String var_left, String s_compare, int var_right_value, String command1, boolean is_command2, String command2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        if (var_left_found //&& var_left_found
                ) {
            //int var_left_value = Int32.TryParse(var_left_iter.second.Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str););
            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);

            int var_left_value = Str_To_Int(var_left_value_old);

            //String var_left_value = var_left_iter.second;
            //String var_right_value = var_right_iter.second;
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter == Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter == Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    boolean check_var_by_str_do_command(String var_left, String s_compare, String var_right_value, String command1, boolean is_command2, String command2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        if (var_left_found //&& var_right_found
                ) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            //String var_right_value = var_right_iter.second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter == Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter == Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    boolean check_var_by_var_do_command(String var_left, String s_compare, String var_right, String command1, boolean is_command2, String command2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        if (var_left_found && var_right_found) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            String var_right_value = var_right_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Check if: var exists print/do command">
    boolean check_var_exists_print(String var_left, String str1, boolean is_str2, String str2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            Cli_Output.Output_Str(Str_Without_Commas.Get(str1));
            Cli_Output.Output_NewLine();
        } else if (is_str2) {
            Cli_Output.Output_Str(Str_Without_Commas.Get(str2));
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    boolean check_var_exists_do_command(String var_left, String command1, boolean is_command2, String command2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //String var_left_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        if (var_left_found) {
            Do_Command(command1);
        } else if (is_command2) {
            Do_Command(command2);
        }
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
    boolean check_label(String label) {
        return Do_Label(label);
    }

    boolean check_goto_label(String label) {
        return Do_Goto_Label(label);
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Print Str">
    boolean check_print_str(String s) {
        Cli_Output.Output_Str(Str_Without_Commas.Get(s));
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
    boolean check_var_by_int_goto_label(String var_left, String s_compare, int var_right_value, String label1, boolean is_label2, String label2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        if (var_left_found //&& var_right_found
                ) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            //int var_left_value = 0;
            //Int32.TryParse(var_left_value_old, out var_left_value);

            int var_left_value = Str_To_Int(var_left_value_old);

            //String var_right_value = var_right_iter.second;
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter == Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter == Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    boolean check_var_by_str_goto_label(String var_left, String s_compare, String var_right_value, String label1, boolean is_label2, String label2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        if (var_left_found //&& var_right_found
                ) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            //String var_right_value = var_right_iter.second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, Str_Without_Commas.Get(var_right_value));
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter == Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter == Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    boolean check_var_by_var_goto_label(String var_left, String s_compare, String var_right, String label1, boolean is_label2, String label2) {
        //map<String, String>::iterator var_left_iter = Values_Map.find(var_left);
        //map<String, String>::iterator var_right_iter = Values_Map.find(var_right);
        //String var_left_value_old = "";
        //String var_right_value_old = "";
        //boolean var_left_found = Values_Map.TryGetValue(var_left, out var_left_value_old);
        boolean var_left_found = Values_Map.containsKey(var_left);
        String var_left_value_old = Values_Map.get(var_left);
        //boolean var_right_found = Values_Map.TryGetValue(var_right, out var_right_value_old);
        boolean var_right_found = Values_Map.containsKey(var_left);
        String var_right_value_old = Values_Map.get(var_right);
        if (var_left_found && var_right_found) {
            //int var_left_value = Int32.TryParse(var_left_iter.second);
            String var_left_value = var_left_value_old;
            String var_right_value = var_right_value_old;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == Local_Compare_Result.CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == Local_Compare_Result.CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == Local_Compare_Result.CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (!var_left_found) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (!var_right_found) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }
        return true;
    }

    // </editor-fold>
    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {

            // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">
            case CMD_ID_check_map:
            case CMD_ID_check_map_print:
                if (is_debug) {
                    return true;
                } else {
                    String var_filter = "";
                    return check_map_print(var_filter, Str_Filter);
                }
            case CMD_ID_check_map_print_by_filter:
                if (is_debug) {
                    return true;
                } else {
                    String var_filter = cmd.Items.get(3).Value_Str;
                    return check_map_print(var_filter, Str_Filter);
                }
            case CMD_ID_check_map_clear:
                if (is_debug) {
                    return true;
                }
                return check_map_clear();

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">
            case CMD_ID_check_modules_by_filter_to_map:
                if (is_debug) {
                    return true;
                } else {
                    String module_filter = cmd.Items.get(2).Value_Str;
                    return check_modules_to_map(module_filter, Str_Filter);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">
            case CMD_ID_check_var_str_set_str_as_value:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String value = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_value(var_left, value, if_force = false);
                }
            case CMD_ID_check_var_str_set_str_as_value_force:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String value = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_value(var_left, value, if_force = true);
                }

            case CMD_ID_check_var_str_set_str_as_var:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String value = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_var(var_left, value, if_force = false);
                }
            case CMD_ID_check_var_str_set_str_as_var_force:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String value = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_var(var_left, value, if_force = true);
                }

            case CMD_ID_check_var_str_set_str_as_expr:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String expr = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_expr(var_left, expr, if_force = false);
                }
            case CMD_ID_check_var_str_set_str_as_expr_force:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String expr = cmd.Items.get(4).Value_Str;
                    boolean if_force;
                    return check_var_set_str_as_expr(var_left, expr, if_force = true);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Var: inc">
            case CMD_ID_check_var_str_inc:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    return check_var_inc_value(var_left);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Check if: int print/inc/do">
            case CMD_ID_check_if_str_compare_int_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String s_msg1 = cmd.Items.get(6).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = "";
                    return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2 = false, s_msg2);
                }
            case CMD_ID_check_if_str_compare_int_print_str_else_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String s_msg1 = cmd.Items.get(6).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = cmd.Items.get(9).Value_Str;
                    return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2 = true, s_msg2);
                }

            case CMD_ID_check_if_str_compare_int_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String var1_inc = cmd.Items.get(6).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = "";
                    return check_var_by_int_inc_var1_or_var2(var_left, s_compare, var_right_value, var1_inc, is_var2_inc = false, var2_inc);
                }
            case CMD_ID_check_if_str_compare_int_inc_str_else_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String var1_inc = cmd.Items.get(6).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = cmd.Items.get(9).Value_Str;
                    return check_var_by_int_inc_var1_or_var2(var_left, s_compare, var_right_value, var1_inc, is_var2_inc = true, var2_inc);
                }

            case CMD_ID_check_if_str_compare_int_do_script_stop:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    return check_var_by_int_do_script_stop(var_left, s_compare, var_right_value);
                }

            case CMD_ID_check_if_str_compare_int_do_script_filename:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_int_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = false);
                }
            case CMD_ID_check_if_str_compare_int_do_script_filename_no_history:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_int_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = true);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Check if: str as value print/inc/do">
            case CMD_ID_check_if_str_compare_str_as_value_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String value = cmd.Items.get(4).Value_Str;
                    String s_msg1 = cmd.Items.get(8).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = "";
                    return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value, s_msg1, is_msg2 = false, s_msg2);
                }
            case CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String value = cmd.Items.get(4).Value_Str;
                    String s_msg1 = cmd.Items.get(8).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = cmd.Items.get(11).Value_Str;
                    return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value, s_msg1, is_msg2 = true, s_msg2);
                }

            case CMD_ID_check_if_str_compare_str_as_value_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String value = cmd.Items.get(4).Value_Str;
                    String var1_inc = cmd.Items.get(8).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = "";
                    return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value, var1_inc, is_var2_inc = false, var2_inc);
                }
            case CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String value = cmd.Items.get(4).Value_Str;
                    String var1_inc = cmd.Items.get(8).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = cmd.Items.get(11).Value_Str;
                    return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value, var1_inc, is_var2_inc = true, var2_inc);
                }

            case CMD_ID_check_if_str_compare_str_as_value_do_script_stop:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    return check_var_by_str_do_script_stop(var_left, s_compare, var_right_value);
                }

            case CMD_ID_check_if_str_compare_str_as_value_do_script_filename:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_str_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = false);
                }
            case CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_str_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = true);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Check if: str as var print/inc/do">
            case CMD_ID_check_if_str_compare_str_as_var_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String s_msg1 = cmd.Items.get(8).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = "";
                    return check_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
                }
            case CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String s_msg1 = cmd.Items.get(8).Value_Str;
                    boolean is_msg2;
                    String s_msg2 = cmd.Items.get(11).Value_Str;
                    return check_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                }

            case CMD_ID_check_if_str_compare_str_as_var_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String var1_inc = cmd.Items.get(8).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = "";
                    return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_inc, is_var2_inc = false, var2_inc);
                }
            case CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String var1_inc = cmd.Items.get(8).Value_Str;
                    boolean is_var2_inc;
                    String var2_inc = cmd.Items.get(11).Value_Str;
                    return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_inc, is_var2_inc = true, var2_inc);
                }

            case CMD_ID_check_if_str_compare_str_as_var_do_script_stop:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    return check_var_by_var_do_script_stop(var_left, s_compare, var_right);
                }

            case CMD_ID_check_if_str_compare_str_as_var_do_script_filename:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = false);
                }
            case CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String filename = cmd.Items.get(7).Value_Str;
                    boolean is_no_history;
                    return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = true);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var do command">
            case CMD_ID_check_if_str_compare_int_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String command1 = cmd.Items.get(7).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_by_int_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
                }
            case CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String command1 = cmd.Items.get(7).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(11).Value_Str;
                    return check_var_by_int_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
                }

            case CMD_ID_check_if_str_compare_str_as_value_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String command1 = cmd.Items.get(9).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
                }
            case CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String command1 = cmd.Items.get(9).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(13).Value_Str;
                    return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
                }

            case CMD_ID_check_if_str_compare_str_as_var_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String command1 = cmd.Items.get(9).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_by_var_do_command(var_left, s_compare, var_right, command1, is_command2 = false, command2);
                }
            case CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String command1 = cmd.Items.get(9).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(13).Value_Str;
                    return check_var_by_var_do_command(var_left, s_compare, var_right, command1, is_command2 = true, command2);
                }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: var exists print/do command">
            case CMD_ID_check_if_str_exists_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String str1 = cmd.Items.get(5).Value_Str;
                    boolean is_str2;
                    String str2 = "";
                    return check_var_exists_print(var_left, str1, is_str2 = false, str2);
                }
            case CMD_ID_check_if_str_exists_print_str_else_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String str1 = cmd.Items.get(5).Value_Str;
                    boolean is_str2;
                    String str2 = cmd.Items.get(8).Value_Str;
                    return check_var_exists_print(var_left, str1, is_str2 = true, str2);
                }

            case CMD_ID_check_if_str_exists_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String command1 = cmd.Items.get(6).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_exists_do_command(var_left, command1, is_command2 = false, command2);
                }
            case CMD_ID_check_if_str_exists_do_command_str_else_do_command_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String command1 = cmd.Items.get(6).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(10).Value_Str;
                    return check_var_exists_do_command(var_left, command1, is_command2 = true, command2);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
            case CMD_ID_check_label_str:
                if (is_debug) {
                    return true;
                } else {
                    String label = cmd.Items.get(2).Value_Str;
                    return check_label(label);
                }
            case CMD_ID_check_goto_label:
                if (is_debug) {
                    return true;
                } else {
                    String label = cmd.Items.get(2).Value_Str;
                    return check_goto_label(label);
                }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Print Str">
            case CMD_ID_check_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String str = cmd.Items.get(2).Value_Str;
                    return check_print_str(str);
                }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
            case CMD_ID_check_if_str_compare_int_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String label1 = cmd.Items.get(6).Value_Str;
                    boolean is_label2;
                    String label2 = "";
                    return check_var_by_int_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = false, label2);
                }
            case CMD_ID_check_if_str_compare_int_goto_str_else_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    //int var_right_value = 0;
                    //Int32.TryParse(cmd.Items.get(4).Value_Str, out var_right_value);
                    int var_right_value = Str_To_Int(cmd.Items.get(4).Value_Str);
                    String label1 = cmd.Items.get(6).Value_Str;
                    boolean is_label2;
                    String label2 = cmd.Items.get(9).Value_Str;
                    return check_var_by_int_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = true, label2);
                }

            case CMD_ID_check_if_str_compare_str_as_value_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String label1 = cmd.Items.get(8).Value_Str;
                    boolean is_label2;
                    String label2 = "";
                    return check_var_by_str_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = false, label2);
                }
            case CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String label1 = cmd.Items.get(8).Value_Str;
                    boolean is_label2;
                    String label2 = cmd.Items.get(11).Value_Str;
                    return check_var_by_str_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = true, label2);
                }

            case CMD_ID_check_if_str_compare_str_as_var_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String label1 = cmd.Items.get(8).Value_Str;
                    boolean is_label2;
                    String label2 = "";
                    return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = false, label2);
                }
            case CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right = Var_Name_Without_Point_Get(cmd.Items.get(4).Value_Str);
                    String label1 = cmd.Items.get(8).Value_Str;
                    boolean is_label2;
                    String label2 = cmd.Items.get(11).Value_Str;
                    return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = true, label2);
                }
            // </editor-fold>
            }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        String Prefix = "Check";
        values_map.put(Prefix + ".Count_Total", Integer.toString(Count_Total));
        values_map.put(Prefix + ".Count_Passed", Integer.toString(Count_Passed));
        values_map.put(Prefix + ".Count_Failed", Integer.toString(Count_Failed));
    }

}
