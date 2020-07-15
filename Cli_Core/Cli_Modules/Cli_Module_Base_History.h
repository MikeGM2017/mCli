/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_History.h
 * Author: mike
 *
 * Created on June 28, 2019, 4:46 PM
 */

#ifndef CLI_MODULE_BASE_HISTORY_H
#define CLIMODULE_BASE_HISTORY_H

#include "Cli_Module.h"

#include "Cli_History.h"

class Cli_Module_Base_History : public Cli_Module {
protected:

    Cli_History &History;

    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_CmdID {
        CMD_ID_NO,

        CMD_ID_history,
        CMD_ID_history_show,
        CMD_ID_history_clear,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_History(Cli_History &history, Cli_Output_Abstract &cli_output) : Cli_Module("Base History"),
    History(history), Cli_Output(cli_output) {
        {
            // show history
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_history);
            cmd->Text_Set("history show");
            cmd->Help_Set("history show");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("history", "history"));
            Cmd_Add(cmd);
        }
        {
            // show history
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_history_show);
            cmd->Text_Set("history show");
            cmd->Help_Set("history show");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("history", "history"));
            cmd->Item_Add(new Cmd_Item_Word("show", "history show"));
            Cmd_Add(cmd);
        }
        {
            // clear history
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_history_clear);
            cmd->Text_Set("history clear");
            cmd->Help_Set("history clear");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("history", "history"));
            cmd->Item_Add(new Cmd_Item_Word("clear", "history clear"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_History() {
    }

    bool history_show() {
        Cli_Output.Output_Str("History:");
        Cli_Output.Output_NewLine();
        int history_size = History.History_Size_Get();
        for (int i = 0; i < (history_size - 1); i++) { // @Attention : Not show last cmd!
            Cli_Output.Output_Str(History.History_Item_Get(i));
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool history_clear() {
        History.Clear();
        return true;
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd->ID_Get()) {
            case CMD_ID_history:
            case CMD_ID_history_show:
                if (is_debug) return true;
                return history_show();
            case CMD_ID_history_clear:
                if (is_debug) return true;
                return history_clear();
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_HISTORY_H */
