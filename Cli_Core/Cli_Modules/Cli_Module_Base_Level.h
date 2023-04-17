/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Level.h
 * Author: mike
 *
 * Created on September 2, 2022, 4:41 PM
 */

#ifndef CLI_MODULE_BASE_LEVEL_H
#define CLI_MODULE_BASE_LEVEL_H

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

class Cli_Module_Base_Level : public Cli_Module {
protected:

    Cli_Input_Abstract &Cli_Input;

    string Level_Root;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_level_root,
        CMD_ID_level_root_quick,
        CMD_ID_level_str,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Level(Cli_Input_Abstract &cli_input, string level_root) : Cli_Module("Base Level"),
    Cli_Input(cli_input), Level_Root(level_root) {
        {
            // level root
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_root);
            cmd->Text_Set("level root");
            cmd->Help_Set("set level to root");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "set level"));
            cmd->Item_Add(new Cmd_Item_Word("root", "set level"));
            Cmd_Add(cmd);
        }
        {
            // level root quick
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_root_quick);
            cmd->Text_Set("!");
            cmd->Help_Set("set level to root");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Base("!", "set level to root"));
            Cmd_Add(cmd);
        }
        {
            // level <str>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_str);
            cmd->Text_Set("level <str>");
            cmd->Help_Set("set level to <str>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "set level"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "set level to <str>"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Level() {
    }

    bool level_root(vector<Level_Description>& Levels) {
        Levels.clear();
        Cli_Input.Level_Set(Level_Root);
        return true;
    }

    bool level_str(vector<Level_Description>& Levels, string level_new) {
        string level_prev = Cli_Input.Level_Get();
        if (level_new.size() >= 2) {
            if (level_new[0] == '\"' && level_new[level_new.size() - 1] == '\"') {
                level_new = level_new.substr(1, level_new.size() - 2);
            }
            if (level_new[0] == '\'' && level_new[level_new.size() - 1] == '\'') {
                level_new = level_new.substr(1, level_new.size() - 2);
            }
        }
        if (level_new.empty()) {
            Levels.clear();
            Cli_Input.Level_Set(Level_Root);
        } else if (level_prev != level_new) {
            Cli_Input.Level_Set(level_new);
            if (!level_prev.empty()) {
                Levels.push_back(level_prev);
            }
            Levels.push_back(level_new);
        }
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_level_root:
            case CMD_ID_level_root_quick:
                if (is_debug) return true;
                return level_root(Levels);
            case CMD_ID_level_str:
            {
                if (is_debug) return true;
                string level_new = cmd->Items[1]->Value_Str;
                return level_str(Levels, level_new);
            }
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_LEVEL_H */
