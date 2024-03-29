﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Vars : Cli_Module
    {
        protected Cli_Modules Modules;
        protected Dictionary<string, string> Values_Map;
        protected Str_Filter Str_Filter;
        protected Cli_Output_CS Cli_Output;

        protected char C_Single;
        protected char C_Multy;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_point_var_name,
            CMD_ID_point_var_name_assign_str,
            CMD_ID_point_var_name_assign_point_var_name,

            CMD_ID_point_var_name_inc,

            CMD_ID_point_var_name_delete,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Vars(Cli_Modules modules, Dictionary<string, string> values_map, Str_Filter str_filter,
            Cli_Output_CS cli_output,
            char c_single = '?', char c_multy = '*') : base("Vars")
        {
            Modules = modules;
            Values_Map = values_map;
            Str_Filter = str_filter;
            Cli_Output = cli_output;
            C_Single = c_single;
            C_Multy = c_multy;

            {
                // get
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name);
                cmd.Text_Set(".<var_name>");
                cmd.Help_Set("get <var_name> value (by filter, .* - get all vars)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name (by filter)", C_Single, C_Multy));
                Cmd_Add(cmd);
            }

            {
                // assign int @Attention: Must be before Local_Cmd_ID.CMD_ID_point_var_name_assign_str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_assign_point_var_name);
                cmd.Text_Set(".<var_name> = .<var2_name>");
                cmd.Help_Set("set <var_name> value of <var2_name>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var2_name>", "var2 name", C_Single, C_Multy));
                Cmd_Add(cmd);
            }
            {
                // assign str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_assign_str);
                cmd.Text_Set(".<var_name> = <str>");
                cmd.Help_Set("set <var_name> to <str>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "new value"));
                Cmd_Add(cmd);
            }

            {
                // inc @Attention: increment as integer only (string converted to "0")
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_inc);
                cmd.Text_Set(".<var_name> inc");
                cmd.Help_Set("increment <var_name>");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("inc", "increment"));
                Cmd_Add(cmd);
            }

            {
                // delete
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_point_var_name_delete);
                cmd.Text_Set(".<var_name> delete");
                cmd.Help_Set("delete <var_name> (by filter, .* - delete all vars)");
                cmd.Is_Global_Set(true);
                cmd.Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
                cmd.Item_Add(new Cmd_Item_Word("delete", "delete (by filter)"));
                Cmd_Add(cmd);
            }

        }

        bool var_get(string point_var_name_str)
        {
            Cli_Output.Output_NewLine();
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (Str_Filter.Is_Match(var_name, item_var_name))
                {
                    Cli_Output.Output_Str(item_var_name + " = \"" + item.Value + "\"");
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        string Str_Get_Without_Commas(string value_str)
        {
            string s = value_str;
            if (value_str.Length >= 2)
            {
                if (
                        (value_str[0] == '\"' && value_str[value_str.Length - 1] == '\"')
                        || (value_str[0] == '\'' && value_str[value_str.Length - 1] == '\'')
                        )
                {
                    s = value_str.Substring(1, value_str.Length - 2);
                }
            }
            return s;
        }

        bool var_set_str(string point_var_name_str, string value_str)
        {
            Cli_Output.Output_NewLine();
            string var_name = point_var_name_str.Substring(1);
            string value_str_without_commas = Str_Get_Without_Commas(value_str);
            Values_Map[var_name] = value_str_without_commas;
            Cli_Output.Output_Str(var_name + " = \"" + value_str_without_commas + "\"");
            Cli_Output.Output_NewLine();
            return true;
        }

        bool var_set_var(string point_var1_name_str, string point_var2_name_str)
        {
            Cli_Output.Output_NewLine();
            string var2_name = point_var2_name_str.Substring(1);
            bool var2_found = false;
            foreach (var item in Values_Map)
            {
                if (item.Key == var2_name)
                {
                    string var1_name = point_var1_name_str.Substring(1);
                    string var2_value = item.Value;
                    Values_Map[var1_name] = var2_value;
                    Cli_Output.Output_Str(var1_name + " = \"" + var2_value + "\"");
                    var2_found = true;
                    break;
                }
            }
            if (!var2_found)
            {
                Cli_Output.Output_Str(point_var2_name_str + " - Not Found");
            }
            Cli_Output.Output_NewLine();
            return true;
        }

        bool var_inc(string point_var_name_str)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                if (item.Key == var_name)
                {
                    int item_var_value_int_new = 0;
                    Int32.TryParse(item.Value, out item_var_value_int_new);
                    item_var_value_int_new++;
                    Values_Map[var_name] = item_var_value_int_new.ToString();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        bool var_delete(string point_var_name_str)
        {
            string var_name = point_var_name_str.Substring(1);
            bool found = false;
            foreach (var item in Values_Map)
            {
                string item_var_name = item.Key;
                if (Str_Filter.Is_Match(var_name, item_var_name))
                {
                    Values_Map.Remove(item.Key);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(var_name + " - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {

                case Local_Cmd_ID.CMD_ID_point_var_name:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_get(point_var_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_assign_str:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        string value_str = cmd.Items[2].Value_Str;
                        return var_set_str(point_var_name_str, value_str);
                    }
                case Local_Cmd_ID.CMD_ID_point_var_name_assign_point_var_name:
                    if (is_debug) return true;
                    {
                        string point_var1_name_str = cmd.Items[0].Value_Str;
                        string point_var2_name_str = cmd.Items[2].Value_Str;
                        return var_set_var(point_var1_name_str, point_var2_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_inc:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_inc(point_var_name_str);
                    }

                case Local_Cmd_ID.CMD_ID_point_var_name_delete:
                    if (is_debug) return true;
                    {
                        string point_var_name_str = cmd.Items[0].Value_Str;
                        return var_delete(point_var_name_str);
                    }

            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }

    }
}
