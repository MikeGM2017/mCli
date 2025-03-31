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

    class Do_Exit : public Do_Abstract {
    protected:

        bool &Cmd_Exit;

    public:

        Do_Exit(bool &cmd_exit) : Cmd_Exit(cmd_exit) {
        }

        virtual void Do(string s = "") {
            Cmd_Exit = Is_Yes(s);
        }

    };

    class Do_Quit : public Do_Abstract {
    protected:

        bool &Cmd_Quit;

    public:

        Do_Quit(bool &cmd_quit) : Cmd_Quit(cmd_quit) {
        }

        virtual void Do(string s = "") {
            Cmd_Quit = Is_Yes(s);
        }

    };

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    bool &Cmd_Exit;
    bool &Cmd_Quit;

    Do_Exit *Do_Exit_Object;
    Do_Quit *Do_Quit_Object;

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

    Cli_Module_Base_Quit(Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            bool &cmd_exit, bool &cmd_quit) : Cli_Module("Base Quit"),
    Cli_Input(cli_input), Cli_Output(cli_output), Cmd_Exit(cmd_exit), Cmd_Quit(cmd_quit) {

        Version = "0.05";

        Do_Exit_Object = new Do_Exit(cmd_exit);
        Do_Quit_Object = new Do_Quit(cmd_quit);

        {
            // E - exit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit_E, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("E");
            cmd->Help_Set("exit from program (forced)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("E", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // Q - quit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit_Q);
            cmd->Text_Set("Q");
            cmd->Help_Set("exit from program (forced)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("Q", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // exit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("exit");
            cmd->Help_Set("exit from program (with confirmation)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            Cmd_Add(cmd);
        }
        {
            // exit force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_exit_force, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("exit force");
            cmd->Help_Set("exit from program (forced)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("exit", "exit from program"));
            cmd->Item_Add(new Cmd_Item_Word("force", "exit from program (forced)"));
            Cmd_Add(cmd);
        }
        {
            // quit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit);
            cmd->Text_Set("quit");
            cmd->Help_Set("exit from program (with confirmation)");
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

    void Cli_Exit_Ask() {
        string s_question = "Exit(with Logout)?(y/n):";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_question);

        Cli_Input.Input_Mode_Set(INPUT_MODE_PROMPT);
        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Do_Object_Set(Do_Exit_Object);
    }

    void Cli_Quit_Ask() {
        string s_question = "Quit(without Logout)?(y/n):";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_question);

        Cli_Input.Input_Mode_Set(INPUT_MODE_PROMPT);
        Cli_Input.Input_Str_Set_Empty();
        Cli_Input.Do_Object_Set(Do_Quit_Object);
    }

    virtual ~Cli_Module_Base_Quit() {
        delete Do_Exit_Object;
        delete Do_Quit_Object;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_quit:
                if (is_debug) return true;
                Cli_Quit_Ask();
                return true;
            case CMD_ID_quit_Q:
            case CMD_ID_quit_force:
                if (is_debug) return true;
                Cmd_Quit = true;
                return true;
            case CMD_ID_exit:
                if (is_debug) return true;
                Cli_Exit_Ask();
                return true;
            case CMD_ID_exit_E:
            case CMD_ID_exit_force:
                if (is_debug) return true;
                Cmd_Exit = true;
                return true;
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_QUIT_H */
