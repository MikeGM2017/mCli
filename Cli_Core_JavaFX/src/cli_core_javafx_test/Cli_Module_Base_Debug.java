/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module_Base_Debug extends Cli_Module {

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;

    protected List<Level_Description> Levels;

    protected Cli_CMD_Processor CMD_Processor;

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_debug_cli = 1;
    private final int CMD_ID_debug_cli_counts = 2;
    private final int CMD_ID_debug_cli_verbose = 3;
    private final int CMD_ID_debug_cli_verbose_failed = 4;

    private final int CMD_ID_LAST = 5;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Debug(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
            List<Level_Description> levels, Cli_CMD_Processor cmd_processor,
            Cli_Output_JavaFX cli_output) {
        super("Base Debug");

        Version = "0.02";

        User_Privilege = user_privilege;
        Modules = modules;
        Levels = levels;
        CMD_Processor = cmd_processor;
        Cli_Output = cli_output;
        {
            // debug cli
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_debug_cli);
            cmd.Text_Set("debug cli");
            cmd.Help_Set("debug cli");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd.Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            Cmd_Add(cmd);
        }
        {
            // debug cli
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_debug_cli_counts);
            cmd.Text_Set("debug cli counts");
            cmd.Help_Set("debug cli counts");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd.Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd.Item_Add(new Cmd_Item_Word("counts", "debug cli counts"));
            Cmd_Add(cmd);
        }
        {
            // debug cli verbose
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_debug_cli_verbose);
            cmd.Text_Set("debug cli verbose");
            cmd.Help_Set("debug cli verbose");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd.Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "show all information"));
            Cmd_Add(cmd);
        }
        {
            // debug cli verbose failed
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_debug_cli_verbose_failed);
            cmd.Text_Set("debug cli verbose failed");
            cmd.Help_Set("debug cli verbose failed");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd.Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "show all information"));
            cmd.Item_Add(new Cmd_Item_Word("failed", "show all information (failed only)"));
            Cmd_Add(cmd);
        }
    }

    void Debug_Cli_Modules(boolean is_counts, boolean is_verbose, boolean is_failed_only,
            Ref_Int total_count_cmd_id,
            Ref_Int total_count,
            Ref_Int total_count_checked,
            Ref_Int total_count_passed,
            Ref_Int total_count_failed) {
        boolean is_debug = true;
        Ref_Boolean debug_res = new Ref_Boolean(false);
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module module_ptr = Modules.Get(module);
            total_count_cmd_id.Value += module_ptr.Cmd_ID_Count_Get();
            if (is_counts) {
                StringBuilder sb = new StringBuilder();
                sb.append("Module: ");
                sb.append(module_ptr.Name_Get());
                sb.append(" id_cnt=");
                sb.append(module_ptr.Cmd_ID_Count_Get());
                Cli_Output.Output_Str(sb.toString());
                Cli_Output.Output_NewLine();
            }
            total_count.Value += module_ptr.Cmd_Count_Get();
            if (is_counts) {
                StringBuilder sb = new StringBuilder();
                sb.append("Module: ");
                sb.append(module_ptr.Name_Get());
                sb.append(" cmd_cnt=");
                sb.append(module_ptr.Cmd_Count_Get());
                Cli_Output.Output_Str(sb.toString());
                Cli_Output.Output_NewLine();
            }
            for (int cmd = 0; cmd < module_ptr.Module_Cmd_List.size(); cmd++) {
                Cli_Cmd cmd_ptr = module_ptr.Module_Cmd_List.get(cmd);
                String s = "";
                for (int item = 0; item < cmd_ptr.Items.size(); item++) {
                    Cmd_Item_Base item_ptr = cmd_ptr.Items.get(item);
                    if (item == 0) {
                        s = item_ptr.Debug_Value_Get();
                    } else {
                        s += " " + item_ptr.Debug_Value_Get();
                    }
                }
                String level = cmd_ptr.Level_Get();
                Levels.clear();
                String s_trim = s.trim();
                Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, s_trim);
                if (level.length() == 0) {
                    debug_res.Value = false;
                    CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                    if (is_verbose) {
                        if (!is_failed_only || (is_failed_only && !debug_res.Value)) {
                            Cli_Output.Output_Str(s + " - " + (debug_res.Value ? "Ok" : "Failed"));
                            Cli_Output.Output_NewLine();
                        }
                    }
                } else {
                    Levels.add(new Level_Description(level));
                    debug_res.Value = false;
                    CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                    if (is_verbose) {
                        if (!is_failed_only || (is_failed_only && !debug_res.Value)) {
                            Cli_Output.Output_Str("[" + cmd_ptr.Level_Get() + "] " + s + " - " + (debug_res.Value ? "Ok" : "Failed"));
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                total_count_checked.Value++;
                if (debug_res.Value) {
                    total_count_passed.Value++;
                } else {
                    total_count_failed.Value++;
                }
            }
        }
    }

    boolean debug_cli(boolean is_counts, boolean is_verbose, boolean is_failed_only) {

        List<Level_Description> Levels_Prev = new ArrayList<>(Levels); // @Warning: Save Levels

        Ref_Int total_count_cmd_id = new Ref_Int(0);
        Ref_Int total_count = new Ref_Int(0);
        Ref_Int total_count_checked = new Ref_Int(0);
        Ref_Int total_count_passed = new Ref_Int(0);
        Ref_Int total_count_failed = new Ref_Int(0);
        Cli_Output.Output_NewLine();
        Debug_Cli_Modules(is_counts, is_verbose, is_failed_only,
                total_count_cmd_id,
                total_count,
                total_count_checked,
                total_count_passed,
                total_count_failed);
        StringBuilder sb = new StringBuilder();
        sb.append("Debug Cli Result:");
        sb.append(" id_cnt:");
        sb.append(total_count_cmd_id.Value);
        sb.append(" total:");
        sb.append(total_count.Value);
        sb.append(" checked:");
        sb.append(total_count_checked.Value);
        sb.append(" passed:");
        sb.append(total_count_passed.Value);
        sb.append(" failed:");
        sb.append(total_count_failed.Value);
        Cli_Output.Output_Str(sb.toString());
        Cli_Output.Output_NewLine();

        Levels = new ArrayList<>(Levels_Prev); // @Warning: Restore Levels

        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_debug_cli:
                if (is_debug) {
                    return true;
                } else {
                    boolean is_counts = false;
                    boolean is_verbose = false;
                    boolean is_failed_only = false;
                    return debug_cli(is_counts, is_verbose, is_failed_only);
                }
            case CMD_ID_debug_cli_counts:
                if (is_debug) {
                    return true;
                } else {
                    boolean is_counts = true;
                    boolean is_verbose = false;
                    boolean is_failed_only = false;
                    return debug_cli(is_counts, is_verbose, is_failed_only);
                }
            case CMD_ID_debug_cli_verbose:
                if (is_debug) {
                    return true;
                } else {
                    boolean is_counts = false;
                    boolean is_verbose = true;
                    boolean is_failed_only = false;
                    return debug_cli(is_counts, is_verbose, is_failed_only);
                }
            case CMD_ID_debug_cli_verbose_failed:
                if (is_debug) {
                    return true;
                } else {
                    boolean is_counts = false;
                    boolean is_verbose = true;
                    boolean is_failed_only = true;
                    return debug_cli(is_counts, is_verbose, is_failed_only);
                }

        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
