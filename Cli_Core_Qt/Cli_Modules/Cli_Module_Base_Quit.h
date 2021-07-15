/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Quit.h
 * Author: mike
 *
 * Created on June 28, 2019, 4:14 PM
 */

#ifndef CLI_MODULE_BASE_QUIT_H
#define CLI_MODULE_BASE_QUIT_H

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"

class Cli_Module_Base_Quit : public Cli_Module {
protected:

    bool &Cmd_Quit;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_quit,
        CMD_ID_quit_Q,
        CMD_ID_quit_force,
        CMD_ID_exit,
        CMD_ID_exit_E,
        CMD_ID_exit_force,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Quit(bool &cmd_quit) : Cli_Module("Base Quit"), Cmd_Quit(cmd_quit) {
        {
            // E - exit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit_E);
            cmd->Text_Set("E");
            cmd->Help_Set("exit from program");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("E", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit);
            cmd->Text_Set("exit");
            cmd->Help_Set("exit from program");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit_force);
            cmd->Text_Set("exit force");
            cmd->Help_Set("exit from program (forced)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            cmd->Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // Q - quit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit_Q);
            cmd->Text_Set("Q");
            cmd->Help_Set("exit from program");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("Q", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // quit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit);
            cmd->Text_Set("quit");
            cmd->Help_Set("exit from program");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("quit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // quit force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit_force);
            cmd->Text_Set("quit force");
            cmd->Help_Set("exit from program (forced)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("quit", "exit from program"));
            cmd->Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Quit() {
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_quit:
            case CMD_ID_quit_Q:
            case CMD_ID_quit_force:
            case CMD_ID_exit:
            case CMD_ID_exit_E:
            case CMD_ID_exit_force:
                if (is_debug) return true;
                Cmd_Quit = true;
                return true;

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_QUIT_H */
