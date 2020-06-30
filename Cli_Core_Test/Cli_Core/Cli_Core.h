/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Core.h
 * Author: mike
 *
 * Created on June 5, 2020, 11:03 AM
 */

#ifndef CLI_CORE_H
#define CLI_CORE_H

#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

#include "Cli_Input_Item.h"

#include "Cli_Modules.h"

#include "Cmd_Token_Parser.h"

#include "Level_Description.h"

#include "Cmd_Item_Valid_Result_Func.h"

#include "TAB_Cmd.h"

class Cli_Cmd_Tab {
public:

    Cli_Cmd *cmd_ptr;
    string s_log;
    string s_add;
    string s_full;
    bool Is_Enter;
    bool is_space_after_add;

    Cli_Cmd_Tab() : cmd_ptr(NULL), Is_Enter(false), is_space_after_add(false) {
    }

};

class Cli_Core {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;

    Cmd_Token_Parser &Token_Parser;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    vector<Level_Description> Levels;

public:

    Cli_Core(Cli_Cmd_Privilege_ID user_privilege, Cmd_Token_Parser &parser,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output) :
    User_Privilege(user_privilege), Token_Parser(parser), Cli_Input(cli_input), Cli_Output(cli_output) {
    }

    virtual ~Cli_Core() {
    }

    virtual Level_Description Level_Get() {
        if (Levels.size() > 0) {
            return Levels[Levels.size() - 1];
        }
        Level_Description level_top;
        return level_top;
    }

