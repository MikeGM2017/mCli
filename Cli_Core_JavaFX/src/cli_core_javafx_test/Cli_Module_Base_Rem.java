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
public class Cli_Module_Base_Rem extends Cli_Module {

    protected Cli_Output_JavaFX Cli_Output;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;
    private final int CMD_ID_rem = 1;
    private final int CMD_ID_LAST = 2;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Rem(String str_rem, Cli_Output_JavaFX cli_output) {
        super("Base Rem");
        Cli_Output = cli_output;
        {
            // rem
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_rem);
            cmd.Text_Set(str_rem);
            cmd.Help_Set("comment (for use in scripts)");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Rem(str_rem, "comment"));
            Cmd_Add(cmd);
        }
    }

    boolean rem(String s_rem) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_rem);
        Cli_Output.Output_NewLine();
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_rem:
                if (is_debug) {
                    return true;
                }
                 {
                    String s_rem = cmd.Items.get(0).Value_Str;
                    return rem(s_rem);
                }
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
