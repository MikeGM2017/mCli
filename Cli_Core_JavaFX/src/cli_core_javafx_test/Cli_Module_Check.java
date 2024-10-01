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

    private final int CMD_ID_print_str = 6; // private final int CMD_ID_check_print_str
    private final int CMD_ID_println_str = 7; // private final int CMD_ID_check_println_str

    private final int CMD_ID_check_label_str = 8;
    private final int CMD_ID_check_goto_label = 9;

    private final int CMD_ID_check_if_var_exists_command = 10;
    private final int CMD_ID_check_if_var_exists_command1_else_command2 = 11;

    private final int CMD_ID_check_if_var_compare_int_command = 12; // compare: == / != / ... / & / | / && / ||
    private final int CMD_ID_check_if_var_compare_int_command1_else_command2 = 13; // compare: == / != / ... / & / | / && / ||

    private final int CMD_ID_check_if_var_compare_str_command = 14; // compare: == / != / ... str: .v / int / "str"
    private final int CMD_ID_check_if_var_compare_str_command1_else_command2 = 15; // compare: == / != / ... str: .v / int / "str"

    private final int CMD_ID_LAST = 16;
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

    Cli_Module_Check(Cli_Modules modules, Map<String, String> values_map,
            Str_Filter str_filter,
            Str_Get_Without_Commas str_without_commas,
            Cli_Output_JavaFX cli_output,
            Ref_Boolean cmd_script_stop,
            Ref_String script_command_str, Ref_String script_label_str,
            Do_Abstract do_command_object) {
        super("Check");

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
            // check map print <.var>
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_map_print_by_filter);
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

        // <editor-fold defaultstate="collapsed" desc="Print Str">
        {
            // check print str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_print_str);
            cmd.Text_Set("print <str>");
            cmd.Help_Set("print <str>");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("print", "print"));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "str"));

            Cmd_Add(cmd);
        }
        {
            // check println str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_println_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_label_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_goto_label);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_exists_command);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_exists_command1_else_command2);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_compare_int_command);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_compare_int_command1_else_command2);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_compare_str_command);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_check_if_var_compare_str_command1_else_command2);
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

    boolean Char_Is_Digit(char c) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        return false;
    }

    boolean Char_Is_Digit_Or_Plus_Or_Minus(char c) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        if (c == '+') {
            return true;
        }
        if (c == '-') {
            return true;
        }
        return false;
    }

    boolean Str_Is_Int(String s) {
        if (s.length() == 0) {
            return false; // Case: empty String is not digit
        }
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (i == 0) {
                if (!Char_Is_Digit_Or_Plus_Or_Minus(c)) {
                    return false;
                }
            } else if (!Char_Is_Digit(c)) {
                return false;
            }
        }
        return true;
    }

    Local_Compare_Result Compare_Values_Str_Or_Int(String var_left_value, String s_compare, String var_right_value) {
        Local_Compare_Result cmp_res = Local_Compare_Result.CMP_ERROR;

        if (Str_Is_Int(var_left_value) && Str_Is_Int(var_right_value)) {
            int var_left_value_int = Str_To_Int(Str_Without_Commas.Get(var_left_value));
            int var_right_value_int = Str_To_Int(Str_Without_Commas.Get(var_right_value));
            cmp_res = Compare_Values_Int(var_left_value_int, s_compare, var_right_value_int);
        } else {
            cmp_res = Compare_Values_Str(Str_Without_Commas.Get(var_left_value), s_compare, Str_Without_Commas.Get(var_right_value));
        }

        return cmp_res;
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
    // <editor-fold defaultstate="collapsed" desc="Compare_Values: int/str">
    Local_Compare_Result Compare_Values_Int(int var_left_value_int, String s_compare, int var_right_value_int) {
        Local_Compare_Result cmp_res = Local_Compare_Result.CMP_FALSE;
        if (null != s_compare) {
            switch (s_compare) {
                case "==":
                    if (var_left_value_int == var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "!=":
                    if (var_left_value_int != var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<":
                    if (var_left_value_int < var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">":
                    if (var_left_value_int > var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "<=":
                    if (var_left_value_int <= var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case ">=":
                    if (var_left_value_int >= var_right_value_int) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "&":
                    if ((var_left_value_int & var_right_value_int) != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "|":
                    if ((var_left_value_int | var_right_value_int) != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "&&":
                    if (var_left_value_int != 0 && var_right_value_int != 0) {
                        cmp_res = Local_Compare_Result.CMP_TRUE;
                    }
                    break;
                case "||":
                    if (var_left_value_int != 0 || var_right_value_int != 0) {
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

    // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
    boolean check_label(String label) {
        return Do_Label(label);
    }

    boolean check_goto_label(String label) {
        return Do_Goto_Label(label);
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Print Str">
    boolean check_print_str(String s, boolean is_newline) {
        Cli_Output.Output_Str(Str_Without_Commas.Get(s));
        if (is_newline) {
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Check if: var exists do command">
    boolean check_var_exists_do_command(String var_left, String command1, boolean is_command2, String command2, Str_Filter str_filter) {
        boolean found = false;
        for (Map.Entry<String, String> item : Values_Map.entrySet()) {
            if (str_filter.Is_Match(var_left, item.getKey())) {
                found = true;
                break;
            }
        }
        if (found) {
            Do_Command(command1);
        } else if (is_command2) {
            Do_Command(command2);
        }
        return true;
    }

    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Check if: var compare var/int/str do command">
    boolean check_var_by_str_do_command(String var_left, String s_compare, String var_right, String command1, boolean is_command2, String command2) {
        boolean var_left_found = Values_Map.containsKey(var_left);

        String var_right_value = "";
        boolean var_right_found = false;
        if (var_right.length() > 0 && var_right.charAt(0) == '.') {
            var_right_found = Values_Map.containsKey(Var_Name_Without_Point_Get(var_right));
            if (var_right_found) {
                var_right_value = Values_Map.get(Var_Name_Without_Point_Get(var_right));
                var_right_found = true; // Case: var_right . .var
            }
        } else {
            var_right_value = var_right;
            var_right_found = true; // Case: var_right . int/str
        }

        if (var_left_found && var_right_found) {
            String var_left_value = Values_Map.get(var_left);

            Local_Compare_Result cmp_res = Compare_Values_Str_Or_Int(var_left_value, s_compare, var_right_value);

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
                    String var_filter = "*";
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
            // <editor-fold defaultstate="collapsed" desc="Print Str">
            case CMD_ID_print_str:
                if (is_debug) {
                    return true;
                } else {
                    String str = cmd.Items.get(1).Value_Str;
                    boolean is_newline;
                    return check_print_str(str, is_newline = false);
                }
            case CMD_ID_println_str:
                if (is_debug) {
                    return true;
                } else {
                    String str = cmd.Items.get(1).Value_Str;
                    boolean is_newline;
                    return check_print_str(str, is_newline = true);
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
            // <editor-fold defaultstate="collapsed" desc="Check if: var exists do command">
            case CMD_ID_check_if_var_exists_command:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String command1 = cmd.Items.get(4).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_exists_do_command(var_left, command1, is_command2 = false, command2, Str_Filter);
                }
            case CMD_ID_check_if_var_exists_command1_else_command2:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String command1 = cmd.Items.get(4).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(6).Value_Str;
                    return check_var_exists_do_command(var_left, command1, is_command2 = true, command2, Str_Filter);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Check if: var compare var/int/str do command">
            case CMD_ID_check_if_var_compare_int_command:
            case CMD_ID_check_if_var_compare_str_command:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str;
                    String command1 = cmd.Items.get(5).Value_Str;
                    boolean is_command2;
                    String command2 = "";
                    return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
                }
            case CMD_ID_check_if_var_compare_int_command1_else_command2:
            case CMD_ID_check_if_var_compare_str_command1_else_command2:
                if (is_debug) {
                    return true;
                } else {
                    String var_left = Var_Name_Without_Point_Get(cmd.Items.get(2).Value_Str);
                    String s_compare = cmd.Items.get(3).Value_Str;
                    String var_right_value = cmd.Items.get(4).Value_Str; //@Warning: Without Var_Name_Without_Point_Get(...) - may be .var/int/str
                    String command1 = cmd.Items.get(5).Value_Str;
                    boolean is_command2;
                    String command2 = cmd.Items.get(7).Value_Str;
                    return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
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
