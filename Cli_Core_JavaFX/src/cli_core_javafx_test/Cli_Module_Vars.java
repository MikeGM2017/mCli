/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module_Vars extends Cli_Module {

    protected Cli_Modules Modules;
    protected Map<String, String> Values_Map;
    protected Str_Filter Str_Filter;
    protected Str_Get_Without_Commas Str_Without_Commas;
    protected Cli_Output_JavaFX Cli_Output;

    protected char C_Single;
    protected char C_Multy;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_point_var_name = 1;
    private final int CMD_ID_point_var_name_assign_str = 2;
    private final int CMD_ID_point_var_name_assign_point_var_name = 3;

    private final int CMD_ID_point_var_name_inc = 4;

    private final int CMD_ID_point_var_name_delete = 5;

    private final int CMD_ID_LAST = 6;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Vars(Cli_Modules modules, Map<String, String> values_map, Str_Filter str_filter,
            Str_Get_Without_Commas str_without_commas,
            Cli_Output_JavaFX cli_output) {
        this(modules, values_map, str_filter, str_without_commas, cli_output, '?', '*');
    }

    public Cli_Module_Vars(Cli_Modules modules, Map<String, String> values_map, Str_Filter str_filter,
            Str_Get_Without_Commas str_without_commas,
            Cli_Output_JavaFX cli_output,
            char c_single, char c_multy) {
        super("Vars");

        Version = "0.03";

        Modules = modules;
        Values_Map = values_map;
        Str_Filter = str_filter;
        Str_Without_Commas = str_without_commas;
        Cli_Output = cli_output;
        C_Single = c_single;
        C_Multy = c_multy;

        // <editor-fold defaultstate="collapsed" desc="Vars: get/set">
        {
            // get
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_point_var_name);
            cmd.Text_Set(".<var_name>");
            cmd.Help_Set("get <var_name> value (by filter, .* - get all vars)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name (by filter)", C_Single, C_Multy));
            Cmd_Add(cmd);
        }

        {
            // assign int @Attention: Must be before CMD_ID_point_var_name_assign_str
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_point_var_name_assign_point_var_name);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_point_var_name_assign_str);
            cmd.Text_Set(".<var_name> = <str>");
            cmd.Help_Set("set <var_name> to <str>");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd.Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "new value"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Vars: inc">
        {
            // inc @Attention: increment as integer only (String converted to "0")
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_point_var_name_inc);
            cmd.Text_Set(".<var_name> inc");
            cmd.Help_Set("increment <var_name>");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd.Item_Add(new Cmd_Item_Word("inc", "increment"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Vars: delete">
        {
            // delete
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_point_var_name_delete);
            cmd.Text_Set(".<var_name> delete");
            cmd.Help_Set("delete <var_name> (by filter, .* - delete all vars)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd.Item_Add(new Cmd_Item_Word("delete", "delete (by filter)"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

    }

    boolean var_get(String point_var_name_str) {
        String var_name = point_var_name_str.substring(1);
        boolean found = false;
        for (Map.Entry<String, String> item : Values_Map.entrySet()) {
            String item_var_name = item.getKey();
            if (Str_Filter.Is_Match(var_name, item_var_name)) {
                Cli_Output.Output_Str(item_var_name + " = \"" + item.getValue() + "\"");
                Cli_Output.Output_NewLine();
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    Map.Entry<String, String> Values_Map_Find_By_Var_Name(String var_name_arg) {
        for (Map.Entry<String, String> item : Values_Map.entrySet()) {
            String item_var_name = "." + item.getKey();
            if (var_name_arg.equals(item_var_name)) {
                return item;
            }
        }
        return null;
    }

    boolean var_set_str(String point_var_name_str, String value_str) {
        String var_name = point_var_name_str.substring(1);
        String value_str_without_commas = Str_Without_Commas.Get(value_str);
        Values_Map.put(var_name, value_str_without_commas);
        Cli_Output.Output_Str(var_name + " = \"" + value_str_without_commas + "\"");
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean var_set_var(String point_var1_name_str, String point_var2_name_str) {
        Map.Entry<String, String> iter2 = Values_Map_Find_By_Var_Name(point_var2_name_str);
        if (iter2 != null) {
            String var1_name = point_var1_name_str.substring(1);
            String var2_value = iter2.getValue();
            Values_Map.put(var1_name, var2_value);
            Cli_Output.Output_Str(var1_name + " = \"" + var2_value + "\"");
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_Str(point_var2_name_str + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    boolean var_inc(String point_var_name_str) {
        String var_name = point_var_name_str.substring(1);
        boolean found = false;
        for (Map.Entry<String, String> item : Values_Map.entrySet()) {
            String item_var_name = item.getKey();
            if (var_name.equals(item_var_name)) {
                int item_var_value_int_new;
                try {
                    item_var_value_int_new = Integer.parseInt(item.getValue()) + 1;
                } catch (NumberFormatException e) {
                    item_var_value_int_new = 1;
                }
                Values_Map.put(item_var_name, Integer.toString(item_var_value_int_new));
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    boolean var_delete(String point_var_name_str) {
        String var_name = point_var_name_str.substring(1);
        boolean found = false;
        Map<String, String> map_new = new HashMap<>();
        for (Map.Entry<String, String> item : Values_Map.entrySet()) {
            String item_var_name = item.getKey();
            if (Str_Filter.Is_Match(var_name, item_var_name)) {
                found = true;
            }
        }
        if (found) {
            for (Map.Entry<String, String> item : Values_Map.entrySet()) {
                String item_var_name = item.getKey();
                if (!Str_Filter.Is_Match(var_name, item_var_name)) {
                    map_new.put(item.getKey(), item.getValue());
                }
            }
            Values_Map.clear();
            Values_Map.putAll(map_new);
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {

            // <editor-fold defaultstate="collapsed" desc="Vars: get/set">
            case CMD_ID_point_var_name:
                if (is_debug) {
                    return true;
                } else {
                    String point_var_name_str = cmd.Items.get(0).Value_Str;
                    return var_get(point_var_name_str);
                }

            case CMD_ID_point_var_name_assign_str:
                if (is_debug) {
                    return true;
                } else {
                    String point_var_name_str = cmd.Items.get(0).Value_Str;
                    String value_str = cmd.Items.get(2).Value_Str;
                    return var_set_str(point_var_name_str, value_str);
                }
            case CMD_ID_point_var_name_assign_point_var_name:
                if (is_debug) {
                    return true;
                } else {
                    String point_var1_name_str = cmd.Items.get(0).Value_Str;
                    String point_var2_name_str = cmd.Items.get(2).Value_Str;
                    return var_set_var(point_var1_name_str, point_var2_name_str);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Vars: inc">
            case CMD_ID_point_var_name_inc:
                if (is_debug) {
                    return true;
                } else {
                    String point_var_name_str = cmd.Items.get(0).Value_Str;
                    return var_inc(point_var_name_str);
                }

            // </editor-fold>
            // <editor-fold defaultstate="collapsed" desc="Vars: delete">
            case CMD_ID_point_var_name_delete:
                if (is_debug) {
                    return true;
                } else {
                    String point_var_name_str = cmd.Items.get(0).Value_Str;
                    return var_delete(point_var_name_str);
                }

            // </editor-fold>
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
