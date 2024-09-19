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
public class Cli_Module_Base_Modules extends Cli_Module {

    protected String Cli_Version = "";

    protected Cli_Modules Modules;

    protected Str_Filter Str_Filter;

    protected Cli_Input_JavaFX Cli_Input;

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_modules = 1;
    private final int CMD_ID_modules_by_filter = 2;
    private final int CMD_ID_modules_by_filter_print = 3;
    private final int CMD_ID_modules_by_filter_print_verbose = 4;

    private final int CMD_ID_LAST = 4;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Modules(String cli_version, Cli_Modules modules,
            Str_Filter str_filter, Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output) {
        super("Base Modules");

        Version = "0.02";

        Cli_Version = cli_version;
        Modules = modules;
        Str_Filter = str_filter;
        Cli_Input = cli_input;
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
        {
            // modules <module_name> print verbose
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_modules_by_filter_print_verbose);
            cmd.Text_Set("modules <module_name> print");
            cmd.Help_Set("modules print (by filter)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd.Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "modules print (by filter) verbose"));
            Cmd_Add(cmd);
        }
    }

    void processors_print() {
        Ref_Cli_Cmd_Privilege_ID user_privilege = new Ref_Cli_Cmd_Privilege_ID(Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF);
        Cli_Modules modules = new Cli_Modules();
        List<Level_Description> levels = new ArrayList<>();
        Cmd_Token_Parser parser = new Cmd_Token_Parser();
        String str_rem = "$";
        Cli_CMD_Processor CMD_Processor = new Cli_CMD_Processor(user_privilege, modules, levels, parser, Cli_Input, Cli_Output, str_rem);
        boolean log_is_active = false;
        Cli_TAB_Processor TAB_Processor = new Cli_TAB_Processor(user_privilege, modules, levels, parser, Cli_Input, Cli_Output, str_rem, log_is_active);

        {
            String type = CMD_Processor.Type_Get();
            String version = CMD_Processor.Version_Get();
            Cli_Output.Output_Str(type);
            Cli_Output.Output_Str(" V");
            Cli_Output.Output_Str(version);
            Cli_Output.Output_NewLine();
        }

        {
            String type = TAB_Processor.Type_Get();
            String version = TAB_Processor.Version_Get();
            Cli_Output.Output_Str(type);
            Cli_Output.Output_Str(" V");
            Cli_Output.Output_Str(version);
            Cli_Output.Output_NewLine();
        }

        Cli_Output.Output_NewLine();
    }

    void filters_print() {
        String type = Str_Filter.Type_Get();
        String version = Str_Filter.Version_Get();
        Cli_Output.Output_Str(type);
        Cli_Output.Output_Str(" V");
        Cli_Output.Output_Str(version);
        Cli_Output.Output_NewLine();
        Cli_Output.Output_NewLine();
    }

    void cmd_items_print(String module_filter, Str_Filter str_filter) {
        List<Cmd_Item_Base> items = new ArrayList<>();
        List<String> words = new ArrayList<>();
        items.add(new Cmd_Item_Base("", ""));
        items.add(new Cmd_Item_Date("", ""));
        items.add(new Cmd_Item_DateTime("", ""));
        items.add(new Cmd_Item_Time("", ""));
        items.add(new Cmd_Item_EQU("", ""));
        items.add(new Cmd_Item_EQU_Range("", "", words));
        items.add(new Cmd_Item_IP4("", ""));
        items.add(new Cmd_Item_IP6("", ""));
        items.add(new Cmd_Item_Int("", ""));
        items.add(new Cmd_Item_Int_List(1, 8, "", ""));
        items.add(new Cmd_Item_Int_Range(1, 8, "", ""));
        items.add(new Cmd_Item_MAC("", ""));
        //items.add(new Cmd_Item_Point_Var_Name("", ""));
        items.add(new Cmd_Item_Rem("", ""));
        items.add(new Cmd_Item_Str("", ""));
        //items.add(new Cmd_Item_Str_Esc("", ""));
        items.add(new Cmd_Item_Word("", ""));
        items.add(new Cmd_Item_Word_List("", "", words));
        items.add(new Cmd_Item_Word_Range("", "", words));
        //items.add(new Cmd_Item_Assignment_Mark("", ""));

        boolean found = false;
        for (int i = 0; i < items.size(); i++) {
            Cmd_Item_Base item = items.get(i);
            String type = item.Type_Get();
            if (str_filter.Is_Match(module_filter, type)) {
                found = true;
                break;
            }
        }

        if (found) {
            StringBuilder s_str = new StringBuilder();
            s_str.append("Cmd Items[").append(items.size()).append("]:");
            Cli_Output.Output_Str(s_str.toString());
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();
            for (int i = 0; i < items.size(); i++) {
                Cmd_Item_Base item = items.get(i);
                String type = item.Type_Get();
                if (str_filter.Is_Match(module_filter, type)) {
                    String version = item.Version_Get();
                    Cli_Output.Output_Str(type);
                    Cli_Output.Output_Str(" V");
                    Cli_Output.Output_Str(version);
                    Cli_Output.Output_NewLine();
                }
            }
        }
    }

    protected boolean modules_by_filter_print(String module_filter, Str_Filter str_filter, boolean is_verbose) {
        Cli_Output.Output_NewLine();
        boolean found = false;
        if (is_verbose) {
            StringBuilder sb = new StringBuilder();
            sb.append("Modules[").append(Modules.Get_Size()).append("]:");
            Cli_Output.Output_Str(sb.toString());
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();
        }
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module module_ptr = Modules.Get(module);
            if (module_ptr != null) {
                String module_name = module_ptr.Name_Get();
                String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                if (str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                    if (!is_verbose) {
                        Cli_Output.Output_Str(module_name);
                    } else {
                        Cli_Output.Output_Str(module_name + " V" + module_ptr.Version_Get());
                    }
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
                    boolean is_verbose;
                    return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                }
            case CMD_ID_modules_by_filter:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = cmd.Items.get(1).Value_Str;
                    boolean is_verbose;
                    return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                }
            case CMD_ID_modules_by_filter_print:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = cmd.Items.get(1).Value_Str;
                    boolean is_verbose;
                    return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                }
            case CMD_ID_modules_by_filter_print_verbose:
                if (is_debug) {
                    return true;
                }
                 {
                    String module_filter = cmd.Items.get(1).Value_Str;
                    boolean is_verbose;
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Cli V" + Cli_Version);
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_NewLine();
                    processors_print();
                    filters_print();
                    cmd_items_print(module_filter, Str_Filter);
                    return modules_by_filter_print(module_filter, Str_Filter, is_verbose = true);
                }
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
