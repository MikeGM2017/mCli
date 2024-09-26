using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Level : Cli_Module
    {

        protected Cli_Input_CS Cli_Input;

        protected Cli_Output_CS Cli_Output;

        protected string Level_Root;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_level,
            CMD_ID_level_get,
            CMD_ID_level_get_all,

            CMD_ID_level_root,
            CMD_ID_level_root_quick,
            CMD_ID_level_up,
            CMD_ID_level_str,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Level(Cli_Input_CS cli_input, Cli_Output_CS cli_output, string level_root) : base("Base Level")
        {

            Version = "0.02";

            Cli_Input = cli_input; Cli_Output = cli_output; Level_Root = level_root;

            {
                // level
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level);
                cmd.Text_Set("level");
                cmd.Help_Set("get current level");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("level", "level"));
                Cmd_Add(cmd);
            }
            {
                // level get
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_get);
                cmd.Text_Set("level get");
                cmd.Help_Set("get current level");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("level", "level"));
                cmd.Item_Add(new Cmd_Item_Word("get", "get"));
                Cmd_Add(cmd);
            }
            {
                // level get all
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_get_all);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_root);
                cmd.Text_Set("level root");
                cmd.Help_Set("set level to root");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("level", "level"));
                cmd.Item_Add(new Cmd_Item_Word("root", "set level"));
                Cmd_Add(cmd);
            }
            {
                // level root quick
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_root_quick);
                cmd.Text_Set("!");
                cmd.Help_Set("set level to root");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Base("!", "set level to root"));
                Cmd_Add(cmd);
            }
            {
                // level up
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_up);
                cmd.Text_Set("level up");
                cmd.Help_Set("up level");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("level", "level"));
                cmd.Item_Add(new Cmd_Item_Word("up", "up level"));
                Cmd_Add(cmd);
            }
            {
                // level <str>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_level_str);
                cmd.Text_Set("level <str>");
                cmd.Help_Set("set level to <str>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Word("level", "level"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "set level to <str>"));
                Cmd_Add(cmd);
            }
        }

        bool level_get()
        {
            Cli_Output.Output_Str("Current Level: " + Cli_Input.Level_Get());
            Cli_Output.Output_NewLine();
            return true;
        }

        bool level_get_all(List<Level_Description> Levels)
        {
            if (Levels.Count > 0)
            {
                StringBuilder sb = new StringBuilder();
                sb.Append("Levels[").Append(Levels.Count).Append("]:");
                Cli_Output.Output_Str(sb.ToString());
                Cli_Output.Output_NewLine();
                for (int i = 0; i < Levels.Count; i++)
                {
                    Level_Description item = Levels[i];
                    string level = item.Level;
                    string parameter = item.Parameter;
                    Cli_Output.Output_Str(level);
                    if (parameter.Length > 0)
                    {
                        Cli_Output.Output_Str(" : " + parameter);
                    }
                    Cli_Output.Output_NewLine();
                }
            }
            else
            {
                Cli_Output.Output_Str("Levels - empty");
                Cli_Output.Output_NewLine();
            }
            level_get();
            return true;
        }

        bool level_root(List<Level_Description> Levels)
        {
            Levels.Clear();
            Cli_Input.Level_Set(Level_Root);
            return true;
        }

        bool level_up(List<Level_Description> Levels)
        {
            if (Levels.Count > 1)
            {
                string level_new = Levels[Levels.Count - 2].Level;
                //Levels.erase(Levels.begin() + Levels.Count - 1);
                Levels.Remove(Levels[Levels.Count - 2]);
                Cli_Input.Level_Set(level_new);
            }
            else
            {
                level_root(Levels);
            }
            return true;
        }

        bool level_str(List<Level_Description> Levels, string level_new)
        {
            string level_prev = Cli_Input.Level_Get();
            if (level_new.Length >= 2)
            {
                if (level_new[0] == '\"' && level_new[level_new.Length - 1] == '\"')
                {
                    level_new = level_new.Substring(1, level_new.Length - 2);
                }
                if (level_new[0] == '\'' && level_new[level_new.Length - 1] == '\'')
                {
                    level_new = level_new.Substring(1, level_new.Length - 2);
                }
            }
            if (level_new.Length == 0)
            {
                Levels.Clear();
                Cli_Input.Level_Set(Level_Root);
            }
            else if (level_prev != level_new)
            {
                Cli_Input.Level_Set(level_new);
                if (level_new.Length != 0)
                {
                    Levels.Add(new Level_Description(level_new));
                }
            }
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_level:
                case Local_Cmd_ID.CMD_ID_level_get:
                    if (is_debug)
                    {
                        return true;
                    }
                    return level_get();
                case Local_Cmd_ID.CMD_ID_level_get_all:
                    if (is_debug)
                    {
                        return true;
                    }
                    return level_get_all(Levels);
                case Local_Cmd_ID.CMD_ID_level_root:
                case Local_Cmd_ID.CMD_ID_level_root_quick:
                    if (is_debug)
                    {
                        return true;
                    }
                    return level_root(Levels);
                case Local_Cmd_ID.CMD_ID_level_up:
                    if (is_debug)
                    {
                        return true;
                    }
                    return level_up(Levels);
                case Local_Cmd_ID.CMD_ID_level_str:
                    if (is_debug)
                    {
                        return true;
                    }
                    else
                    {
                        string level_new = cmd.Items[1].Value_Str;
                        return level_str(Levels, level_new);
                    }
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            values_map["Level"] = Cli_Input.Level_Get();
        }

    }
}
