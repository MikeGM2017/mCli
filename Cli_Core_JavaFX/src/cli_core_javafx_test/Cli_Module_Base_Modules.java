/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.List;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module_Base_Modules extends Cli_Module {

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;

    protected Str_Filter Str_Filter;

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_modules = 1;
    private final int CMD_ID_modules_by_filter = 2;
    private final int CMD_ID_modules_by_filter_print = 3;

    private final int CMD_ID_LAST = 4;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Modules(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
            Str_Filter str_filter, Cli_Output_JavaFX cli_output) {
        super("Base Modules");
        User_Privilege = user_privilege;
        Modules = modules;
        Str_Filter = str_filter;
        Cli_Output = cli_output;
        {
            // modules
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_modules);
            cmd.Text_Set("modules");
            cmd.Help_Set("modules print (all)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("modules", "modules print (all)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name>
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_modules_by_filter);
            cmd.Text_Set("modules <module_name>");
            cmd.Help_Set("modules print (by filter)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules print (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name> print
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_modules_by_filter_print);
            cmd.Text_Set("modules <module_name> print");
            cmd.Help_Set("modules print (by filter)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd.Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
            Cmd_Add(cmd);
        }
    }
    
    protected boolean modules_by_filter_print(String module_filter, Str_Filter str_filter) {
        Cli_Output.Output_NewLine();
        boolean found = false;
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module module_ptr = Modules.Get(module);
            if (module_ptr != null) {
                String module_name = module_ptr.Name_Get();
                String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                if (str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                    Cli_Output.Output_Str(module_name);
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

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_modules:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = "*";
                    return modules_by_filter_print(module_filter, Str_Filter);
                }
            case CMD_ID_modules_by_filter:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = cmd.Items.get(1).Value_Str;
                    return modules_by_filter_print(module_filter, Str_Filter);
                }
            case CMD_ID_modules_by_filter_print:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = cmd.Items.get(1).Value_Str;
                    return modules_by_filter_print(module_filter, Str_Filter);
                }
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
