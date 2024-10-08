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

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"
#include "Cmd_Item_Point_Var_Name.h"
#include "Cmd_Item_Assignment_Mark.h"

#include "Cli_Output_Abstract.h"

#include "Str_Filter_Abstract.h"

#include "Str_Get_Without_Commas.h"

class Cli_Module_Vars : public Cli_Module {
protected:

    Cli_Modules &Modules;
    map<string, string> &Values_Map;
    Str_Filter_Abstract &Str_Filter;
    Str_Get_Without_Commas &Str_Without_Commas;
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

        CMD_ID_point_var_name_add_str,
        CMD_ID_point_var_name_stradd_str,

        CMD_ID_point_var_name_delete,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Vars(Cli_Modules &modules, map<string, string> &values_map, Str_Filter_Abstract &str_filter,
            Str_Get_Without_Commas &str_without_commas,
            Cli_Output_Abstract &cli_output,
            char c_single = '?', char c_multy = '*') :
    Cli_Module("Vars"), Modules(modules), Values_Map(values_map), Str_Filter(str_filter),
    Str_Without_Commas(str_without_commas),
    Cli_Output(cli_output), C_Single(c_single), C_Multy(c_multy) {

        Version = "0.07";

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

        // <editor-fold defaultstate="collapsed" desc="Vars: add">
        {
            // .<var_name> add <str>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_add_str);
            cmd->Text_Set(".<var_name> add <str>");
            cmd->Help_Set("<var_name> add int/var/str");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Word("add", "add"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "value to add")); // <str> -> .v/int/str
            Cmd_Add(cmd);
        }
        {
            // .<var_name> stradd <str>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_stradd_str);
            cmd->Text_Set(".<var_name> stradd <str>");
            cmd->Help_Set("<var_name> add var/str as str");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Word("stradd", "add as str")); // <str> -> .v/str
            cmd->Item_Add(new Cmd_Item_Str("<str>", "value to add as str"));
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

    int Str_To_Int(string s) {
        return atoi(s.c_str());
    }

    string Int_To_Str(int v) {
        stringstream s_str;
        s_str << v;
        return s_str.str();
    }

    bool Char_Is_Digit(char c) {
        if (c >= '0' && c <= '9') return true;
        return false;
    }

    bool Char_Is_Digit_Or_Plus_Or_Minus(char c) {
        if (c >= '0' && c <= '9') return true;
        if (c == '+') return true;
        if (c == '-') return true;
        return false;
    }

