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

#include "Cli_Module.h"

#include "Cli_CMD_Processor_Abstract.h"

#include "Cli_History.h"

#include "Cli_Output_Abstract.h"

class Cli_Module_Base_Script : public Cli_Module {
protected:

    Cli_History &History;

    Cli_Output_Abstract &Cli_Output;

    bool &Cmd_Script_Stop;
    bool &Cmd_Quit;

    char *Script_Buf;
    int Script_Buf_Size;

    Cli_CMD_Processor_Abstract &Cli_Command_Processor;

    string Str_Rem;

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

    Cli_Module_Base_Script(Cli_History &history, Cli_Output_Abstract &cli_output,
            string str_rem, bool &cmd_script_stop, bool &cmd_quit, int script_buf_size,
            Cli_CMD_Processor_Abstract &cli_command_processor) : Cli_Module("Base Script"),
    History(history), Cli_Output(cli_output),
    Str_Rem(str_rem),
    Cmd_Script_Stop(cmd_script_stop), Cmd_Quit(cmd_quit), Script_Buf_Size(script_buf_size),
    Cli_Command_Processor(cli_command_processor) {

        Script_Buf = new char[Script_Buf_Size];

        {
            // do script stop // @Attention: Must be before do script "file"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_stop);
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
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script);
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
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_no_history);
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

    bool save_history_as_script(Cli_Cmd *cmd) {
        string filename = cmd->Items[4]->Value_Str;
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

    bool do_script(Cli_Cmd *cmd, bool is_no_history) {
        string filename = cmd->Items[2]->Value_Str;
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
                s = fgets(Script_Buf, Script_Buf_Size, h);
                if (s) {
                    string s_trim = Str_Trim(s);
                    if (!is_no_history && !is_debug) {
                        History.History_Put(s_trim);
                    }
                    Cli_Input_Item input_item(CLI_INPUT_ITEM_TYPE_STR, s_trim);
                    Cli_Output.Output_Str(s_trim);
                    Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                }
            } while (s && !Cmd_Script_Stop && !Cmd_Quit);
            Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - " + (Cmd_Script_Stop ? "Stopped" : "End"));
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
