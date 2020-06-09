/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Tab_Test.h
 * Author: mike
 *
 * Created on June 9, 2020, 11:53 AM
 */

#ifndef CLI_MODULE_TAB_TEST_H
#define CLI_MODULE_TAB_TEST_H

#include "Cli_Module.h"

class Cli_Module_Tab_Test : public Cli_Module {
public:

    enum Local_CmdID {
        CMD_ID_NO,

        CMD_ID_min,

        CMD_ID_min_min,
        CMD_ID_min_max,
        CMD_ID_min_mux_min,
        CMD_ID_min_middle_min,
        CMD_ID_min_middle_max,
        CMD_ID_min_mux_max,

        CMD_ID_max,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Tab_Test() : Cli_Module("Tab Test") {
        {
            // min
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min);
            cmd->Text_Set("min");
            cmd->Help_Set("min (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            Cmd_Add(cmd);
        }

        {
            // min min
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_min);
            cmd->Text_Set("min min");
            cmd->Help_Set("min min (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("min", "min min (tab test)"));
            Cmd_Add(cmd);
        }
        {
            // min max
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_max);
            cmd->Text_Set("min max");
            cmd->Help_Set("min max (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("max", "min max (tab test)"));
            Cmd_Add(cmd);
        }

        {
            // min min min
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_mux_min);
            cmd->Text_Set("min mux min");
            cmd->Help_Set("min mux min (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("mux", "min mux (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("min", "min mux min (tab test)"));
            Cmd_Add(cmd);
        }
        {
            // min middle min
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_middle_min);
            cmd->Text_Set("min middle min");
            cmd->Help_Set("min middle min (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("middle", "min middle (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("min", "min middle min (tab test)"));
            Cmd_Add(cmd);
        }
        {
            // min middle max
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_middle_max);
            cmd->Text_Set("min middle max");
            cmd->Help_Set("min middle max (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("middle", "min middle (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("max", "min middle max (tab test)"));
            Cmd_Add(cmd);
        }
        {
            // min min max
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_min_mux_max);
            cmd->Text_Set("min mux max");
            cmd->Help_Set("min mux max (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("min", "min (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("mux", "min mux (tab test)"));
            cmd->Item_Add(new Cmd_Item_Word("max", "min min max (tab test)"));
            Cmd_Add(cmd);
        }

        {
            // max
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_max);
            cmd->Text_Set("max");
            cmd->Help_Set("max (tab test)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("max", "max (tab test)"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Tab_Test() {
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd_id) {
            case CMD_ID_min:
            case CMD_ID_min_min:
            case CMD_ID_min_max:
            case CMD_ID_min_mux_min:
            case CMD_ID_min_middle_min:
            case CMD_ID_min_middle_max:
            case CMD_ID_min_mux_max:
            case CMD_ID_max:
                if (is_debug) return true;
                return true;
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_TAB_TEST_H */
