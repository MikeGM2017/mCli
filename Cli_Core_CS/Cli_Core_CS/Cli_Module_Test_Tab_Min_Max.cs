using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Test_Tab_Min_Max : Cli_Module
    {
        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_min,

            CMD_ID_min_min,
            CMD_ID_min_max,
            CMD_ID_min_mux_min,
            CMD_ID_min_middle_min,
            CMD_ID_min_middle_max,
            CMD_ID_min_mux_max,

            CMD_ID_max,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Test_Tab_Min_Max() : base("Test Tab Min Max")
        {
            {
                // min
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min);
                cmd.Text_Set("min");
                cmd.Help_Set("min (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                Cmd_Add(cmd);
            }

            {
                // min min
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_min);
                cmd.Text_Set("min min");
                cmd.Help_Set("min min (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("min", "min min (test tab min max)"));
                Cmd_Add(cmd);
            }
            {
                // min max
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_max);
                cmd.Text_Set("min max");
                cmd.Help_Set("min max (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("max", "min max (test tab min max)"));
                Cmd_Add(cmd);
            }

            {
                // min min min
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_mux_min);
                cmd.Text_Set("min mux min");
                cmd.Help_Set("min mux min (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("mux", "min mux (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("min", "min mux min (test tab min max)"));
                Cmd_Add(cmd);
            }
            {
                // min middle min
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_middle_min);
                cmd.Text_Set("min middle min");
                cmd.Help_Set("min middle min (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("middle", "min middle (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("min", "min middle min (test tab min max)"));
                Cmd_Add(cmd);
            }
            {
                // min middle max
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_middle_max);
                cmd.Text_Set("min middle max");
                cmd.Help_Set("min middle max (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("middle", "min middle (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("max", "min middle max (test tab min max)"));
                Cmd_Add(cmd);
            }
            {
                // min min max
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_min_mux_max);
                cmd.Text_Set("min mux max");
                cmd.Help_Set("min mux max (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("mux", "min mux (test tab min max)"));
                cmd.Item_Add(new Cmd_Item_Word("max", "min min max (test tab min max)"));
                Cmd_Add(cmd);
            }

            {
                // max
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_max);
                cmd.Text_Set("max");
                cmd.Help_Set("max (test tab min max)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("max", "max (test tab min max)"));
                Cmd_Add(cmd);
            }
        }

        override public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_min:
                case Local_Cmd_ID.CMD_ID_min_min:
                case Local_Cmd_ID.CMD_ID_min_max:
                case Local_Cmd_ID.CMD_ID_min_mux_min:
                case Local_Cmd_ID.CMD_ID_min_middle_min:
                case Local_Cmd_ID.CMD_ID_min_middle_max:
                case Local_Cmd_ID.CMD_ID_min_mux_max:
                case Local_Cmd_ID.CMD_ID_max:
                    if (is_debug) return true;
                    return true;
            }
            return false; // Not Implemented
        }

        override public void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }

    }
}
