using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Quit : Cli_Module
    {

        protected class Do_Exit : Do_Abstract
        {
            protected Ref_Boolean Cmd_Exit;

            public Do_Exit(Ref_Boolean cmd_exit)
            {
                Cmd_Exit = cmd_exit;
            }

            override public void Do()
            {
                Cmd_Exit.Value = true;
            }
        }

        protected class Do_Quit : Do_Abstract
        {
            protected Ref_Boolean Cmd_Quit;

            public Do_Quit(Ref_Boolean cmd_quit)
            {
                Cmd_Quit = cmd_quit;
            }

            override public void Do()
            {
                Cmd_Quit.Value = true;
            }
        }

        protected Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        protected Ref_Boolean Cmd_Exit;
        protected Ref_Boolean Cmd_Quit;

        protected Do_Exit Do_Exit_Object;
        protected Do_Quit Do_Quit_Object;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_quit,
            CMD_ID_quit_Q,
            CMD_ID_quit_force,
            CMD_ID_exit,
            CMD_ID_exit_E,
            CMD_ID_exit_force,

            CMD_ID_LAST
        };

        override public int Cmd_ID_Count_Get()
        {
            return (int)Local_Cmd_ID.CMD_ID_LAST - (int)Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Quit(Cli_Input_CS cli_input, Cli_Output_CS cli_output,
            Ref_Boolean cmd_exit, Ref_Boolean cmd_quit) : base("Base Quit")
        {
            Version = "0.03";

            Cli_Input = cli_input;
            Cli_Output = cli_output;

            Cmd_Exit = cmd_exit;
            Cmd_Quit = cmd_quit;

            Do_Exit_Object = new Do_Exit(cmd_exit);
            Do_Quit_Object = new Do_Quit(cmd_quit);

            {
                // E - exit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit_E, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
                cmd.Text_Set("E");
                cmd.Help_Set("exit from program (forced)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("E", "exit from program (forced)"));
                Cmd_Add(cmd);
            }
            {
                // Q - quit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_quit_Q);
                cmd.Text_Set("Q");
                cmd.Help_Set("exit from program (forced)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("Q", "exit from program (forced)"));
                Cmd_Add(cmd);
            }
            {
                // exit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
                cmd.Text_Set("exit");
                cmd.Help_Set("exit from program (with confirmation)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
                Cmd_Add(cmd);
            }
            {
                // exit force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit_force, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
                cmd.Text_Set("exit force");
                cmd.Help_Set("exit from program (forced)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
                cmd.Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
                Cmd_Add(cmd);
            }
            {
                // quit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_quit);
                cmd.Text_Set("quit");
                cmd.Help_Set("exit from program (with confirmation)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("quit", "exit from program"));
                Cmd_Add(cmd);
            }
            {
                // quit force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_quit_force);
                cmd.Text_Set("quit force");
                cmd.Help_Set("exit from program (forced)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("quit", "exit from program"));
                cmd.Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
                Cmd_Add(cmd);
            }
        }

        void Cli_Exit_Ask()
        {
            string s_question = "Exit(with Logout)?(y/n):";
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(s_question);

            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
            Cli_Input.Input_Str_Set_Empty();
            Cli_Input.Do_Object_Set(Do_Exit_Object);
        }

        void Cli_Quit_Ask()
        {
            string s_question = "Quit(without Logout)?(y/n):";
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(s_question);

            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
            Cli_Input.Input_Str_Set_Empty();
            Cli_Input.Do_Object_Set(Do_Quit_Object);
        }

        override public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_quit:
                    if (is_debug) return true;
                    Cli_Quit_Ask();
                    return true;
                case Local_Cmd_ID.CMD_ID_quit_Q:
                case Local_Cmd_ID.CMD_ID_quit_force:
                    if (is_debug) return true;
                    Cmd_Quit.Value = true;
                    return true;
                case Local_Cmd_ID.CMD_ID_exit:
                    if (is_debug) return true;
                    Cli_Exit_Ask();
                    return true;
                case Local_Cmd_ID.CMD_ID_exit_E:
                case Local_Cmd_ID.CMD_ID_exit_force:
                    if (is_debug) return true;
                    Cmd_Exit.Value = true;
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
