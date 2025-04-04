/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Wait.h
 * Author: mike
 *
 * Created on July 16, 2020, 5:00 PM
 */

#ifndef CLI_MODULE_BASE_WAIT_H
#define CLI_MODULE_BASE_WAIT_H

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <sstream>

using namespace std;

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Int_Range.h"

class Cli_Module_Base_Wait : public Cli_Module {
protected:

    bool &Log_Wait_Enable;
    bool &Cmd_Wait_Stop;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_wait,
        CMD_ID_wait_log_enable,
        CMD_ID_wait_log_disable,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Wait(bool &log_wait_enable, bool &cmd_wait_stop,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output) : Cli_Module("Base Wait"),
    Log_Wait_Enable(log_wait_enable), Cmd_Wait_Stop(cmd_wait_stop),
    Cli_Input(cli_input), Cli_Output(cli_output) {
        Version = "0.02";
        {
            // wait <sec>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_wait, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("wait <sec>");
            cmd->Help_Set("wait <sec:1..60> (for use in scripts)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("wait", "wait <sec>"));
            cmd->Item_Add(new Cmd_Item_Int_Range(1, 60, "<1..60>", "wait time in sec"));
            Cmd_Add(cmd);
        }
        {
            // log wait enable
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_wait_log_enable, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("wait log enable");
            cmd->Help_Set("wait logging enable");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("wait", "wait"));
            cmd->Item_Add(new Cmd_Item_Word("log", "wait logging"));
            cmd->Item_Add(new Cmd_Item_Word("enable", "wait logging enable"));
            Cmd_Add(cmd);
        }
        {
            // log wait disable
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_wait_log_disable, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("wait log disable");
            cmd->Help_Set("wait logging disable");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("wait", "wait"));
            cmd->Item_Add(new Cmd_Item_Word("log", "wait logging"));
            cmd->Item_Add(new Cmd_Item_Word("disable", "wait logging disable"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Wait() {
    }

    bool wait(Cli_Cmd *cmd, bool log_wait_enable) {
        string token_value = cmd->Items[1]->Value_Str;
        int wait_sec = atoi(token_value.c_str());
        Cmd_Wait_Stop = false;
        Cli_Input.Is_Ctrl_C_Pressed_Clear();

        if (log_wait_enable) {
            Cli_Output.Output_Str("Wait (Press Enter to stop):");
            Cli_Output.Output_NewLine();
        }

        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Input_Mode_Set(INPUT_MODE_WAIT);
        Cli_Input.Wait_Count_Set(wait_sec);

        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_wait_log_enable:
                if (is_debug) return true;
                Log_Wait_Enable = true;
                return true;
            case CMD_ID_wait_log_disable:
                if (is_debug) return true;
                Log_Wait_Enable = false;
                return true;

            case CMD_ID_wait:
                if (is_debug) return true;
                return wait(cmd, Log_Wait_Enable);

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_WAIT_H */
