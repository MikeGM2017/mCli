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
public class Cli_Module_Base_Help extends Cli_Module {

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;

    protected Str_Filter Help_Str_Filter;

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_help_H = 1;
    private final int CMD_ID_help = 2;
    private final int CMD_ID_help_full = 3;
    private final int CMD_ID_help_full_verbose = 4;
    private final int CMD_ID_help_command = 5;
    private final int CMD_ID_help_command_verbose = 6;

    private final int CMD_ID_help_module_module_name = 7;
    private final int CMD_ID_help_module_module_name_verbose = 8;

    private final int CMD_ID_LAST = 9;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Help(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
            Str_Filter help_str_filter, Cli_Output_JavaFX cli_output) {
        super("Base Help");
        User_Privilege = user_privilege;
        Modules = modules;
        Help_Str_Filter = help_str_filter;
        Cli_Output = cli_output;

        {
            // H - help
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_H);
            cmd.Text_Set("H");
            cmd.Help_Set("show help");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("H", "show help"));
            Cmd_Add(cmd);
        }
        {
            // help
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help);
            cmd.Text_Set("help");
            cmd.Help_Set("show help");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            Cmd_Add(cmd);
        }

        {
            // help full
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_full);
            cmd.Text_Set("help full");
            cmd.Help_Set("show all commands");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Word("full", "show all commands"));
            Cmd_Add(cmd);
        }
        {
            // help full verbose
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_full_verbose);
            cmd.Text_Set("help full verbose");
            cmd.Help_Set("show all commands with arguments information");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Word("full", "show all commands"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // help "<command>"
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_command);
            cmd.Text_Set("help \"<command>\"");
            cmd.Help_Set("show selected commands (by filter)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // help "<command>" verbose
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_command_verbose);
            cmd.Text_Set("help \"<command>\" verbose");
            cmd.Help_Set("show selected commands (by filter) with arguments information");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information (by filter)"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // help module "<module_name>"
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_module_module_name);
            cmd.Text_Set("help module \"<module_name>\"");
            cmd.Help_Set("show module commands (modules by filter)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Word("module", "show module commands (modules by filter)"));
            cmd.Item_Add(new Cmd_Item_Str("\"<module_name>\"", "modules about which need to obtain information (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // help module "<module_name>" verbose
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_help_module_module_name_verbose);
            cmd.Text_Set("help module \"<module_name>\" verbose");
            cmd.Help_Set("show module commands (modules by filter) with arguments information");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd.Item_Add(new Cmd_Item_Word("module", "show module commands (modules by filter)"));
            cmd.Item_Add(new Cmd_Item_Str("\"<module_name>\"", "modules about which need to obtain information (by filter)"));
            cmd.Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

    }

    protected boolean HELP_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, String level,
            boolean is_full, boolean is_module_full) {
        if (cmd_ptr != null && user_privilege.ordinal() <= cmd_ptr.Privilege_Get()) {
            if (is_full) {
                return true;
            }
            if (is_module_full) {
                return true;
            }
            if (cmd_ptr.Is_Global_Get()) {
                return true;
            }
            if (cmd_ptr.Level_Get() == level) {
                return true;
            }
        }
        return false;
    }

    protected int Help_Cli_Modules_Get_Len(int user_privilege, Cli_Modules modules,
            String level,
            boolean is_full, boolean is_verbose, boolean is_module_full,
            String module_filter, String command_filter, Str_Filter str_filter) {
        int len_max = 0;

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module module_ptr = modules.Get(module);
            String module_name = module_ptr.Name_Get();
            String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
            if (is_full || str_filter.Is_Match(module_filter, module_name)
                    || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                for (int cmd = 0; cmd < module_ptr.Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd cmd_ptr = module_ptr.Module_Cmd_List.get(cmd);
                    boolean is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level, is_full, is_module_full);
                    if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr.Items.get(0).Text_Get())) {
                        int len = 0;
                        if (level.length() == 0) {
                            int len_level = cmd_ptr.Level_Get().length();
                            if (len_level > 0) {
                                len += len_level + 3; // "[" + ... + "] " - OnHelp_CliModules(...)
                            }
                        }
                        len += cmd_ptr.Text_Get().length();
                        if (len_max < len) {
                            len_max = len;
                        }
                        if (is_verbose) {
                            for (int i = 0; i < cmd_ptr.Items.size(); i++) {
                                Cmd_Item_Base item = cmd_ptr.Items.get(i);
                                len = 1 + item.Text_Get().length(); // " " + ...
                                if (len_max < len) {
                                    len_max = len;
                                }
                            }
                        }
                    }
                }
            }
        }

        return len_max;
    }

    protected void Help_Cli_Modules_Print(int user_privilege, Cli_Modules modules,
            String level,
            boolean is_full, boolean is_verbose, boolean is_module_full,
            String module_filter, String command_filter, Str_Filter str_filter,
            int len_max, Ref_Int modules_count, Ref_Int commands_count,
            Cli_Output_JavaFX Cli_Output) {

        StringBuilder sb = new StringBuilder();

        //Cli_Output.Output_NewLine();
        sb.append('\n');

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module module_ptr = modules.Get(module);
            String module_name = module_ptr.Name_Get();
            String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
            if (is_full || str_filter.Is_Match(module_filter, module_name)
                    || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                modules_count.Value++;
                for (int cmd = 0; cmd < module_ptr.Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd cmd_ptr = module_ptr.Module_Cmd_List.get(cmd);
                    String s = "";
                    StringBuilder sb1 = new StringBuilder();
                    StringBuilder sb2 = new StringBuilder();
                    if (level.length() == 0) {
                        String s_level = cmd_ptr.Level_Get();
                        if (s_level.length() > 0) {
                            s += "[" + s_level + "] ";
                            sb1.append("[");
                            sb1.append(s_level);
                            sb1.append("] ");
                        }
                    }
                    s += cmd_ptr.Text_Get();
                    sb1.append(cmd_ptr.Text_Get());
                    boolean is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level, is_full, is_module_full);
                    if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr.Items.get(0).Text_Get())) {

                        int sb1_tail_len = len_max - sb1.toString().length();
                        if (sb1_tail_len < 0) {
                            sb1_tail_len = 0;
                        }
                        sb2.append(sb1.toString());
                        for (int i1 = 0; i1 < sb1_tail_len; i1++) {
                            sb2.append(' ');
                        }

                        sb2.append(" - ");
                        sb2.append(cmd_ptr.Help_Get());
                        //Cli_Output.Output_Str(sb2.str());
                        //Cli_Output.Output_NewLine();
                        sb.append(sb2.toString());
                        sb.append('\n');
                        commands_count.Value++;
                        if (is_verbose && cmd_ptr.Items.size() > 1) {
                            for (int i = 1; i < cmd_ptr.Items.size(); i++) {
                                Cmd_Item_Base item = cmd_ptr.Items.get(i);
                                StringBuilder sb3 = new StringBuilder();
                                StringBuilder sb4 = new StringBuilder();
                                sb3.append(" ");
                                sb3.append(item.Text_Get());

                                int sb3_tail_len = len_max - sb3.toString().length();
                                if (sb3_tail_len < 0) {
                                    sb3_tail_len = 0;
                                }
                                sb4.append(sb3.toString());
                                for (int i3 = 0; i3 < sb3_tail_len; i3++) {
                                    sb4.append(' ');
                                }

                                sb4.append(" - ");
                                sb4.append(item.Help_Get());
                                //Cli_Output.Output_Str(sb4.str());
                                //Cli_Output.Output_NewLine();
                                sb.append(sb4.toString());
                                sb.append('\n');
                            }
                        }
                    }
                }
            }
        }

        Cli_Output.Output_Str(sb.toString());

    }

    protected void help(String level, boolean is_full, boolean is_verbose, boolean is_module_full,
            String module_filter, String command_filter, Cli_Output_JavaFX Cli_Output) {
        Ref_Int modules_count = new Ref_Int(0);
        Ref_Int commands_count = new Ref_Int(0);
        int len_max = 0;
        int len;

        len = Help_Cli_Modules_Get_Len(User_Privilege.Value.ordinal(), Modules, level,
                is_full, is_verbose, is_module_full,
                module_filter, command_filter, Help_Str_Filter);
        if (len_max < len) {
            len_max = len;
        }

        Help_Cli_Modules_Print(User_Privilege.Value.ordinal(), Modules, level,
                is_full, is_verbose, is_module_full,
                module_filter, command_filter, Help_Str_Filter,
                len_max, modules_count, commands_count,
                Cli_Output);

        if (modules_count.Value == 0) {
            Cli_Output.Output_Str("modules \"");
            Cli_Output.Output_Str(module_filter);
            Cli_Output.Output_Str("\" - not found");
            Cli_Output.Output_NewLine();
        } else if (commands_count.Value == 0) {
            Cli_Output.Output_Str("commands \"");
            Cli_Output.Output_Str(command_filter);
            Cli_Output.Output_Str("\" - not found");
            Cli_Output.Output_NewLine();
        }

    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        Level_Description level = new Level_Description();
        String parameter = "";
        if (Levels.size() > 0) {
            level = Levels.get(Levels.size() - 1);
            parameter = level.Parameter;
        }
        switch (cmd_id) {
            case CMD_ID_help_H:
            case CMD_ID_help:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = false;
                    boolean is_verbose = false;
                    boolean is_module_full = false;
                    String module_filter = "*";
                    String command_filter = "*";
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;

            case CMD_ID_help_full:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = true;
                    boolean is_verbose = false;
                    boolean is_module_full = false;
                    String module_filter = "*";
                    String command_filter = "*";
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;
            case CMD_ID_help_full_verbose:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = true;
                    boolean is_verbose = true;
                    boolean is_module_full = false;
                    String module_filter = "*";
                    String command_filter = "*";
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;

            case CMD_ID_help_command:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = false;
                    boolean is_verbose = false;
                    boolean is_module_full = false;
                    String module_filter = "*";
                    String command_filter = cmd.Items.get(1).Value_Str;
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;
            case CMD_ID_help_command_verbose:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = false;
                    boolean is_verbose = true;
                    boolean is_module_full = false;
                    String module_filter = "*";
                    String command_filter = cmd.Items.get(1).Value_Str;
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;

            case CMD_ID_help_module_module_name:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = false;
                    boolean is_verbose = false;
                    boolean is_module_full = true;
                    String module_filter = cmd.Items.get(2).Value_Str;
                    String command_filter = "*";
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;
            case CMD_ID_help_module_module_name_verbose:
                if (is_debug) {
                    return true;
                }
                 {
                    boolean is_full = false;
                    boolean is_verbose = true;
                    boolean is_module_full = true;
                    String module_filter = cmd.Items.get(2).Value_Str;
                    String command_filter = "*";
                    help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                }
                return true;

            default:
                return false; // Not Implemented

        }

    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
