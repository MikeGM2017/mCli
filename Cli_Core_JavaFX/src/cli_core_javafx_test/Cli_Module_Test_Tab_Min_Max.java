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
public class Cli_Module_Test_Tab_Min_Max extends Cli_Module {

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_min = 1;

    private final int CMD_ID_min_min = 2;
    private final int CMD_ID_min_max = 3;
    private final int CMD_ID_min_mux_min = 4;
    private final int CMD_ID_min_middle_min = 5;
    private final int CMD_ID_min_middle_max = 6;
    private final int CMD_ID_min_mux_max = 7;

    private final int CMD_ID_max = 8;

    private final int CMD_ID_need_nmin = 9;

    private final int CMD_ID_min_need_nmin_nmin = 10;
    private final int CMD_ID_min_need_nmin_nmax = 11;
    private final int CMD_ID_min_need_nmin_nmux_nmin = 12;
    private final int CMD_ID_min_need_nmin_nmiddle_nmin = 13;
    private final int CMD_ID_min_need_nmin_nmiddle_nmax = 14;
    private final int CMD_ID_min_need_nmin_nmux_nmax = 15;

    private final int CMD_ID_min_need_nmax = 16;

    private final int CMD_ID_min_mmmax1 = 17;
    private final int CMD_ID_min_mmmax2 = 18;
    private final int CMD_ID_min_mmmax3 = 19;
    private final int CMD_ID_min_mmmax345 = 20;
    private final int CMD_ID_min_mmmax444 = 21;
    private final int CMD_ID_min_mmmax455 = 22;
    private final int CMD_ID_min_mmmax5 = 23;
    private final int CMD_ID_min_mmmax555 = 24;
    private final int CMD_ID_min_mmmax566 = 25;

