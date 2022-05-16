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
public class Cli_Module_Base_Quit extends Cli_Module {

    protected Boolean_Ref Cmd_Exit;
    protected Boolean_Ref Cmd_Quit;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_quit = 1;
    private final int CMD_ID_quit_Q = 2;
    private final int CMD_ID_quit_force = 3;
    private final int CMD_ID_exit = 4;
    private final int CMD_ID_exit_E = 5;
    private final int CMD_ID_exit_force = 6;

    private final int CMD_ID_LAST = 8;
    //};

    @Override
    int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Quit(Boolean_Ref cmd_exit, Boolean_Ref cmd_quit) {
        super("Base Quit");
        Cmd_Exit = cmd_exit;
        Cmd_Quit = cmd_quit;
        {
            // E - exit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit_E);
            cmd.Text_Set("E");
            cmd.Help_Set("exit from program");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("E", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // Q - quit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_quit_Q);
            cmd.Text_Set("Q");
            cmd.Help_Set("quit from program");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("Q", "quit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit);
            cmd.Text_Set("exit");
            cmd.Help_Set("exit from program");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit force
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit_force);
            cmd.Text_Set("exit force");
            cmd.Help_Set("exit from program (forced)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            cmd.Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // quit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_quit);
            cmd.Text_Set("quit");
            cmd.Help_Set("exit from program");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("quit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // quit force
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_quit_force);
            cmd.Text_Set("quit force");
            cmd.Help_Set("exit from program (forced)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("quit", "exit from program"));
            cmd.Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_quit:
            case CMD_ID_quit_Q:
            case CMD_ID_quit_force:
                if (is_debug) {
                    return true;
                }
                Cmd_Quit.Value = true;
                return true;
            case CMD_ID_exit:
            case CMD_ID_exit_E:
            case CMD_ID_exit_force:
                if (is_debug) {
                    return true;
                }
                Cmd_Exit.Value = true;
                return true;
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
