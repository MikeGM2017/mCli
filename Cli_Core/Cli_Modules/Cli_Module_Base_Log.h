/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Log.h
 * Author: mike
 *
 * Created on July 15, 2020, 4:47 PM
 */

#ifndef CLI_MODULE_BASE_LOG_H
#define CLI_MODULE_BASE_LOG_H

#include "Cli_Module.h"

#include "Cli_Input_Abstract.h"

#include "Cmd_Item_Word.h"

class Cli_Module_Base_Log : public Cli_Module {
protected:

    Cli_Input_Abstract &Cli_Input;

public:

    enum Local_CmdID {
        CMD_ID_NO,

        CMD_ID_log_clear,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Log(Cli_Input_Abstract &cli_input) : Cli_Module("Base Log"), Cli_Input(cli_input) {
        {
            // log clear
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_log_clear);
            cmd->Text_Set("log clear");
            cmd->Help_Set("clear log");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("log", "log"));
            cmd->Item_Add(new Cmd_Item_Word("clear", "log clear"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Log() {
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd_id) {
            case CMD_ID_log_clear:
                if (is_debug) return true;
                Cli_Input.Input_Clear();
                return true;
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_LOG_H */
