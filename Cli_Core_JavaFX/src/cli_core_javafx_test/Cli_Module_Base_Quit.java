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

    protected class Do_Exit extends Do_Abstract {

        protected Ref_Boolean Cmd_Exit;

        public Do_Exit(Ref_Boolean cmd_exit) {
            Cmd_Exit = cmd_exit;
        }

        @Override
        public void Do() {
            Cmd_Exit.Value = true;
        }
    }

    protected class Do_Quit extends Do_Abstract {

        protected Ref_Boolean Cmd_Quit;

        public Do_Quit(Ref_Boolean cmd_quit) {
            Cmd_Quit = cmd_quit;
        }

        @Override
        public void Do() {
            Cmd_Quit.Value = true;
        }
    }

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected Ref_Boolean Cmd_Exit;
    protected Ref_Boolean Cmd_Quit;

    protected Do_Exit Do_Exit_Object;
    protected Do_Quit Do_Quit_Object;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_quit = 1;
    private final int CMD_ID_quit_Q = 2;
    private final int CMD_ID_quit_force = 3;
    private final int CMD_ID_exit = 4;
    private final int CMD_ID_exit_E = 5;
    private final int CMD_ID_exit_force = 6;

    private final int CMD_ID_LAST = 7;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Quit(Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output,
            Ref_Boolean cmd_exit, Ref_Boolean cmd_quit) {
        super("Base Quit");

        Version = "0.03";

        Cli_Input = cli_input;
        Cli_Output = cli_output;

        Cmd_Exit = cmd_exit;
        Cmd_Quit = cmd_quit;

        Do_Exit_Object = new Do_Exit(cmd_exit);
        Do_Quit_Object = new Do_Quit(cmd_quit);

        {
            // E - exit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit_E, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
            cmd.Text_Set("E");
            cmd.Help_Set("exit from program (forced)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("E", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // Q - quit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_quit_Q);
            cmd.Text_Set("Q");
            cmd.Help_Set("exit from program (forced)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("Q", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // exit
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
            cmd.Text_Set("exit");
            cmd.Help_Set("exit from program (with confirmation)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit force
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_exit_force, Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);
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
            cmd.Help_Set("exit from program (with confirmation)");
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

    void Cli_Exit_Ask() {
        String s_question = "Exit(with Logout)?(y/n):";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_question);

        Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Do_Object_Set(Do_Exit_Object);
    }

    void Cli_Quit_Ask() {
        String s_question = "Quit(without Logout)?(y/n):";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_question);

        Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Do_Object_Set(Do_Quit_Object);
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_quit:
                if (is_debug) {
                    return true;
                }
                Cli_Quit_Ask();
                return true;
            case CMD_ID_quit_Q:
            case CMD_ID_quit_force:
                if (is_debug) {
                    return true;
                }
                Cmd_Quit.Value = true;
                return true;
            case CMD_ID_exit:
                if (is_debug) {
                    return true;
                }
                Cli_Exit_Ask();
                return true;
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
