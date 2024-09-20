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
public class Cli_Module_Base_Wait extends Cli_Module {

    protected Ref_Boolean Log_Wait_Enable;
    protected Ref_Boolean Cmd_Wait_Stop;

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_wait = 1;
    private final int CMD_ID_wait_log_enable = 2;
    private final int CMD_ID_wait_log_disable = 3;

    private final int CMD_ID_LAST = 4;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Wait(Ref_Boolean log_wait_enable, Ref_Boolean cmd_wait_stop,
            Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output) {
        super("Base Wait");

        Version = "0.02";

        Log_Wait_Enable = log_wait_enable;
        Cmd_Wait_Stop = cmd_wait_stop;
        Cli_Input = cli_input;
        Cli_Output = cli_output;
        {
            // wait_threaded <sec>
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_wait);
            cmd.Text_Set("wait <sec>");
            cmd.Help_Set("wait <sec:1..60> (for use in scripts)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("wait", "wait <sec>"));
            cmd.Item_Add(new Cmd_Item_Int_Range(1, 60, "<1..60>", "wait time in sec"));
            Cmd_Add(cmd);
        }
        {
            // log wait_threaded enable
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_wait_log_enable);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_wait_log_disable);
            cmd.Text_Set("wait log disable");
            cmd.Help_Set("wait logging disable");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("wait", "wait"));
            cmd.Item_Add(new Cmd_Item_Word("log", "wait logging"));
            cmd.Item_Add(new Cmd_Item_Word("disable", "wait logging disable"));
            Cmd_Add(cmd);
        }
    }

    boolean wait(Cli_Cmd cmd, boolean log_wait_enable) {
        String token_value = cmd.Items.get(1).Value_Str;
        int wait_sec = Integer.valueOf(token_value);

        Cmd_Wait_Stop.Value = false;
        Cli_Input.Is_Ctrl_C_Pressed_Clear();

        if (log_wait_enable) {
            Cli_Output.Output_Str("Wait (Press Enter to stop):");
            Cli_Output.Output_NewLine();
        }

        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Wait_Count_Set(wait_sec);
        Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_WAIT);
        Cli_Input.Wait_Count_Set(wait_sec);

        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_wait_log_enable:
                if (is_debug) {
                    return true;
                }
                Log_Wait_Enable.Value = true;
                return true;
            case CMD_ID_wait_log_disable:
                if (is_debug) {
                    return true;
                }
                Log_Wait_Enable.Value = false;
                return true;

            case CMD_ID_wait:
                if (is_debug) {
                    return true;
                }
                return wait(cmd, Log_Wait_Enable.Value);
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