    private final int CMD_ID_LAST = 26;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Test_Tab_Min_Max() {
        super("Test Tab Min Max");
        {
            // min
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min);
            cmd.Text_Set("min");
            cmd.Help_Set("min (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            Cmd_Add(cmd);
        }

        {
            // min min
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_min);
            cmd.Text_Set("min min");
            cmd.Help_Set("min min (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("min", "min min (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min max
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_max);
            cmd.Text_Set("min max");
            cmd.Help_Set("min max (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("max", "min max (test tab min max)"));
            Cmd_Add(cmd);
        }

        {
            // min mux min
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mux_min);
            cmd.Text_Set("min mux min");
            cmd.Help_Set("min mux min (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mux", "min mux (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("min", "min mux min (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min middle min
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_middle_min);
            cmd.Text_Set("min middle min");
            cmd.Help_Set("min middle min (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("middle", "min middle (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("min", "min middle min (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min middle max
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_middle_max);
            cmd.Text_Set("min middle max");
            cmd.Help_Set("min middle max (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("middle", "min middle (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("max", "min middle max (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mux max
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mux_max);
            cmd.Text_Set("min mux max");
            cmd.Help_Set("min mux max (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mux", "min mux (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("max", "min min max (test tab min max)"));
            Cmd_Add(cmd);
        }

        {
            // max
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_max);
            cmd.Text_Set("max");
            cmd.Help_Set("max (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("max", "max (test tab min max)"));
            Cmd_Add(cmd);
        }

        {
            // min need nmin
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_need_nmin);
            cmd.Text_Set("min need nmin");
            cmd.Help_Set("min need nmin (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }

        {
            // min need nmin nmin
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmin);
            cmd.Text_Set("min need nmin nmin");
            cmd.Help_Set("min need nmin nmin (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin nmin (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }
        {
            // min need nmin nmax
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmax);
            cmd.Text_Set("min need nmin nmax");
            cmd.Help_Set("min need nmin nmax (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmax", "nmin nmax (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }

        {
            // min need nmin nmux nmin
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmux_nmin);
            cmd.Text_Set("min need nmin nmux nmin");
            cmd.Help_Set("min need nmin nmux nmin (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmux", "nmin nmux (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin nmux nmin (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }
        {
            // min need nmin nmiddle nmin
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmiddle_nmin);
            cmd.Text_Set("min need nmin nmiddle nmin");
            cmd.Help_Set("min need nmin nmiddle nmin (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmiddle", "nmin nmiddle (test tab min need nminnmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin nmiddle nmin (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }
        {
            // min need nmin nmiddle nmax
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmiddle_nmax);
            cmd.Text_Set("min need nmin nmiddle nmax");
            cmd.Help_Set("min need nmin nmiddle nmax (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmiddle", "nmin nmiddle (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmax", "nmin nmiddle nmax (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }
        {
            // min need nmin nmin nmax
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmin_nmux_nmax);
            cmd.Text_Set("min need nmin nmux nmax");
            cmd.Help_Set("min need nmin nmux nmax (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmin", "nmin (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmux", "nmin nmux (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmax", "nmin nmin nmax (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }

        {
            // min need nmax
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_need_nmax);
            cmd.Text_Set("min need nmax");
            cmd.Help_Set("min need nmax (test tab min need nmin nmax)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("need", "need (test tab min need nmin nmax)"));
            cmd.Item_Add(new Cmd_Item_Word("nmax", "nmax (test tab min need nmin nmax)"));
            Cmd_Add(cmd);
        }

        {
            // min mmmax1
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax1);
            cmd.Text_Set("min mmmax1");
            cmd.Help_Set("min mmmax1 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax1", "mmmax1 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax2
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax2);
            cmd.Text_Set("min mmmax2");
            cmd.Help_Set("min mmmax2 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax2", "mmmax2 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax3
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax3);
            cmd.Text_Set("min mmmax3");
            cmd.Help_Set("min mmmax3 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax3", "mmmax3 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax345
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax345);
            cmd.Text_Set("min mmmax345");
            cmd.Help_Set("min mmmax345 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax345", "mmmax345 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax444
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax444);
            cmd.Text_Set("min mmmax444");
            cmd.Help_Set("min mmmax444 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax444", "mmmax444 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax455
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax455);
            cmd.Text_Set("min mmmax455");
            cmd.Help_Set("min mmmax455 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax455", "mmmax455 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax5
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax5);
            cmd.Text_Set("min mmmax5");
            cmd.Help_Set("min mmmax5 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax5", "mmmax5 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax555
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax555);
            cmd.Text_Set("min mmmax555");
            cmd.Help_Set("min mmmax555 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax555", "mmmax555 (test tab min max)"));
            Cmd_Add(cmd);
        }
        {
            // min mmmax566
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_min_mmmax566);
            cmd.Text_Set("min mmmax566");
            cmd.Help_Set("min mmmax566 (test tab min max)");
            cmd.Is_Global_Set(true);
            cmd.Level_Set("");
            cmd.Item_Add(new Cmd_Item_Word("min", "min (test tab min max)"));
            cmd.Item_Add(new Cmd_Item_Word("mmmax566", "mmmax566 (test tab min max)"));
            Cmd_Add(cmd);
        }

    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_min:
            case CMD_ID_min_min:
            case CMD_ID_min_max:
            case CMD_ID_min_mux_min:
            case CMD_ID_min_middle_min:
            case CMD_ID_min_middle_max:
            case CMD_ID_min_mux_max:
            case CMD_ID_max:
                if (is_debug) {
                    return true;
                }
                return true;

            case CMD_ID_need_nmin:
            case CMD_ID_min_need_nmin_nmin:
            case CMD_ID_min_need_nmin_nmax:
            case CMD_ID_min_need_nmin_nmux_nmin:
            case CMD_ID_min_need_nmin_nmiddle_nmin:
            case CMD_ID_min_need_nmin_nmiddle_nmax:
            case CMD_ID_min_need_nmin_nmux_nmax:
            case CMD_ID_min_need_nmax:
                if (is_debug) {
                    return true;
                }
                return true;

            case CMD_ID_min_mmmax1:
            case CMD_ID_min_mmmax2:
            case CMD_ID_min_mmmax3:
            case CMD_ID_min_mmmax345:
            case CMD_ID_min_mmmax444:
            case CMD_ID_min_mmmax455:
            case CMD_ID_min_mmmax5:
            case CMD_ID_min_mmmax555:
            case CMD_ID_min_mmmax566:
                if (is_debug) {
                    return true;
                }
                return true;

            default:
                return false; // Not Implemented

        }
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
