/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Script.h
 * Author: mike
 *
 * Created on July 16, 2020, 11:20 AM
 */

#ifndef CLI_MODULE_BASE_SCRIPT_H
#define CLI_MODULE_BASE_SCRIPT_H

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

#include "Cli_CMD_Processor_Abstract.h"

#include "Cli_History.h"

#include "Cli_Input_Abstract.h"
#include "Cli_Output_Abstract.h"

class Cli_Module_Base_Script : public Cli_Module {
protected:

    Cli_History &History;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    bool &Cmd_Script_Stop;
    bool &Cmd_Quit;

    char *Script_Buf;
    int Script_Buf_Size;

    Cli_CMD_Processor_Abstract &Cli_Command_Processor;

    string Str_Rem;

    string &Script_Command_Str;
    string &Script_Label_Str;

    string &Script_Dir_Str;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_do_script,
        CMD_ID_do_script_no_history,
        CMD_ID_do_script_stop,
        CMD_ID_save_history_as_script,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Script(Cli_History &history,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            string str_rem, bool &cmd_script_stop, bool &cmd_quit, int script_buf_size,
            Cli_CMD_Processor_Abstract &cli_command_processor,
            string &script_command_str, string &script_label_str, string &script_dir_str) : Cli_Module("Base Script"),
    History(history), Cli_Input(cli_input), Cli_Output(cli_output),
    Str_Rem(str_rem),
    Cmd_Script_Stop(cmd_script_stop), Cmd_Quit(cmd_quit), Script_Buf_Size(script_buf_size),
    Cli_Command_Processor(cli_command_processor),
    Script_Command_Str(script_command_str), Script_Label_Str(script_label_str), Script_Dir_Str(script_dir_str) {

        Version = "0.02";

        Script_Buf = new char[Script_Buf_Size];

        struct stat st = {0};

        if (stat(Script_Dir_Str.c_str(), &st) == -1) {
            mkdir(Script_Dir_Str.c_str(), 0700);
        }

        {
            // do script stop // @Attention: Must be before do script "file"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_stop, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("do script stop");
            cmd->Help_Set("stop execute script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "stop execute script"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("do script \"<file>\"");
            cmd->Help_Set("execute script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>" no history
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_no_history, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("do script \"<file>\" no history");
            cmd->Help_Set("execute script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "not save to history"));
            Cmd_Add(cmd);
        }
        {
            // save history as script "<file>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_save_history_as_script);
            cmd->Text_Set("save history as script \"<file>\"");
            cmd->Help_Set("save history as script to file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("save", "save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "save history"));
            cmd->Item_Add(new Cmd_Item_Word("as", "save history as"));
            cmd->Item_Add(new Cmd_Item_Word("script", "save history as script to file"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Script() {
        delete[] Script_Buf;
    }

    bool script_filename_check(string s) {
        if (s.length() == 0) return false; // Failed
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') continue; // Ok
            if (c >= 'A' && c <= 'Z') continue; // Ok
            if (c >= '0' && c <= '9') continue; // Ok
            if (c == '_') continue; // Ok
            return false; // Failed
        }
        return true; // Ok
    }

    bool save_history_as_script(Cli_Cmd *cmd) {

        string cmd_filename = cmd->Items[4]->Value_Str;

        bool res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        string filename = Script_Dir_Str + "/" + cmd_filename;
        FILE *h = fopen(filename.c_str(), "wt");
        if (h) {
            for (int i = 0; i < History.History_Size_Get() - 1; i++) // @Attention : Last cmd not saved!
                fprintf(h, "%s\n", History.History_Item_Get(i).c_str());
            fclose(h);
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Script saved from history as " + filename);
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not open file " + filename + " for write");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() ? (s.size() - 1) : 0;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    bool Execute_Command_check_goto_label(FILE *h, string &label_str) {
        bool stop = false;
        bool found = false;
        char *s;
        fseek(h, 0, SEEK_SET);
        do {
            s = fgets(Script_Buf, Script_Buf_Size, h);
            if (s) {
                char *s1 = strstr(s, "check");
                if (s1) {
                    char *s2 = strstr(s1, "label");
                    if (s2) {
                        char *s3 = strstr(s2, label_str.c_str());
                        if (s3) {
                            found = true;
                            stop = true; // Ok - Label Found
                        }
                    }
                }
            } else {
                stop = true; // Failed - Label Not Found
            }
        } while (!stop);
        return found;
    }

    void Execute_Script_Command(bool is_debug, bool &debug_res) {
        string Script_Command_Str_Trim1 = Str_Trim(Script_Command_Str);
        bool is_commas_found = false;
        if (Script_Command_Str_Trim1.size() >= 2
                && Script_Command_Str_Trim1[0] == '\"'
                && Script_Command_Str_Trim1[Script_Command_Str_Trim1.size() - 1] == '\"') {
            is_commas_found = true;
        }
        if (Script_Command_Str_Trim1.size() >= 2
                && Script_Command_Str_Trim1[0] == '\''
                && Script_Command_Str_Trim1[Script_Command_Str_Trim1.size() - 1] == '\'') {
            is_commas_found = true;
        }
        string Script_Command_Str_Trim2;
        if (is_commas_found) {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1.substr(1, Script_Command_Str_Trim1.size() - 2);
        } else {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1;
        }
        Cli_Input_Item input_item2(CLI_INPUT_ITEM_TYPE_STR, Script_Command_Str_Trim2);
        Script_Command_Str.clear();
        Cli_Command_Processor.Process_Input_Item(input_item2, is_debug, debug_res);
    }

    bool do_script(Cli_Cmd *cmd, bool is_no_history) {

        string cmd_filename = cmd->Items[2]->Value_Str;

        bool res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        string filename = Script_Dir_Str + "/" + cmd_filename;

        Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

        FILE *h = fopen(filename.c_str(), "rt");
        if (h) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - Begin");
            Cli_Output.Output_NewLine();
            bool is_debug = false;
            bool debug_res = false;
            char *s;
            Cmd_Script_Stop = false;
            do {
                if (!Cli_Input.Is_Ctrl_C_Pressed_Get()) {
                    s = fgets(Script_Buf, Script_Buf_Size, h);
                    if (s) {
                        string s_trim = Str_Trim(s);
                        if (!is_no_history && !is_debug) {
                            History.History_Put(s_trim);
                        }
                        Cli_Input_Item input_item(CLI_INPUT_ITEM_TYPE_STR, s_trim);
                        Cli_Output.Output_Str(s_trim);

                        Script_Command_Str.clear();
                        Script_Label_Str.clear();
                        Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);

                        if (Script_Command_Str.size()) {
                            Execute_Script_Command(is_debug, debug_res);
                            Script_Command_Str.clear();
                        }

                        //@Warning: Command "check goto <label>" - special case: is moves file position
                        if (Script_Label_Str.size()) {
                            bool label_found = Execute_Command_check_goto_label(h, Script_Label_Str);
                            if (!label_found) {
                                Cli_Output.Output_NewLine();
                                Cli_Output.Output_Str("ERROR: label \"" + Script_Label_Str + "\" - not found, script stopped");
                                Cli_Output.Output_NewLine();
                                Cmd_Script_Stop = true; // Stop - label not found
                            }
                            Script_Label_Str.clear();
                        }

                    }
                } else {
                    Cmd_Script_Stop = true; // Stop By Ctrl+C
                }
            } while (s && !Cmd_Script_Stop && !Cmd_Quit);
            if (Cli_Input.Is_Ctrl_C_Pressed_Get()) {
                Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - Stopped by Ctrl+C");
                Cli_Input.Is_Ctrl_C_Pressed_Clear();
            } else {
                Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - " + (Cmd_Script_Stop ? "Stopped" : "End"));
            }
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not open file " + filename + " for read");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {

            case CMD_ID_save_history_as_script:
                if (is_debug) return true;
                return save_history_as_script(cmd);
            case CMD_ID_do_script:
                if (is_debug) return true;
            {
                bool is_no_history = false;
                return do_script(cmd, is_no_history);
            }
                break;
            case CMD_ID_do_script_no_history:
                if (is_debug) return true;
            {
                bool is_no_history = true;
                return do_script(cmd, is_no_history);
            }
                break;
            case CMD_ID_do_script_stop:
                if (is_debug) return true;
                Cmd_Script_Stop = true;
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

#endif /* CLI_MODULE_BASE_SCRIPT_H */