    virtual string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() - 1;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end - 1 > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    virtual bool Process_Input_Item(Cli_Modules &modules, Cli_Input_Item &input_item, const string str_rem) {
        string s_trim = Str_Trim(input_item.Text_Get());

        if (s_trim.size() == 0) return false;

        if (!s_trim.empty()) {
            bool is_processed = false;
            bool is_debug = false;
            bool stop = false;
            Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
            vector<Cmd_Token *> tokens = Token_Parser.Parse(s_trim, str_rem, parse_res);
            for (int module = 0; module < modules.Get_Size(); module++) {
                Cli_Module *module_ptr = modules.Get(module);
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

    virtual void Tab_Cmd_Add_By_Level(Cli_Cmd *cmd_ptr, string &level, list<string> &str_list) {
        if (cmd_ptr->Is_Global_Get() || (cmd_ptr->Level_Get() == level && User_Privilege <= cmd_ptr->Privilege_Get())) {
            string s = cmd_ptr->Items[0]->Text_Get();
            if (find(str_list.begin(), str_list.end(), s) == str_list.end()) {
                str_list.insert(str_list.end(), s);
            }
        }
    }

    virtual string TAB_Help_Get(string level, Cli_Modules &modules) {
        list<string> str_list;

        str_list.insert(str_list.end(), "H");
        str_list.insert(str_list.end(), "Q");
        str_list.insert(str_list.end(), "E");

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (module_ptr) {
                for (int cmd = 0; cmd < module_ptr->Cmd_Count_Get(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Cmd_Get(cmd);
                    if (cmd_ptr) {
                        Tab_Cmd_Add_By_Level(cmd_ptr, level, str_list);
                    }
                }
            }
        }

        stringstream s_str;
        for (list<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++)
            s_str << " " << *iter;

        return s_str.str();
    }

    virtual void TAB_Cmd_List_Get_With_Flags(
            // in
            const string level, Cli_Modules &modules, const string s_cmd_in, const vector<Cmd_Token *> &tokens,
            // out
            string &s_log, string &s_add,
            bool &Is_Log, bool &Is_Add, bool &Is_Space_Before, bool &Is_Space_After) {

        vector<Cli_Cmd_Tab *> cmd_tab_list;

        bool is_last_space = false;
        if (!s_cmd_in.empty()) {
            if (s_cmd_in[s_cmd_in.size() - 1] == ' ')
                is_last_space = true;
        }

        // <editor-fold defaultstate="collapsed" desc="TAB: last cmd item - full/partial -> cmd_tab_list">
        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (module_ptr) {
                for (int cmd = 0; cmd < module_ptr->Cmd_Count_Get(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Cmd_Get(cmd);
                    if (cmd_ptr) {
                        if (tokens.size() <= cmd_ptr->Items.size()) {
                            bool is_valid = true;
                            for (int token = 0; token < tokens.size(); token++) {
                                Cmd_Item_Base *cmd_item_ptr = cmd_ptr->Items[token];
                                Cmd_Token *token_ptr = tokens[token];
                                Cmd_Item_Valid_Result res_parse = cmd_item_ptr->Parse(token_ptr->Text_Get());
                                if (token < tokens.size() - 1) {
                                    if (res_parse != CMD_ITEM_OK) {
                                        is_valid = false;
                                        break;
                                    }
                                } else if (token == tokens.size() - 1) {
                                    if (res_parse == CMD_ITEM_OK) {
                                        if (token < cmd_ptr->Items.size() - 1) {
                                            Cli_Cmd_Tab *cmd_tab_ptr = new Cli_Cmd_Tab;
                                            cmd_tab_ptr->cmd_ptr = cmd_ptr;
                                            cmd_tab_ptr->is_space_after_add =
                                                    cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());

                                            //if (cmd_tab_ptr->is_space_after)
                                            if (is_last_space)
                                                cmd_tab_ptr->s_log = cmd_ptr->Items[token + 1]->Text_Get();
                                            else
                                                cmd_tab_ptr->s_log = cmd_item_ptr->Text_Get();

                                            cmd_tab_list.push_back(cmd_tab_ptr);
                                        } else if (token == cmd_ptr->Items.size() - 1) {
                                            Cli_Cmd_Tab *cmd_tab_ptr = new Cli_Cmd_Tab;
                                            cmd_tab_ptr->cmd_ptr = cmd_ptr;
                                            cmd_tab_ptr->Is_Enter = true;
                                            cmd_tab_ptr->s_log = cmd_item_ptr->Text_Get();
                                            cmd_tab_ptr->is_space_after_add =
                                                    cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
                                            cmd_tab_list.push_back(cmd_tab_ptr);
                                        }
                                    } else if (res_parse == CMD_ITEM_INCOMPLETE) {
                                        string token_str = tokens[token]->Text_Get();
                                        string cmd_item_str = cmd_item_ptr->Text_Get();
                                        if (token_str.size() < cmd_item_str.size()) {
                                            string s_incomplete_tail = cmd_item_ptr->Incomplete_Tail_Get(token_str);
                                            if (!s_incomplete_tail.empty()) {
                                                Cli_Cmd_Tab *cmd_tab_ptr = new Cli_Cmd_Tab;
                                                cmd_tab_ptr->cmd_ptr = cmd_ptr;
                                                cmd_tab_ptr->s_add = s_incomplete_tail;
                                                cmd_tab_ptr->s_full = cmd_item_str;
                                                cmd_tab_ptr->is_space_after_add =
                                                        cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
                                                cmd_tab_list.push_back(cmd_tab_ptr);
                                            } else if (s_incomplete_tail.empty()) {
                                                Cli_Cmd_Tab *cmd_tab_ptr = new Cli_Cmd_Tab;
                                                cmd_tab_ptr->cmd_ptr = cmd_ptr;
                                                cmd_tab_ptr->s_log = cmd_item_str;
                                                cmd_tab_ptr->is_space_after_add =
                                                        cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
                                                cmd_tab_list.push_back(cmd_tab_ptr);
                                            }
                                        }
                                    } else {
                                        is_valid = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="TAB: cmd_tab_list -> Output: s_log,Is_Log / s_add,Is_Add">
        bool Is_Enter = false;
        set<string> s_log_set;
        vector<string> s_log_vector;
        set<string> s_add_set;
        int add_count = 0;
        bool is_block_space_after = false;

        for (int i = 0; i < cmd_tab_list.size(); i++) {
            Cli_Cmd_Tab *cmd_tab_ptr = cmd_tab_list[i];
            if (!cmd_tab_ptr->s_add.empty()) {
                if (s_add_set.find(cmd_tab_ptr->s_add) == s_add_set.end()) {
                    s_add_set.insert(cmd_tab_ptr->s_add);
                    add_count++;
                }
            }
            if (!cmd_tab_ptr->is_space_after_add) {
                is_block_space_after = true;
            }
        }

        for (int i = 0; i < cmd_tab_list.size(); i++) {
            Cli_Cmd_Tab *cmd_tab_ptr = cmd_tab_list[i];
            if (!cmd_tab_ptr->s_log.empty()) {
                if (cmd_tab_ptr->Is_Enter) {
                    Is_Enter = true;
                } else {
                    Is_Log = true;
                    if (s_log_set.find(cmd_tab_ptr->s_log) == s_log_set.end()) {
                        s_log_set.insert(cmd_tab_ptr->s_log);
                        s_log_vector.push_back(cmd_tab_ptr->s_log);
                    }
                }
            }
            if (!cmd_tab_ptr->s_add.empty()) {
                if (add_count == 1) {
                    s_add = cmd_tab_ptr->s_add;
                    Is_Add = true;
                } else if (add_count > 1) {
                    Is_Log = true;
                    if (s_log_set.find(cmd_tab_ptr->s_full) == s_log_set.end()) {
                        s_log_set.insert(cmd_tab_ptr->s_full);
                        s_log_vector.push_back(cmd_tab_ptr->s_full);
                    }
                }
            }
        }

        if (!is_block_space_after) {
            if (!is_last_space &&
                    ((!Is_Add && Is_Log && !Is_Enter && s_log_vector.size() == 1)
                    || (!Is_Add && Is_Log && Is_Enter && s_log_vector.size() >= 1)
                    || (!Is_Add && add_count == 0 && Is_Log && !Is_Enter && s_log_vector.size() >= 1))) {
                Is_Add = false;
                Is_Log = false;
                Is_Enter = false;
                Is_Space_After = true;
            }
        }

        if (Is_Log) {
            for (int i = 0; i < s_log_vector.size(); i++) {
                s_log += " ";
                s_log += s_log_vector[i];
            }
        }

        if (Is_Enter) {
            s_log += " ";
            s_log += "<Enter>";
            Is_Log = true;
        }
        // </editor-fold>

    }

    virtual vector<TAB_Cmd *> TAB_Cmd_List_Get(const string level, Cli_Modules &modules, const string s_cmd_in, const vector<Cmd_Token *> &tokens) {
        vector<TAB_Cmd *> tab_cmd_list;

        string s_log;
        string s_add;

        bool Is_Log = false;
        bool Is_Add = false;
        bool Is_Space_Before = false;
        bool Is_Space_After = false;

        TAB_Cmd_List_Get_With_Flags(
                // in
                level, modules, s_cmd_in, tokens,
                // out
                s_log, s_add,
                Is_Log, Is_Add, Is_Space_Before, Is_Space_After);

        if (Is_Log)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_LOG_PRINT, s_log));
        if (Is_Space_Before)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_INPUT_CHECK_SPACE, ""));
        if (Is_Add)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_INPUT_ADD, s_add));
        if (Is_Space_After)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_INPUT_CHECK_SPACE, ""));

        return tab_cmd_list;
    }

    virtual void Process_Tab(Cli_Modules &modules, Cli_Input_Item &input_item, const string str_rem, bool &is_invitation_print) {
        vector<TAB_Cmd *> tab_cmd_list;
        string s_trim = Str_Trim(input_item.Text_Get());
        Level_Description level_description = Level_Get();
        string level = level_description.Level;
        string s_help;
        if (s_trim.size() == 0) {
            s_help = TAB_Help_Get(level, modules);
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_LOG_PRINT, s_help));
        } else {
            Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
            vector<Cmd_Token *> tokens = Token_Parser.Parse(s_trim, str_rem, parse_res);

            tab_cmd_list = TAB_Cmd_List_Get(level, modules, input_item.Text_Get(), tokens);

            for (int i = 0; i < tokens.size(); i++)
                delete tokens[i];
            tokens.clear();
        }

        if (tab_cmd_list.size()) {
            for (int tab_cmd = 0; tab_cmd < tab_cmd_list.size(); tab_cmd++) {
                TAB_Cmd *tab_cmd_ptr = tab_cmd_list[tab_cmd];
                if (tab_cmd_ptr) {
                    switch (tab_cmd_ptr->ID) {
                        case TAB_CMD_ID_LOG_PRINT:
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(tab_cmd_ptr->Text);
                            Cli_Output.Output_NewLine();
                            is_invitation_print = true;
                            break;
                        case TAB_CMD_ID_INPUT_ADD:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr->Text);
                            Cli_Input.Input_Str_Modified_To_Output(s_prev);
                            Cli_Input.Input_End();
                            is_invitation_print = false;
                        }
                            break;
                        case TAB_CMD_ID_INPUT_CHECK_SPACE:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            Cli_Input.Input_Str_Set(s_prev + " ");
                            Cli_Input.Input_Str_Modified_To_Output(s_prev);
                            Cli_Input.Input_End();
                            is_invitation_print = false;
                        }
                            break;
                    }
                }
            }

            for (int i = 0; i < tab_cmd_list.size(); i++)
                delete tab_cmd_list[i];
            tab_cmd_list.clear();

        } else {
            Cli_Output.Output_NewLine();
        }

    }

};

#endif /* CLI_CORE_H */
