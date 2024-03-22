using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Rem : Cli_Module
    {
        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_rem,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Rem(string str_rem, Cli_Output_CS cli_output) : base("Base Rem")
        {
            Cli_Output = cli_output;
            {
                // rem
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_rem);
                cmd.Text_Set(str_rem);
                cmd.Help_Set("comment (for use in scripts)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Rem(str_rem, "comment"));
                Cmd_Add(cmd);
            }
        }

        bool rem(string s_rem)
        {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(s_rem);
            Cli_Output.Output_NewLine();
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_rem:
                    if (is_debug) return true;
                    {
                        string s_rem = cmd.Items[0].Value_Str;
                        return rem(s_rem);
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
