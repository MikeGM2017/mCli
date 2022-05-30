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
public class Cli_Module_Base_Log extends Cli_Module {

    protected Cli_Input_JavaFX Cli_Input;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_log_clear = 1;

    private final int CMD_ID_LAST = 2;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Log(Cli_Input_JavaFX cli_input) {
        super("Base Log");
        Cli_Input = cli_input;
        {
            // log clear
            Cli_Cmd cmd = new Cli_Cmd( CMD_ID_log_clear);
            cmd.Text_Set("log clear");
            cmd.Help_Set("clear log");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("log", "log"));
            cmd.Item_Add(new Cmd_Item_Word("clear", "log clear"));
            Cmd_Add(cmd);
        }
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_log_clear:
                if (is_debug) {
                    return true;
                }
                Cli_Input.Input_Clear();
                return true;
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
