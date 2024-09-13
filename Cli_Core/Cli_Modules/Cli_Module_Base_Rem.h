/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Rem.h
 * Author: mike
 *
 * Created on June 28, 2019, 5:11 PM
 */

#ifndef CLI_MODULE_BASE_REM_H
#define CLI_MODULE_BASE_REM_H

#include "Cli_Module.h"

#include "Cli_Output_Abstract.h"

#include "Cmd_Item_Rem.h"

class Cli_Module_Base_Rem : public Cli_Module {
protected:

    Cli_Output_Abstract &Cli_Output;

public:

    // Step 1: define Local_Cmd_ID

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_rem,

        CMD_ID_LAST
    };

    // Step 2: override virtual int Cmd_ID_Count_Get() - return id-count of Local_Cmd_ID

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    // Step 3: constructor + commands

    Cli_Module_Base_Rem(string str_rem, Cli_Output_Abstract &cli_output) : Cli_Module("Base Rem"),
    Cli_Output(cli_output) {

        Version = "0.02";

        {
            // rem
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_rem);
            cmd->Text_Set(str_rem);
            cmd->Help_Set("comment (for use in scripts)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Rem(str_rem, "comment"));
            Cmd_Add(cmd);
        }
    }

    // Step 4: override destructor

    virtual ~Cli_Module_Base_Rem() {
    }

    // Step 5: override virtual bool Execute(...)

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_rem:
                if (is_debug) return true;
            {
                string s_rem = cmd->Items[0]->Value_Str;
                return rem(s_rem);
            }

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    // Step 6: functions for CMD_ID_XXX - Begin

    bool rem(string s_rem) {
        Cli_Output.Output_Str(s_rem);
        Cli_Output.Output_NewLine();
        return true;
    }

    // Step 6: functions for CMD_ID_XXX - End

    // Step 7: override virtual void To_Map(...)

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLIMODULE_BASE_REM_H */
