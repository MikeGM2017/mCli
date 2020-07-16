/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_CMD_Processor.h
 * Author: mike
 *
 * Created on July 16, 2020, 11:56 AM
 */

#ifndef CLI_CMD_PROCESSOR_H
#define CLI_CMD_PROCESSOR_H

#include <vector>

using namespace std;

#include "Cli_CMD_Processor_Abstract.h"

#include "Cli_Output_Abstract.h"

#include "Level_Description.h"

class Cli_CMD_Processor : public Cli_CMD_Processor_Abstract {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;

    vector<Level_Description> &Levels;
    Cmd_Token_Parser &Token_Parser;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    string Str_Rem;

public:

    Cli_CMD_Processor(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            vector<Level_Description> &levels, Cmd_Token_Parser &parser,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            string str_rem) :
    User_Privilege(user_privilege), Modules(modules),
    Levels(levels), Token_Parser(parser),
    Cli_Input(cli_input), Cli_Output(cli_output),
    Str_Rem(str_rem) {
    }

    virtual ~Cli_CMD_Processor() {
    }

    virtual bool Do(string s_trim, bool is_debug, bool &debug_res) {
        return false;
    }

    virtual string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() - 1;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end - 1 > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    virtual bool Process_Input_Item(Cli_Input_Item &input_item) {
        string s_trim = Str_Trim(input_item.Text_Get());

        if (s_trim.size() == 0) return false;

        if (!s_trim.empty()) {
            bool is_processed = false;
            bool is_debug = false;
            bool stop = false;
            Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
            vector<Cmd_Token *> tokens = Token_Parser.Parse(s_trim, Str_Rem, parse_res);
            for (int module = 0; module < Modules.Get_Size(); module++) {
                Cli_Module *module_ptr = Modules.Get(module);
                if (module_ptr) {
                    for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size() && !stop; cmd++) {
                        Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
                        if (cmd_ptr) {
                            Cmd_Item_Valid_Result res_cmd_valid = cmd_ptr->Is_Valid(tokens);
                            switch (res_cmd_valid) {
                                case CMD_ITEM_OK:
                                    Cli_Output.Output_NewLine();
                                    module_ptr->Execute(cmd_ptr->ID_Get(), cmd_ptr, Levels, is_debug);
                                    is_processed = true;
                                    stop = true;
                                    break;
                                case CMD_ITEM_ERROR:
                                case CMD_ITEM_NOT_MATCH:
                                    break;
                                default:
                                    Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str("ERROR: ");
                                    Cli_Output.Output_Str(s_trim);
                                    Cli_Output.Output_Str(" - ");
                                    Cli_Output.Output_Str(Cmd_Item_Valid_Result_Func::To_String(res_cmd_valid));
                                    //Cli_Output.Output_NewLine();
                            }
                        }
                    }
                }
            }
            if (!is_processed) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(s_trim);
                Cli_Output.Output_Str(" - Not Processed");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_NewLine();
        }
        return true; // Ok
    }

};

#endif /* CLI_CMD_PROCESSOR_H */