    bool Str_Is_Int(string s) {
        if (s.empty()) return false; // Case: empty string is not digit
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (i == 0) {
                if (!Char_Is_Digit_Or_Plus_Or_Minus(c)) return false;
            } else {
                if (!Char_Is_Digit(c)) return false;
            }
        }
        return true;
    }

    bool var_get(string point_var_name_str) {
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

    string var_name_get(string s) {
        if (s.length() > 0 && s[0] == '.') {
            string var_name = s.substr(1);
            if (var_name.length() > 0 && var_name[0] == '.') {
                string var_name2 = var_name.substr(1);
                map<string, string>::iterator iter = Values_Map.find(var_name2);
                if (iter != Values_Map.end()) {
                    var_name = iter->second;
                    if (var_name.length() > 0 && var_name[0] == '.') {
                        var_name = var_name.substr(1);
                    }
                }
            }
            return var_name;
        }
        return s;
    }

    bool var_set_str(string point_var_name_str, string value_str) {
        string var_name = var_name_get(point_var_name_str);
        string value_str_without_commas = Str_Without_Commas.Get(value_str);
        Values_Map[var_name] = value_str_without_commas;
        Cli_Output.Output_Str(var_name + " = \"" + value_str_without_commas + "\"");
        Cli_Output.Output_NewLine();
        return true;
    }

    bool var_set_var(string point_var1_name_str, string point_var2_name_str) {
        map<string, string>::iterator iter2 = Values_Map.find(point_var2_name_str.substr(1));
        if (iter2 != Values_Map.end()) {
            string var1_name = var_name_get(point_var1_name_str);
            string var2_value = iter2->second;
            Values_Map[var1_name] = var2_value;
            Cli_Output.Output_Str(var1_name + " = \"" + var2_value + "\"");
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_Str(point_var2_name_str + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool var_inc(string point_var_name_str) {
        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter = Values_Map.begin(); iter != Values_Map.end(); iter++) {
            string item_var_name = iter->first;
            if (var_name == item_var_name) {
                int item_var_value_int_new = Str_To_Int(iter->second) + 1;
                iter->second = Int_To_Str(item_var_value_int_new);
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool var_add(string point_var_name_str, string add_str, bool is_try_add_int) {
        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter_left = Values_Map.begin(); iter_left != Values_Map.end(); iter_left++) {
            string item_var_name = iter_left->first;
            if (var_name == item_var_name) {
                string item_var_value_old = iter_left->second.c_str();
                if (is_try_add_int && Str_Is_Int(item_var_value_old) && Str_Is_Int(Str_Without_Commas.Get(add_str))) { // Case 1: VAR_INT add VALUE_INT
                    int item_var_value_int_old = Str_To_Int(item_var_value_old);
                    int add_value_int = Str_To_Int(Str_Without_Commas.Get(add_str));
                    int item_var_value_int_new = item_var_value_int_old + add_value_int;
                    iter_left->second = Int_To_Str(item_var_value_int_new);
                } else if (add_str.length() > 0 && add_str[0] == '.') { // Case 2: VAR add VAR
                    map<string, string>::iterator iter_right = Values_Map.find(add_str.substr(1));
                    if (iter_right != Values_Map.end()) {
                        string add_var_value = iter_right->second;
                        if (is_try_add_int && Str_Is_Int(item_var_value_old) && Str_Is_Int(add_var_value)) { // Case 2.1: VAR_INT add VAR_INT
                            int item_var_value_int_old = Str_To_Int(item_var_value_old);
                            int add_value_int = Str_To_Int(add_var_value);
                            int item_var_value_int_new = item_var_value_int_old + add_value_int;
                            iter_left->second = Int_To_Str(item_var_value_int_new);
                        } else { // Case 2.2: VAR add VAR as str
                            string item_var_value_new = item_var_value_old + add_var_value;
                            iter_left->second = item_var_value_new;
                        }
                    } else {
                        Cli_Output.Output_Str(add_str + " - Not Found");
                        Cli_Output.Output_NewLine();
                    }
                } else { // Case 3: VAR add STR
                    string item_var_value_new = item_var_value_old + Str_Without_Commas.Get(add_str);
                    iter_left->second = item_var_value_new;
                }
                found = true;
            }
        }
        if (!found) {
            Cli_Output.Output_Str(var_name + " - Not Found");
            Cli_Output.Output_NewLine();
            if (add_str.length() > 0 && add_str[0] == '.') {
                map<string, string>::iterator iter_right = Values_Map.find(add_str.substr(1));
                if (iter_right == Values_Map.end()) {
                    Cli_Output.Output_Str(add_str + " - Not Found");
                    Cli_Output.Output_NewLine();
                }
            }
        }
        return true;
    }

    bool var_delete(string point_var_name_str) {
        string var_name = point_var_name_str.substr(1);
        bool found = false;
        for (map<string, string>::iterator iter = Values_Map.begin(); iter != Values_Map.end(); iter++) {
            string item_var_name = iter->first;
            if (Str_Filter.Is_Match(var_name, item_var_name)) {
                Values_Map.erase(iter);
                found = true;
            }
        }
        if (!found) {
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

                // <editor-fold defaultstate="collapsed" desc="Vars: add int/var/str">

            case CMD_ID_point_var_name_add_str:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                string add_str = cmd->Items[2]->Value_Str;
                bool is_try_add_int;
                return var_add(point_var_name_str, add_str, is_try_add_int = true);
            }
            case CMD_ID_point_var_name_stradd_str:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                string add_str = cmd->Items[2]->Value_Str;
                bool is_try_add_int;
                return var_add(point_var_name_str, add_str, is_try_add_int = false);
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
        // Nothing
    }

};

#endif /* CLI_MODULE_VARS_H */
