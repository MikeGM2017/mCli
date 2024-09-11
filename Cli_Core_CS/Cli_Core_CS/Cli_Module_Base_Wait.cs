using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Wait : Cli_Module
    {
        protected Ref_Boolean Log_Wait_Enable;
        protected Ref_Boolean Cmd_Wait_Stop;

        protected Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_wait,
            CMD_ID_wait_log_enable,
            CMD_ID_wait_log_disable,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Wait(Ref_Boolean log_wait_enable, Ref_Boolean cmd_wait_stop,
        Cli_Input_CS cli_input, Cli_Output_CS cli_output) : base("Base Wait")
        {

            Version = "0.02";

            Log_Wait_Enable = log_wait_enable;
            Cmd_Wait_Stop = cmd_wait_stop;
            Cli_Input = cli_input;
            Cli_Output = cli_output;
            {
                // wait_threaded <sec>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_wait);
                cmd.Text_Set("wait <sec>");
                cmd.Help_Set("wait <sec:1..60> (for use in scripts)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("wait", "wait <sec>"));
                cmd.Item_Add(new Cmd_Item_Int_Range(1, 60, "<1..60>", "wait time in sec"));
                Cmd_Add(cmd);
            }
            {
                // log wait_threaded enable
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_wait_log_enable);
                cmd.Text_Set("wait log enable");
                cmd.Help_Set("wait logging enable");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("wait", "wait"));
                cmd.Item_Add(new Cmd_Item_Word("log", "wait logging"));
                cmd.Item_Add(new Cmd_Item_Word("enable", "wait logging enable"));
                Cmd_Add(cmd);
            }
            {
                // log wait_threaded disable
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_wait_log_disable);
                cmd.Text_Set("wait log disable");
                cmd.Help_Set("wait logging disable");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("wait", "wait"));
                cmd.Item_Add(new Cmd_Item_Word("log", "wait logging"));
                cmd.Item_Add(new Cmd_Item_Word("disable", "wait logging disable"));
                Cmd_Add(cmd);
            }
        }

        bool wait(Cli_Cmd cmd, bool log_wait_enable)
        {
            String token_value = cmd.Items[1].Value_Str;
            int wait_sec = 0;
            Int32.TryParse(token_value, out wait_sec);
            Cmd_Wait_Stop.Value = false;
            Cli_Input.Is_Ctrl_C_Pressed_Clear();

            if (log_wait_enable)
            {
                Cli_Output.Output_Str("Wait (Press Enter to stop):");
                Cli_Output.Output_NewLine();
            }

            Cli_Input.Input_Str_Set_Empty();
            Cli_Input.Wait_Count_Set(wait_sec);
            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_WAIT);
            Cli_Input.Wait_Count_Set(wait_sec);

            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_wait_log_enable:
                    if (is_debug)
                    {
                        return true;
                    }
                    Log_Wait_Enable.Value = true;
                    return true;
                case Local_Cmd_ID.CMD_ID_wait_log_disable:
                    if (is_debug)
                    {
                        return true;
                    }
                    Log_Wait_Enable.Value = false;
                    return true;

                case Local_Cmd_ID.CMD_ID_wait:
                    if (is_debug)
                    {
                        return true;
                    }
                    return wait(cmd, Log_Wait_Enable.Value);
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }

    }
}
