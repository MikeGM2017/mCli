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

    Cli_Output_Abstract &Cli_Output;

    string Level_Root;

public:

    enum Local_Cmd_ID {
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

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Level(Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output, string level_root) : Cli_Module("Base Level"),
    Cli_Input(cli_input), Cli_Output(cli_output), Level_Root(level_root) {

        Version = "0.02";

        {
            // level
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level);
            cmd->Text_Set("level");
            cmd->Help_Set("get current level");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
            Cmd_Add(cmd);
        }
        {
            // level get
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_get);
            cmd->Text_Set("level get");
            cmd->Help_Set("get current level");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
            cmd->Item_Add(new Cmd_Item_Word("get", "get"));
            Cmd_Add(cmd);
        }
        {
            // level get all
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_get_all);
            cmd->Text_Set("level get all");
            cmd->Help_Set("get all levels");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
            cmd->Item_Add(new Cmd_Item_Word("get", "get"));
            cmd->Item_Add(new Cmd_Item_Word("all", "all"));
            Cmd_Add(cmd);
        }

        {
            // level root
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_root);
            cmd->Text_Set("level root");
            cmd->Help_Set("set level to root");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
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
            // level up
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_up);
            cmd->Text_Set("level up");
            cmd->Help_Set("up level");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
            cmd->Item_Add(new Cmd_Item_Word("up", "up level"));
            Cmd_Add(cmd);
        }
        {
            // level <str>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_level_str);
            cmd->Text_Set("level <str>");
            cmd->Help_Set("set level to <str>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("level", "level"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "set level to <str>"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Level() {
    }

    bool level_get() {
        Cli_Output.Output_Str("Current Level: " + Cli_Input.Level_Get());
        Cli_Output.Output_NewLine();
        return true;
    }

    bool level_get_all(vector<Level_Description> &Levels) {
        if (Levels.size() > 0) {
            stringstream s_str;
            s_str << "Levels[" << Levels.size() << "]:";
            Cli_Output.Output_Str(s_str.str());
            Cli_Output.Output_NewLine();
            for (int i = 0; i < Levels.size(); i++) {
                Level_Description &item = Levels[i];
                string level = item.Level;
                string parameter = item.Parameter;
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

    bool level_root(vector<Level_Description> &Levels) {
        Levels.clear();
        Cli_Input.Level_Set(Level_Root);
        return true;
    }

    bool level_up(vector<Level_Description> &Levels) {
        if (Levels.size() > 1) {
            string level_new = Levels[Levels.size() - 2].Level;
            Levels.erase(Levels.begin() + Levels.size() - 1);
            Cli_Input.Level_Set(level_new);
        } else {
            level_root(Levels);
        }
        return true;
    }

    bool level_str(vector<Level_Description> &Levels, string level_new) {
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
            if (!level_new.empty()) {
                Levels.push_back(level_new);
            }
        }
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
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
                    string level_new = cmd->Items[1]->Value_Str;
                    return level_str(Levels, level_new);
                }
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        values_map["Level"] = Cli_Input.Level_Get();
    }

};

#endif /* CLI_MODULE_BASE_LEVEL_H */
