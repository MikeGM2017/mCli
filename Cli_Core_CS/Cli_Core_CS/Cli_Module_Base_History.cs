using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_History : Cli_Module
    {
        protected Cli_History History;

        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_history,
            CMD_ID_history_show,
            CMD_ID_history_clear,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return (int)Local_Cmd_ID.CMD_ID_LAST - (int)Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_History(Cli_History history, Cli_Output_CS cli_output) : base("Base History")
        {
            History = history;
            Cli_Output = cli_output;

            {
                // show history
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_history);
                cmd.Text_Set("history show");
                cmd.Help_Set("history show");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("history", "history"));
                Cmd_Add(cmd);
            }
            {
                // show history
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_history_show);
                cmd.Text_Set("history show");
                cmd.Help_Set("history show");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("history", "history"));
                cmd.Item_Add(new Cmd_Item_Word("show", "history show"));
                Cmd_Add(cmd);
            }
            {
                // clear history
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_history_clear);
                cmd.Text_Set("history clear");
                cmd.Help_Set("history clear");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("history", "history"));
                cmd.Item_Add(new Cmd_Item_Word("clear", "history clear"));
                Cmd_Add(cmd);
            }
        }

        bool history_show()
        {
            Cli_Output.Output_Str("History:");
            Cli_Output.Output_NewLine();
            int history_size = History.History_Size_Get();
            for (int i = 0; i < (history_size - 1); i++)
            { // @Attention : Not show last cmd!
                Cli_Output.Output_Str(History.History_Item_Get(i));
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        bool history_clear()
        {
            History.Clear();
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_history:
                case Local_Cmd_ID.CMD_ID_history_show:
                    if (is_debug) return true;
                    return history_show();
                case Local_Cmd_ID.CMD_ID_history_clear:
                    if (is_debug) return true;
                    return history_clear();
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }
    }
}
