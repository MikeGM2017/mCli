using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Debug : Cli_Module
    {
        protected Ref_Cli_Cmd_Privilege_ID User_Privilege;

        protected Cli_Modules Modules;

        protected List<Level_Description> Levels;

        protected Cli_CMD_Processor CMD_Processor;

        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_debug_cli,
            CMD_ID_debug_cli_counts,
            CMD_ID_debug_cli_verbose,
            CMD_ID_debug_cli_verbose_failed,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Debug(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                List<Level_Description> levels, Cli_CMD_Processor cmd_processor,
                Cli_Output_CS cli_output) : base("Base Debug")
        {
            User_Privilege = user_privilege;
            Modules = modules;
            Levels = levels;
            CMD_Processor = cmd_processor;
            Cli_Output = cli_output;

            {
                // debug cli
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_debug_cli);
                cmd.Text_Set("debug cli");
                cmd.Help_Set("debug cli");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("debug", "debug"));
                cmd.Item_Add(new Cmd_Item_Word("cli", "debug cli"));
                Cmd_Add(cmd);
            }
            {
                // debug cli
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_debug_cli_counts);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_debug_cli_verbose);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_debug_cli_verbose_failed);
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

        void Debug_Cli_Modules(bool is_counts, bool is_verbose, bool is_failed_only,
                Ref_Int total_count_cmd_id,
                Ref_Int total_count,
                Ref_Int total_count_checked,
                Ref_Int total_count_passed,
                Ref_Int total_count_failed)
        {
            bool is_debug = true;
            Ref_Boolean debug_res = new Ref_Boolean(false);
            for (int module = 0; module < Modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = Modules.Get(module);
                total_count_cmd_id.Value += module_ptr.Cmd_ID_Count_Get();
                if (is_counts)
                {
                    StringBuilder s_str = new StringBuilder();
                    s_str.Append("Module: ");
                    s_str.Append(module_ptr.Name_Get());
                    s_str.Append(" id_cnt=" + module_ptr.Cmd_ID_Count_Get().ToString());
                    Cli_Output.Output_Str(s_str.ToString());
                    Cli_Output.Output_NewLine();
                }
                total_count.Value += module_ptr.Cmd_Count_Get();
                if (is_counts)
                {
                    StringBuilder s_str = new StringBuilder();
                    s_str.Append("Module: ");
                    s_str.Append(module_ptr.Name_Get());
                    s_str.Append(" cmd_cnt=" + module_ptr.Cmd_Count_Get().ToString());
                    Cli_Output.Output_Str(s_str.ToString());
                    Cli_Output.Output_NewLine();
                }
                for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                {
                    Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                    string s = "";
                    for (int item = 0; item < cmd_ptr.Items.Count; item++)
                    {
                        Cmd_Item_Base item_ptr = cmd_ptr.Items[item];
                        if (item == 0)
                            s = item_ptr.Debug_Value_Get();
                        else
                            s += " " + item_ptr.Debug_Value_Get();
                    }
                    string level = cmd_ptr.Level_Get();
                    Levels.Clear();
                    string s_trim = s.Trim();
                    Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, s_trim);
                    if (level.Length == 0)
                    {
                        debug_res.Value = false;
                        CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                        if (is_verbose)
                        {
                            if (!is_failed_only || (is_failed_only && !debug_res.Value))
                            {
                                Cli_Output.Output_Str(s + " - " + (debug_res.Value ? "Ok" : "Failed"));
                                Cli_Output.Output_NewLine();
                            }
                        }
                    }
                    else
                    {
                        Levels.Add(new Level_Description(level));
                        debug_res.Value = false;
                        CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                        if (is_verbose)
                        {
                            if (!is_failed_only || (is_failed_only && !debug_res.Value))
                            {
                                Cli_Output.Output_Str("[" + cmd_ptr.Level_Get() + "] " + s + " - " + (debug_res.Value ? "Ok" : "Failed"));
                                Cli_Output.Output_NewLine();
                            }
                        }
                    }
                    total_count_checked.Value++;
                    if (debug_res.Value)
                        total_count_passed.Value++;

                    else
                        total_count_failed.Value++;
                }
            }
        }

        bool debug_cli(bool is_counts, bool is_verbose, bool is_failed_only)
        {
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
            StringBuilder s_str = new StringBuilder();
            s_str.Append("Debug Cli Result:");
            s_str.Append(" id_cnt:" + total_count_cmd_id.Value.ToString());
            s_str.Append(" total:" + total_count.Value.ToString());
            s_str.Append(" checked:" + total_count_checked.Value.ToString());
            s_str.Append(" passed:" + total_count_passed.Value.ToString());
            s_str.Append(" failed:" + total_count_failed.Value.ToString());
            Cli_Output.Output_Str(s_str.ToString());
            Cli_Output.Output_NewLine();
            Levels.Clear();

            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_debug_cli:
                    if (is_debug) return true;
                    {
                        bool is_counts = false;
                        bool is_verbose = false;
                        bool is_failed_only = false;
                        return debug_cli(is_counts, is_verbose, is_failed_only);
                    }
                case Local_Cmd_ID.CMD_ID_debug_cli_counts:
                    if (is_debug) return true;
                    {
                        bool is_counts = true;
                        bool is_verbose = false;
                        bool is_failed_only = false;
                        return debug_cli(is_counts, is_verbose, is_failed_only);
                    }
                case Local_Cmd_ID.CMD_ID_debug_cli_verbose:
                    if (is_debug) return true;
                    {
                        bool is_counts = false;
                        bool is_verbose = true;
                        bool is_failed_only = false;
                        return debug_cli(is_counts, is_verbose, is_failed_only);
                    }
                case Local_Cmd_ID.CMD_ID_debug_cli_verbose_failed:
                    if (is_debug) return true;
                    {
                        bool is_counts = false;
                        bool is_verbose = true;
                        bool is_failed_only = true;
                        return debug_cli(is_counts, is_verbose, is_failed_only);
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
