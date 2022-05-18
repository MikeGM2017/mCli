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
public class Cli_Module_Base_History extends Cli_Module {

    protected Cli_History History;

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_history = 1;
    private final int CMD_ID_history_show = 2;
    private final int CMD_ID_history_clear = 3;

    private final int CMD_ID_LAST = 4;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_History(Cli_History history, Cli_Output_JavaFX cli_output) {
        super("Base History");
        History = history;
        Cli_Output = cli_output;
        {
            // show history
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_history);
            cmd.Text_Set("history");
            cmd.Help_Set("history show");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("history", "history"));
            Cmd_Add(cmd);
        }
        {
            // show history
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_history_show);
            cmd.Text_Set("history show");
            cmd.Help_Set("history show");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("history", "history"));
            cmd.Item_Add(new Cmd_Item_Word("show", "history show"));
            Cmd_Add(cmd);
        }
        {
            // clear history
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_history_clear);
            cmd.Text_Set("history clear");
            cmd.Help_Set("history clear");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("history", "history"));
            cmd.Item_Add(new Cmd_Item_Word("clear", "history clear"));
            Cmd_Add(cmd);
        }
    }

    boolean history_show() {
        Cli_Output.Output_Str("History:");
        Cli_Output.Output_NewLine();
        int history_size = History.History_Size_Get();
        for (int i = 0; i < (history_size - 1); i++) { // @Attention : Not show last cmd!
            Cli_Output.Output_Str(History.History_Item_Get(i));
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    boolean history_clear() {
        History.Clear();
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_history:
            case CMD_ID_history_show:
                if (is_debug) {
                    return true;
                }
                return history_show();
            case CMD_ID_history_clear:
                if (is_debug) {
                    return true;
                }
                return history_clear();

            default:
                return false; // Not Implemented

        }
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
