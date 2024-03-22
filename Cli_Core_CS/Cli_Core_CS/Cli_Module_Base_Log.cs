using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Log : Cli_Module
    {
        protected Cli_Input_CS Cli_Input;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_log_clear,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Log(Cli_Input_CS cli_input) : base("Base Log")
        {
            Cli_Input = cli_input;
            {
                // log clear
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_log_clear);
                cmd.Text_Set("log clear");
                cmd.Help_Set("clear log");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("log", "log"));
                cmd.Item_Add(new Cmd_Item_Word("clear", "log clear"));
                Cmd_Add(cmd);
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
                case Local_Cmd_ID.CMD_ID_log_clear:
                    if (is_debug) return true;
                    Cli_Input.Input_Clear();
                    return true;
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }
    }
}
