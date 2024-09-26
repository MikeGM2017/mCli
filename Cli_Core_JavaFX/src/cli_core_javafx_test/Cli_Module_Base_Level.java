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
public class Cli_Module_Base_Level extends Cli_Module {

    protected Cli_Input_JavaFX Cli_Input;

    protected Cli_Output_JavaFX Cli_Output;

    String Level_Root;

    //enum Local_Cmd_ID
    //{
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_level = 1;
    private final int CMD_ID_level_get = 2;
    private final int CMD_ID_level_get_all = 3;

    private final int CMD_ID_level_root = 4;
    private final int CMD_ID_level_root_quick = 5;
    private final int CMD_ID_level_up = 6;
    private final int CMD_ID_level_str = 7;

    private final int CMD_ID_LAST = 8;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Level(Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output, String level_root) {
        super("Base Level");

        Version = "0.02";

        Cli_Input = cli_input;
        Cli_Output = cli_output;
        Level_Root = level_root;

        {
            // level
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level);
            cmd.Text_Set("level");
            cmd.Help_Set("get current level");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            Cmd_Add(cmd);
        }
        {
            // level get
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_get);
            cmd.Text_Set("level get");
            cmd.Help_Set("get current level");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            cmd.Item_Add(new Cmd_Item_Word("get", "get"));
            Cmd_Add(cmd);
        }
        {
            // level get all
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_get_all);
            cmd.Text_Set("level get all");
            cmd.Help_Set("get all levels");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            cmd.Item_Add(new Cmd_Item_Word("get", "get"));
            cmd.Item_Add(new Cmd_Item_Word("all", "all"));
            Cmd_Add(cmd);
        }

        {
            // level root
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_root);
            cmd.Text_Set("level root");
            cmd.Help_Set("set level to root");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            cmd.Item_Add(new Cmd_Item_Word("root", "set level"));
            Cmd_Add(cmd);
        }
        {
            // level root quick
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_root_quick);
            cmd.Text_Set("!");
            cmd.Help_Set("set level to root");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Base("!", "set level to root"));
            Cmd_Add(cmd);
        }
        {
            // level up
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_up);
            cmd.Text_Set("level up");
            cmd.Help_Set("up level");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            cmd.Item_Add(new Cmd_Item_Word("up", "up level"));
            Cmd_Add(cmd);
        }
        {
            // level <str>
            Cli_Cmd cmd = new Cli_Cmd((int) CMD_ID_level_str);
            cmd.Text_Set("level <str>");
            cmd.Help_Set("set level to <str>");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("level", "level"));
            cmd.Item_Add(new Cmd_Item_Str("<str>", "set level to <str>"));
            Cmd_Add(cmd);
        }
    }

    boolean level_get() {
        Cli_Output.Output_Str("Current Level: " + Cli_Input.Level_Get());
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean level_get_all(List<Level_Description> Levels) {
        if (Levels.size() > 0) {
            Cli_Output.Output_Str("Levels[" + Integer.toString(Levels.size()) + "]:");
            Cli_Output.Output_NewLine();
            for (Level_Description item : Levels) {
                String level = item.Level;
                String parameter = item.Parameter;
                Cli_Output.Output_Str(level);
                if (parameter.length() > 0) {
                    Cli_Output.Output_Str(" : " + parameter);
                }
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("Levels - empty");
            Cli_Output.Output_NewLine();
        }
        level_get();
        return true;
    }

    boolean level_root(List<Level_Description> Levels) {
        Levels.clear();
        Cli_Input.Level_Set(Level_Root);
        return true;
    }

    boolean level_up(List<Level_Description> Levels) {
        if (Levels.size() > 1) {
            String level_new = Levels.get(Levels.size() - 2).Level;
            Levels.remove(Levels.size() - 1);
            Cli_Input.Level_Set(level_new);
        } else {
            level_root(Levels);
        }
        return true;
    }

    boolean level_str(List<Level_Description> Levels, String level_new) {
        String level_prev = Cli_Input.Level_Get();
        if (level_new.length() >= 2) {
            if (level_new.charAt(0) == '\"' && level_new.charAt(level_new.length() - 1) == '\"') {
                level_new = level_new.substring(1, level_new.length() - 1);
            }
            if (level_new.charAt(0) == '\'' && level_new.charAt(level_new.length() - 1) == '\'') {
                level_new = level_new.substring(1, level_new.length() - 1);
            }
        }
        if (level_new.length() == 0) {
            Levels.clear();
            Cli_Input.Level_Set(Level_Root);
        } else if (!level_prev.equals(level_new)) {
            Cli_Input.Level_Set(level_new);
            if (level_new.length() != 0) {
                Levels.add(new Level_Description(level_new));
            }
        }
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {
            case CMD_ID_level:
            case CMD_ID_level_get:
                if (is_debug) {
                    return true;
                }
                return level_get();
            case CMD_ID_level_get_all:
                if (is_debug) {
                    return true;
                }
                return level_get_all(Levels);
            case CMD_ID_level_root:
            case CMD_ID_level_root_quick:
                if (is_debug) {
                    return true;
                }
                return level_root(Levels);
            case CMD_ID_level_up:
                if (is_debug) {
                    return true;
                }
                return level_up(Levels);
            case CMD_ID_level_str:
                if (is_debug) {
                    return true;
                } else {
                    String level_new = cmd.Items.get(1).Value_Str;
                    return level_str(Levels, level_new);
                }
        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        values_map.put("Level", Cli_Input.Level);
    }

}
