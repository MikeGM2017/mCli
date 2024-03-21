using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Help : Cli_Module
    {
        protected Ref_Cli_Cmd_Privilege_ID User_Privilege;

        protected Cli_Modules Modules;

        protected Str_Filter Help_Str_Filter;

        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_help_H,
            CMD_ID_help,
            CMD_ID_help_full,
            CMD_ID_help_full_verbose,
            CMD_ID_help_command,
            CMD_ID_help_command_verbose,

            CMD_ID_help_module_module_name,
            CMD_ID_help_module_module_name_verbose,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Help(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                Str_Filter help_str_filter,
                Cli_Output_CS cli_output) : base("Base Help")
        {
            User_Privilege = user_privilege;
            Modules = modules;
            Help_Str_Filter = help_str_filter;
            Cli_Output = cli_output;

            {
                // H - help
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_H);
                cmd.Text_Set("H");
                cmd.Help_Set("show help");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("H", "show help"));
                Cmd_Add(cmd);
            }
            {
                // help
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help);
                cmd.Text_Set("help");
                cmd.Help_Set("show help");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
                Cmd_Add(cmd);
            }

            {
                // help full
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_full);
                cmd.Text_Set("help full");
                cmd.Help_Set("show all commands");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
                cmd.Item_Add(new Cmd_Item_Word("full", "show all commands"));
                Cmd_Add(cmd);
            }
            {
                // help full verbose
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_full_verbose);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_command);
                cmd.Text_Set("help \"<command>\"");
                cmd.Help_Set("show selected commands (by filter)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("help", "show help"));
                cmd.Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information (by filter)"));
                Cmd_Add(cmd);
            }
            {
                // help "<command>" verbose
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_command_verbose);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_module_module_name);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_help_module_module_name_verbose);
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

        public virtual bool HELP_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, string level,
                bool is_full, bool is_module_full)
        {
            if (cmd_ptr != null && (int)user_privilege <= cmd_ptr.Privilege_Get())
            {
                if (is_full) return true;
                if (is_module_full) return true;
                if (cmd_ptr.Is_Global_Get()) return true;
                if (cmd_ptr.Level_Get() == level) return true;
            }
            return false;
        }

        protected int Help_Cli_Modules_Get_Len(int user_privilege, Cli_Modules modules,
                    String level,
                    bool is_full, bool is_verbose, bool is_module_full,
                    String module_filter, String command_filter, Str_Filter str_filter)
        {
            int len_max = 0;

            for (int module = 0; module < modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = modules.Get(module);
                String module_name = module_ptr.Name_Get();
                String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                if (is_full || str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas))
                {
                    for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                    {
                        Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                        bool is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level, is_full, is_module_full);
                        if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr.Items[0].Text_Get()))
                        {
                            int len = 0;
                            if (level.Length == 0)
                            {
                                int len_level = cmd_ptr.Level_Get().Length;
                                if (len_level > 0)
                                {
                                    len += len_level + 3; // "[" + ... + "] " - OnHelp_CliModules(...)
                                }
                            }
                            len += cmd_ptr.Text_Get().Length;
                            if (len_max < len)
                            {
                                len_max = len;
                            }
                            if (is_verbose)
                            {
                                for (int i = 0; i < cmd_ptr.Items.Count; i++)
                                {
                                    Cmd_Item_Base item = cmd_ptr.Items[i];
                                    len = 1 + item.Text_Get().Length; // " " + ...
                                    if (len_max < len)
                                    {
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
            bool is_full, bool is_verbose, bool is_module_full,
            String module_filter, String command_filter, Str_Filter str_filter,
            int len_max, Ref_Int modules_count, Ref_Int commands_count,
            Cli_Output_CS Cli_Output)
        {

            StringBuilder sb = new StringBuilder();

            //Cli_Output.Output_NewLine();
            sb.Append("\r\n");

            for (int module = 0; module < modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = modules.Get(module);
                String module_name = module_ptr.Name_Get();
                String module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                if (is_full || str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas))
                {
                    modules_count.Value++;
                    for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                    {
                        Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                        String s = "";
                        StringBuilder sb1 = new StringBuilder();
                        StringBuilder sb2 = new StringBuilder();
                        if (level.Length == 0)
                        {
                            String s_level = cmd_ptr.Level_Get();
                            if (s_level.Length > 0)
                            {
                                s += "[" + s_level + "] ";
                                sb1.Append("[");
                                sb1.Append(s_level);
                                sb1.Append("] ");
                            }
                        }
                        s += cmd_ptr.Text_Get();
                        sb1.Append(cmd_ptr.Text_Get());
                        bool is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level, is_full, is_module_full);
                        if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr.Items[0].Text_Get()))
                        {

                            int sb1_tail_len = len_max - sb1.ToString().Length;
                            if (sb1_tail_len < 0)
                            {
                                sb1_tail_len = 0;
                            }
                            sb2.Append(sb1.ToString());
                            for (int i1 = 0; i1 < sb1_tail_len; i1++)
                            {
                                sb2.Append(' ');
                            }

                            sb2.Append(" - ");
                            sb2.Append(cmd_ptr.Help_Get());
                            //Cli_Output.Output_Str(sb2.str());
                            //Cli_Output.Output_NewLine();
                            sb.Append(sb2.ToString());
                            sb.Append("\r\n");
                            commands_count.Value++;
                            if (is_verbose && cmd_ptr.Items.Count > 1)
                            {
                                for (int i = 1; i < cmd_ptr.Items.Count; i++)
                                {
                                    Cmd_Item_Base item = cmd_ptr.Items[i];
                                    StringBuilder sb3 = new StringBuilder();
                                    StringBuilder sb4 = new StringBuilder();
                                    sb3.Append(" ");
                                    sb3.Append(item.Text_Get());

                                    int sb3_tail_len = len_max - sb3.ToString().Length;
                                    if (sb3_tail_len < 0)
                                    {
                                        sb3_tail_len = 0;
                                    }
                                    sb4.Append(sb3.ToString());
                                    for (int i3 = 0; i3 < sb3_tail_len; i3++)
                                    {
                                        sb4.Append(' ');
                                    }

                                    sb4.Append(" - ");
                                    sb4.Append(item.Help_Get());
                                    //Cli_Output.Output_Str(sb4.str());
                                    //Cli_Output.Output_NewLine();
                                    sb.Append(sb4.ToString());
                                    sb.Append("\r\n");
                                }
                            }
                        }
                    }
                }
            }

            Cli_Output.Output_Str(sb.ToString());

        }

        void help(string level, bool is_full, bool is_verbose, bool is_module_full,
                string module_filter, string command_filter, Cli_Output_CS Cli_Output)
        {
            Ref_Int modules_count = new Ref_Int(0);
            Ref_Int commands_count = new Ref_Int(0);
            int len_max = 0;
            int len;

            len = Help_Cli_Modules_Get_Len((int)User_Privilege.Value, Modules, level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter, Help_Str_Filter);
            if (len_max < len)
                len_max = len;

            Help_Cli_Modules_Print((int)User_Privilege.Value, Modules, level,
                    is_full, is_verbose, is_module_full,
                    module_filter, command_filter, Help_Str_Filter,
                    len_max, modules_count, commands_count,
                    Cli_Output);

            if (modules_count.Value == 0)
            {
                Cli_Output.Output_Str("modules \"");
                Cli_Output.Output_Str(module_filter);
                Cli_Output.Output_Str("\" - not found");
                Cli_Output.Output_NewLine();
            }
            else if (commands_count.Value == 0)
            {
                Cli_Output.Output_Str("commands \"");
                Cli_Output.Output_Str(command_filter);
                Cli_Output.Output_Str("\" - not found");
                Cli_Output.Output_NewLine();
            }

        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            Level_Description level = new Level_Description();
            string parameter;
            if (Levels.Count > 0)
            {
                level = Levels[Levels.Count - 1];
                parameter = level.Parameter;
            }
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_help_H:
                case Local_Cmd_ID.CMD_ID_help:
                    if (is_debug) return true;
                    {
                        bool is_full = false;
                        bool is_verbose = false;
                        bool is_module_full = false;
                        string module_filter = "*";
                        string command_filter = "*";
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;

                case Local_Cmd_ID.CMD_ID_help_full:
                    if (is_debug) return true;
                    {
                        bool is_full = true;
                        bool is_verbose = false;
                        bool is_module_full = false;
                        string module_filter = "*";
                        string command_filter = "*";
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;
                case Local_Cmd_ID.CMD_ID_help_full_verbose:
                    if (is_debug) return true;
                    {
                        bool is_full = true;
                        bool is_verbose = true;
                        bool is_module_full = false;
                        string module_filter = "*";
                        string command_filter = "*";
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;

                case Local_Cmd_ID.CMD_ID_help_command:
                    if (is_debug) return true;
                    {
                        bool is_full = false;
                        bool is_verbose = false;
                        bool is_module_full = false;
                        string module_filter = "*";
                        string command_filter = cmd.Items[1].Value_Str;
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;
                case Local_Cmd_ID.CMD_ID_help_command_verbose:
                    if (is_debug) return true;
                    {
                        bool is_full = false;
                        bool is_verbose = true;
                        bool is_module_full = false;
                        string module_filter = "*";
                        string command_filter = cmd.Items[1].Value_Str;
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;

                case Local_Cmd_ID.CMD_ID_help_module_module_name:
                    if (is_debug) return true;
                    {
                        bool is_full = false;
                        bool is_verbose = false;
                        bool is_module_full = true;
                        string module_filter = cmd.Items[2].Value_Str;
                        string command_filter = "*";
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;
                case Local_Cmd_ID.CMD_ID_help_module_module_name_verbose:
                    if (is_debug) return true;
                    {
                        bool is_full = false;
                        bool is_verbose = true;
                        bool is_module_full = true;
                        string module_filter = cmd.Items[2].Value_Str;
                        string command_filter = "*";
                        help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
                    }
                    return true;

                default:
                    return false; // Not Implemented

            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }
    }
}
