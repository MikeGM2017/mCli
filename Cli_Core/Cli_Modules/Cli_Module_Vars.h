/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Vars.h
 * Author: mike
 *
 * Created on June 7, 2021, 9:54 AM
 */

#ifndef CLI_MODULE_VARS_H
#define CLI_MODULE_VARS_H

#include "Cli_Module.h"

#include "Cmd_Item_Point_Var_Name.h"
#include "Cmd_Item_Assignment_Mark.h"
#include "Cli_Output_Abstract.h"
#include "Str_Filter_Abstract.h"
#include "Cmd_Item_Str.h"

class Cli_Module_Vars : public Cli_Module {
protected:

    Cli_Modules &Modules;
    map<string, string> &Values_Map;
    Str_Filter_Abstract &Str_Filter;
    Cli_Output_Abstract &Cli_Output;

    char C_Single;
    char C_Multy;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_point_var_name,
        CMD_ID_point_var_name_assign_str,
        CMD_ID_point_var_name_assign_point_var_name,

        CMD_ID_point_var_name_inc,

        CMD_ID_point_var_name_delete,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Vars(Cli_Modules &modules, map<string, string> &values_map, Str_Filter_Abstract &str_filter,
            Cli_Output_Abstract &cli_output,
            char c_single = '?', char c_multy = '*') :
    Cli_Module("Vars"), Modules(modules), Values_Map(values_map), Str_Filter(str_filter),
    Cli_Output(cli_output), C_Single(c_single), C_Multy(c_multy) {

        // <editor-fold defaultstate="collapsed" desc="Vars: get/set">
        {
            // get
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name);
            cmd->Text_Set(".<var_name>");
            cmd->Help_Set("get <var_name> value (by filter, .* - get all vars)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name (by filter)", C_Single, C_Multy));
            Cmd_Add(cmd);
        }

        {
            // assign int @Attention: Must be before CMD_ID_point_var_name_assign_str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_assign_point_var_name);
            cmd->Text_Set(".<var_name> = .<var2_name>");
            cmd->Help_Set("set <var_name> value of <var2_name>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var2_name>", "var2 name", C_Single, C_Multy));
            Cmd_Add(cmd);
        }
        {
            // assign str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_assign_str);
            cmd->Text_Set(".<var_name> = <str>");
            cmd->Help_Set("set <var_name> to <str>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "new value"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Vars: inc">
        {
            // inc @Attention: increment as integer only (string converted to "0")
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_inc);
            cmd->Text_Set(".<var_name> inc");
            cmd->Help_Set("increment <var_name>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Word("inc", "increment"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Vars: delete">
        {
            // delete
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_delete);
            cmd->Text_Set(".<var_name> delete");
            cmd->Help_Set("delete <var_name> (by filter, .* - delete all vars)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Word("delete", "delete (by filter)"));
            Cmd_Add(cmd);
        }
        // </editor-fold>

    }

    ~Cli_Module_Vars() {
    }

    bool var_get(string point_var_name_str) {
        Cli_Output.Output_NewLine();

        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter = Values_Map.begin();
                iter != Values_Map.end(); iter++) {
            string item_var_name = iter->first;
            if (Str_Filter.Is_Match(var_name, item_var_name)) {
                Cli_Output.Output_Str(item_var_name + " = \"" + iter->second + "\"");
                Cli_Output.Output_NewLine();
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    map<string, string>::iterator Values_Map_Find_By_Var_Name(string var_name_arg) {
        for (map<string, string>::iterator iter = Values_Map.begin();
                iter != Values_Map.end(); iter++) {
            string item_var_name = "." + iter->first;
            if (var_name_arg == item_var_name) {
                return iter;
                break;
            }
        }
        return Values_Map.end();
    }

    string Str_Get_Without_Commas(string value_str) {
        string s = value_str;
        if (value_str.size() >= 2) {
            if (
                    (value_str[0] == '\"' && value_str[value_str.size() - 1] == '\"')
                    || (value_str[0] == '\'' && value_str[value_str.size() - 1] == '\'')
                    ) {
                s = value_str.substr(1, value_str.size() - 2);
            }
        }
        return s;
    }

    bool var_set_str(string point_var_name_str, string value_str) {
        Cli_Output.Output_NewLine();
        string var_name = point_var_name_str.substr(1);
        string value_str_without_commas = Str_Get_Without_Commas(value_str);
        Values_Map[var_name] = value_str_without_commas;
        Cli_Output.Output_Str(var_name + " = \"" + value_str_without_commas + "\"");
        Cli_Output.Output_NewLine();
        return true;
    }

    bool var_set_var(string point_var1_name_str, string point_var2_name_str) {
        Cli_Output.Output_NewLine();
        map<string, string>::iterator iter2 = Values_Map_Find_By_Var_Name(point_var2_name_str);
        if (iter2 != Values_Map.end()) {
            string var1_name = point_var1_name_str.substr(1);
            string var2_value = iter2->second;
            Values_Map[var1_name] = var2_value;
            Cli_Output.Output_Str(var1_name + " = \"" + var2_value + "\"");
        } else {
            Cli_Output.Output_Str(point_var2_name_str + " - Not Found");
        }
        Cli_Output.Output_NewLine();
        return true;
    }

    bool var_inc(string point_var_name_str) {

        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter = Values_Map.begin();
                iter != Values_Map.end(); iter++) {
            string item_var_name = iter->first;
            if (var_name == item_var_name) {
                int item_var_value_int_new = atoi(iter->second.c_str()) + 1;
                stringstream s_str;
                s_str << item_var_value_int_new;
                iter->second = s_str.str();
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool var_delete(string point_var_name_str) {

        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter = Values_Map.begin();
                iter != Values_Map.end(); iter++) {
            string item_var_name = iter->first;
            if (Str_Filter.Is_Match(var_name, item_var_name)) {
                Values_Map.erase(iter);
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {

                // <editor-fold defaultstate="collapsed" desc="Vars: get/set">

            case CMD_ID_point_var_name:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                return var_get(point_var_name_str);
            }

            case CMD_ID_point_var_name_assign_str:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                string value_str = cmd->Items[2]->Value_Str;
                return var_set_str(point_var_name_str, value_str);
            }
            case CMD_ID_point_var_name_assign_point_var_name:
                if (is_debug) return true;
            {
                string point_var1_name_str = cmd->Items[0]->Value_Str;
                string point_var2_name_str = cmd->Items[2]->Value_Str;
                return var_set_var(point_var1_name_str, point_var2_name_str);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Vars: inc">

            case CMD_ID_point_var_name_inc:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                return var_inc(point_var_name_str);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Vars: delete">

            case CMD_ID_point_var_name_delete:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                return var_delete(point_var_name_str);
            }

                // </editor-fold>

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_VARS_H */
