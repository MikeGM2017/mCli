using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Quit : Cli_Module
    {

        protected Ref_Boolean Cmd_Exit;
        protected Ref_Boolean Cmd_Quit;

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

        public Cli_Module_Base_Quit(Ref_Boolean cmd_exit, Ref_Boolean cmd_quit) : base("Base Quit")
        {

            Cmd_Exit = cmd_exit;
            Cmd_Quit = cmd_quit;

            {
                // E - exit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit_E);
                cmd.Text_Set("E");
                cmd.Help_Set("exit from program");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("E", "exit from program"));
                Cmd_Add(cmd);
            }
            {
                // Q - quit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_quit_Q);
                cmd.Text_Set("Q");
                cmd.Help_Set("exit from program");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("Q", "exit from program"));
                Cmd_Add(cmd);
            }
            {
                // exit
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit);
                cmd.Text_Set("exit");
                cmd.Help_Set("exit from program");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
                Cmd_Add(cmd);
            }
            {
                // exit force
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_exit_force);
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
                cmd.Help_Set("exit from program");
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

        override public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_quit:
                case Local_Cmd_ID.CMD_ID_quit_Q:
                case Local_Cmd_ID.CMD_ID_quit_force:
                    if (is_debug) return true;
                    Cmd_Quit.Value = true;
                    return true;
                case Local_Cmd_ID.CMD_ID_exit:
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
