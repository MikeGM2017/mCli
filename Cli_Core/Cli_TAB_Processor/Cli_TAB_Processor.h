/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_TAB_Processor.h
 * Author: mike
 *
 * Created on July 16, 2020, 4:34 PM
 */

#ifndef CLI_TAB_PROCESSOR_H
#define CLI_TAB_PROCESSOR_H

#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

#include "Cli_TAB_Processor_Abstract.h"

#include "Cli_TAB_Result.h"

#include "Cli_Modules.h"
#include "Level_Description.h"
#include "Cmd_Token_Parser.h"
#include "Cli_Input_Abstract.h"
#include "Cli_Output_Abstract.h"
#include "TAB_Cmd.h"

class Cli_TAB_Processor : public Cli_TAB_Processor_Abstract {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;

    vector<Level_Description> &Levels;
    Cmd_Token_Parser &Token_Parser;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    string Str_Rem;

    vector<string> Log;
    bool Log_Is_Active;

public:

    Cli_TAB_Processor(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            vector<Level_Description> &levels, Cmd_Token_Parser &parser,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            string str_rem, bool log_is_active) :
    User_Privilege(user_privilege), Modules(modules),
    Levels(levels), Token_Parser(parser),
    Cli_Input(cli_input), Cli_Output(cli_output),
    Str_Rem(str_rem), Log_Is_Active(log_is_active) {
        Type = "Cli_TAB_Processor";
        Version = "0.02";
    }

    virtual Level_Description Level_Get() {
        if (Levels.size() > 0) {
            return Levels[Levels.size() - 1];
        }
        Level_Description level_top;
        return level_top;
    }

    int Log_Size_Get() {
        return Log.size();
    }

    string Log_Item_Get(int index) {
        if (index >= 0 && index < Log.size()) {
            return Log[index];
        }
        return "";
    }

    static string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() ? (s.size() - 1) : 0;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    virtual bool TAB_Cmd_Ptr_Check_By_Level(Cli_Cmd *cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, string level) {
        if (cmd_ptr && user_privilege <= cmd_ptr->Privilege_Get()) {
            if (cmd_ptr->Is_Global_Get()) return true;
            if (cmd_ptr->Level_Get() == level) return true;
        }
        return false;
    }

    virtual void TAB_Cmd_Add_By_Level(Cli_Cmd *cmd_ptr, string &level, list<string> &str_list) {
        bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level);
        if (is_cmd_prt_valid) {
            string s = cmd_ptr->Items[0]->Text_Get();
            if (find(str_list.begin(), str_list.end(), s) == str_list.end()) {
                str_list.insert(str_list.end(), s);
            }
        }
    }

    virtual string TAB_Help_Get(string level, Cli_Modules &modules) {
        list<string> str_list;

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (module_ptr) {
                for (int cmd = 0; cmd < module_ptr->Cmd_Count_Get(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Cmd_Get(cmd);
                    bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level);
                    if (is_cmd_prt_valid) {
                        TAB_Cmd_Add_By_Level(cmd_ptr, level, str_list);
                    }
                }
            }
        }

        stringstream s_str;
        for (list<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++)
            s_str << " " << *iter;

        return s_str.str();
    }

    void TAB_On_OK_CAN_CONTINUE(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;
        tab_result_ptr->Is_Enter = true;
        tab_result_ptr->s_log = ",";
        tab_result_ptr->is_space_after_add = false;
        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr, Cmd_Item_Base* cmd_item_ptr) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;
        tab_result_ptr->Is_Enter = true;
        //is_incomplete_str = true;
        tab_result_ptr->s_log = cmd_item_ptr->Text_Get();
        tab_result_ptr->is_space_after_add = false;
        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_OK_not_last_token(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr, int token, Cmd_Item_Base* cmd_item_ptr) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;

        //cmd_tab_ptr->is_space_after_add =
        //        cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
        if (token + 1 < cmd_ptr->Items.size() - 1) {
            tab_result_ptr->is_space_after_add =
                    cmd_item_ptr->Is_Space_After_Add(cmd_ptr->Items[token + 1]->Text_Get());
        } else {
            tab_result_ptr->is_space_after_add = false; // Next token - last token in cmd list
        }

        //if (is_last_space) {
        tab_result_ptr->s_log = cmd_ptr->Items[token + 1]->Text_Get();
        //cmd_tab_ptr->s_log_or_add = cmd_ptr->Items[token + 1]->Text_Get();
        //} else {
        //    cmd_tab_ptr->s_log = cmd_item_ptr->Text_Get();
        //    cmd_tab_ptr->s_log_or_add = cmd_item_ptr->Text_Get();
        //}

        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_OK_last_token(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr, Cmd_Item_Base* cmd_item_ptr, Cmd_Token* token_ptr) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;
        tab_result_ptr->Is_Enter = true;
        ////cmd_tab_ptr->s_log = cmd_item_ptr->Text_Get();

        //if (cmd_item_ptr->Type_Get() == "Str") {
        //    cmd_tab_ptr->s_log = cmd_item_ptr->Text_Get();
        //}

        //cmd_tab_ptr->s_log_or_add = cmd_item_ptr->Text_Get();
        tab_result_ptr->is_space_after_add =
                cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
        //cmd_tab_ptr->is_space_after_add = false;
        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_INCOMPLETE_STR(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr, Cmd_Item_Base* cmd_item_ptr) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;

        tab_result_ptr->s_log = cmd_item_ptr->Text_Get() + " - Incomplete";
        tab_result_ptr->is_space_after_add = false;
        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_incomplete_tail_list(vector<Cli_TAB_Result*>& tab_result_list, Cli_Cmd* cmd_ptr, int token, Cmd_Item_Base* cmd_item_ptr, Cmd_Token* token_ptr, string& token_str, vector<string>& s_incomplete_tail_list) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;
        tab_result_ptr->s_add_list = s_incomplete_tail_list;

        string s_beg;
        if (!token_str.empty()) {
            size_t pos = token_str.find_last_of(','); // @Magic: for Cmd_Item_Word_List
            if (pos == token_str.npos) {
                s_beg = token_str;
            } else {
                s_beg = token_str.substr(pos + 1); // @Magic: for Cmd_Item_Word_List
            }
        }

        for (int s_add_index = 0; s_add_index < tab_result_ptr->s_add_list.size(); s_add_index++) {
            string s_add_item = tab_result_ptr->s_add_list[s_add_index];
            tab_result_ptr->s_full_list.push_back(s_beg + s_add_item);
        }

        tab_result_ptr->is_space_after_add =
                cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());

        if (token == cmd_ptr->Items.size() - 1) { // Last token in cmd list
            //cmd_tab_ptr->Is_Enter = true;
            tab_result_ptr->is_space_after_add = false;
        }

        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_incomplete_tail_list_empty(vector<Cli_TAB_Result*>& tab_result_list, bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas, Cli_Cmd* cmd_ptr, Cmd_Item_Base* cmd_item_ptr, Cmd_Token* token_ptr, string& token_str, string& cmd_item_str) {
        Cli_TAB_Result *tab_result_ptr = new Cli_TAB_Result;
        tab_result_ptr->cmd_ptr = cmd_ptr;
        char last_token_char = (token_str.empty() ? 0 : token_str[token_str.size() - 1]);
        if (!is_last_char_space || last_token_char == ' ' || last_token_char == '\t') {
            tab_result_ptr->s_log = cmd_item_str + " - Incomplete";
        }
        if (!is_last_char_comma && !is_last_char_commas) {
            tab_result_ptr->is_space_after_add =
                    cmd_item_ptr->Is_Space_After_Add(token_ptr->Text_Get());
        } else {
            tab_result_ptr->is_space_after_add = false;
        }
        tab_result_list.push_back(tab_result_ptr);
    }

    void TAB_On_INCOMPLETE(const vector<Cmd_Token*>& tokens, vector<Cli_TAB_Result*>& tab_result_list,
            bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas,
            Cli_Cmd* cmd_ptr, int token, Cmd_Item_Base* cmd_item_ptr, Cmd_Token* token_ptr) {
        string token_str = tokens[token]->Text_Get();
        string cmd_item_str = cmd_item_ptr->Text_Get();
        vector<string> s_incomplete_tail_list;
        if (!is_last_char_space) {
            s_incomplete_tail_list = cmd_item_ptr->Incomplete_Tail_List_Get(token_str);
        }
        if (!s_incomplete_tail_list.empty()) {
            TAB_On_incomplete_tail_list(tab_result_list, cmd_ptr, token, cmd_item_ptr, token_ptr, token_str, s_incomplete_tail_list);
        } else if (s_incomplete_tail_list.empty()) {
            TAB_On_incomplete_tail_list_empty(tab_result_list, is_last_char_space,
                    is_last_char_comma, is_last_char_commas,
                    cmd_ptr, cmd_item_ptr, token_ptr, token_str, cmd_item_str);
        }
    }

    void TAB_Result_List_Parse_To_Flags(const vector<Cmd_Token*>& tokens, string& s_log, string& s_add,
            bool& Is_Log, bool& Is_Add, bool& Is_Space_After,
            vector<Cli_TAB_Result*>& tab_result_list,
            bool is_incomplete_str, bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas) {
        {

            bool Is_Enter = false;
            set<string> s_add_set;
            set<string> s_log_set;
            string s_add_1;
            string s_log_1;
            bool is_space_after_add_1 = false;
            bool is_space_after_log_1 = false;
            vector<string> s_add_vector;
            vector<string> s_log_vector;
            string s_add_full_1;

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result *tab_result_ptr = tab_result_list[i];
                if (tab_result_ptr->Is_Enter) {
                    Is_Enter = true;
                }
            }

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result *tab_result_ptr = tab_result_list[i];
                if (!tab_result_ptr->s_add_list.empty()) {
                    for (int s_add_index = 0; s_add_index < tab_result_ptr->s_add_list.size(); s_add_index++) {
                        string s_add_item = tab_result_ptr->s_add_list[s_add_index];
                        if (s_add_set.find(s_add_item) == s_add_set.end()) {
                            s_add_set.insert(s_add_item);
                            s_add_1 = s_add_item;
                            s_add_vector.push_back(tab_result_ptr->s_full_list[s_add_index]);
                            s_add_full_1 = tab_result_ptr->s_full_list[s_add_index];
                        }
                    }
                }
                if (tab_result_ptr->is_space_after_add)
                    is_space_after_add_1 = true;
            }

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result *tab_result_ptr = tab_result_list[i];
                if (!tab_result_ptr->s_log.empty()) {
                    if (s_log_set.find(tab_result_ptr->s_log) == s_log_set.end()) {
                        s_log_set.insert(tab_result_ptr->s_log);
                        s_log_1 = tab_result_ptr->s_log;
                        s_log_vector.push_back(tab_result_ptr->s_log);
                    }
                }
                if (tab_result_ptr->is_space_after_add)
                    is_space_after_log_1 = true;
            }

            Is_Log = false;
            s_log = "";
            Is_Add = false;
            s_add = "";
            Is_Space_After = false;

            if (s_add_vector.size() == 0 && s_log_vector.size() == 0) {
                s_log = (Is_Enter ? " <Enter>" : " <Error>");
            } else if (!Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 0) {
                s_add = s_add_1;
                if (is_space_after_add_1)
                    Is_Space_After = true;
                else
                    Is_Space_After = false;
            } else if (!Is_Enter && s_add_vector.size() == 0 && s_log_vector.size() == 1) {
                if (!s_log_1.empty() && s_log_1[0] != '<' && s_log_1[0] != '\"' && s_log_1[0] != '\'' && s_log_1[0] != '[') {
                    if (!is_last_char_space)
                        s_add = " " + s_log_1;
                    else
                        s_add = s_log_1;

                    if (is_space_after_log_1)
                        Is_Space_After = true;
                    else
                        Is_Space_After = false;
                } else {
                    s_log = " " + s_log_1;
                    if (!is_last_char_comma && !is_last_char_commas) {
                        Is_Space_After = true;
                    }
                }
            } else if (Is_Enter && s_add_vector.size() == 0 && s_log_vector.size() == 1) {
                s_log = " " + s_log_1 + " <Enter>";
                if (is_space_after_log_1)
                    Is_Space_After = true;
                else
                    Is_Space_After = false;
            } else if (!Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 1) {
                s_log = " " + s_log_1 + " " + s_add_full_1;
            } else if (Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 1) {
                s_add = s_add_1;
                Is_Space_After = true;
            } else if (s_add_vector.size() == 0 && s_log_vector.size() >= 2) {
                s_log = "";
                for (int i = 0; i < s_log_vector.size(); i++) {
                    s_log += " " + s_log_vector[i];
                }
                if (Is_Enter)
                    s_log += " <Enter>";
                Is_Space_After = true;
            } else if (!Is_Enter && s_add_vector.size() >= 2 && s_log_vector.size() == 0) {
                {
                    // Add minimal common part or log full variants
                    int len_min = s_add_vector[0].size();
                    for (int i = 0; i < s_add_vector.size(); i++) {
                        if (len_min > s_add_vector[i].size()) {
                            len_min = s_add_vector[i].size();
                        }
                    }
                    string s_common;
                    for (int pos = 0; pos < len_min; pos++) {
                        char c = s_add_vector[0][pos];
                        bool is_diff = false;
                        for (int i = 0; i < s_add_vector.size(); i++) {
                            if (s_add_vector[i][pos] != c) {
                                is_diff = true;
                                break;
                            }
                        }
                        if (!is_diff) {
                            s_common += c;
                        } else {
                            break;
                        }
                    }
                    string s_last_token1 = tokens[tokens.size() - 1]->Text_Get();
                    string s_last_token;
                    size_t pos = s_last_token1.find_last_of(','); // @Magic: for Cmd_Item_Word_List
                    if (pos == s_last_token1.npos) {
                        s_last_token = s_last_token1;
                    } else {
                        s_last_token = s_last_token1.substr(pos + 1); // @Magic: for Cmd_Item_Word_List
                    }
                    string s_common_part;
                    if (!s_common.empty()) {
                        s_common_part = s_common.substr(s_last_token.size());
                    }
                    if (!s_common_part.empty()) {
                        s_add = s_common_part;
                    } else {
                        s_log = "";
                        for (int i = 0; i < s_add_vector.size(); i++) {
                            s_log += " ";
                            s_log += s_add_vector[i];
                        }
                    }
                }
            } else if (s_add_vector.size() >= 2 || s_log_vector.size() >= 2) {
                s_log = "";
                for (int i = 0; i < s_log_vector.size(); i++) {
                    s_log += " ";
                    s_log += s_log_vector[i];
                }
                for (int i = 0; i < s_add_vector.size(); i++) {
                    s_log += " ";
                    s_log += s_add_vector[i];
                }
                if (Is_Enter)
                    s_log += " <Enter>";
            } else {
                s_log = " <Error>";
            }

            Is_Add = !s_add.empty();
            Is_Log = !s_log.empty();

            if (is_incomplete_str) {
                Is_Space_After = false;
            }
            if (is_last_char_space) {
                Is_Space_After = false;
            }

        }
    }

    virtual void TAB_Cmd_List_Get_With_Flags(
            // in
            Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            const string level, const string s_cmd_in, const string s_cmd_in_trim, const vector<Cmd_Token *> &tokens,
            // out
            string &s_log, string &s_add,
            bool &Is_Log, bool &Is_Add, bool &Is_Space_After) {

        vector<Cli_TAB_Result *> tab_result_list;

        bool is_incomplete_str = false;
        char last_char = 0;
        bool is_last_char_space = false;
        bool is_last_char_comma = false;
        bool is_last_char_commas = false;
        if (!s_cmd_in.empty()) {
            last_char = s_cmd_in[s_cmd_in.size() - 1];
            if (last_char == ' ' || last_char == '\t') is_last_char_space = true;
            else if (last_char == ',') is_last_char_comma = true;
            else if (last_char == '\'' || last_char == '\"') is_last_char_commas = true;
        }

        // <editor-fold defaultstate="collapsed" desc="TAB: last cmd item - full/partial -> cmd_tab_list">
        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (module_ptr) {
                for (int cmd = 0; cmd < module_ptr->Cmd_Count_Get(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Cmd_Get(cmd);
                    bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level);
                    if (is_cmd_prt_valid) {
                        if (tokens.size() <= cmd_ptr->Items.size()) {
                            for (int token = 0; token < tokens.size(); token++) {
                                Cmd_Item_Base *cmd_item_ptr = cmd_ptr->Items[token];
                                Cmd_Token *token_ptr = tokens[token];
                                Cmd_Item_Valid_Result res_parse = cmd_item_ptr->Parse(token_ptr->Text_Get());

                                if (res_parse == CMD_ITEM_OK_CAN_CONTINUE && is_last_char_space) {
                                    res_parse = CMD_ITEM_OK;
                                }
                                if (res_parse == CMD_ITEM_OK_CAN_CONTINUE && (token < tokens.size() - 1)) {
                                    res_parse = CMD_ITEM_OK;
                                }

                                if (res_parse == CMD_ITEM_OK_CAN_CONTINUE) {
                                    TAB_On_OK_CAN_CONTINUE(tab_result_list, cmd_ptr);
                                } else if (token < tokens.size() - 1) { // Not last token in token list, but not OK -> not valid
                                    if (res_parse != CMD_ITEM_OK
                                            && res_parse != CMD_ITEM_OK_CAN_CONTINUE
                                            && res_parse != CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                                        break;
                                    }
                                } else if (token == tokens.size() - 1) { // Last token in token list
                                    if (res_parse == CMD_ITEM_OK || res_parse == CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                                        if (res_parse == CMD_ITEM_OK_STR_WITHOUT_COMMAS && !is_last_char_space) {
                                            TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(tab_result_list, cmd_ptr, cmd_item_ptr);
                                        } else {
                                            if (token < cmd_ptr->Items.size() - 1) { // Not last token in cmd list
                                                TAB_On_OK_not_last_token(tab_result_list, cmd_ptr, token, cmd_item_ptr);
                                            } else if (token == cmd_ptr->Items.size() - 1) { // Last token in cmd list
                                                TAB_On_OK_last_token(tab_result_list, cmd_ptr, cmd_item_ptr, token_ptr);
                                            }
                                        }
                                    } else if (res_parse == CMD_ITEM_INCOMPLETE || res_parse == CMD_ITEM_INCOMPLETE_STR) {
                                        if (res_parse == CMD_ITEM_INCOMPLETE_STR) {
                                            TAB_On_INCOMPLETE_STR(tab_result_list, cmd_ptr, cmd_item_ptr);
                                            is_incomplete_str = true;
                                        } else {
                                            TAB_On_INCOMPLETE(tokens, tab_result_list, is_last_char_space, is_last_char_comma, is_last_char_commas, cmd_ptr, token, cmd_item_ptr, token_ptr);
                                        }
                                    } else {
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

        TAB_Result_List_Parse_To_Flags(tokens, s_log, s_add, Is_Log, Is_Add, Is_Space_After,
                tab_result_list, is_incomplete_str, is_last_char_space, is_last_char_comma, is_last_char_commas);

        for (int i = 0; i < tab_result_list.size(); i++) {
            delete tab_result_list[i];
        }
        tab_result_list.clear();

    }

    virtual vector<TAB_Cmd *> TAB_Cmd_List_Get(
            // in
            Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            const string level, const string s_cmd_in, const string s_cmd_in_trim, const vector<Cmd_Token *> &tokens) {
        vector<TAB_Cmd *> tab_cmd_list;

        string s_log;
        string s_add;

        bool Is_Log = false;
        bool Is_Add = false;
        bool Is_Space_After = false;

        TAB_Cmd_List_Get_With_Flags(
                // in
                user_privilege, modules, level, s_cmd_in, s_cmd_in_trim, tokens,
                // out
                s_log, s_add,
                Is_Log, Is_Add, Is_Space_After);

        if (Is_Log)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_LOG_PRINT, s_log));
        if (Is_Add)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_INPUT_ADD, s_add));
        if (Is_Space_After)
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_INPUT_CHECK_SPACE, ""));

        return tab_cmd_list;
    }

    virtual void Process_Input_Item(Cli_Input_Item &input_item, bool &is_invitation_print) {
        vector<TAB_Cmd *> tab_cmd_list;
        string s_trim = Str_Trim(input_item.Text_Get());
        Level_Description level_description = Level_Get();
        string level = level_description.Level;
        string s_help;
        if (s_trim.size() == 0) {
            s_help = TAB_Help_Get(level, Modules);
            tab_cmd_list.push_back(new TAB_Cmd(TAB_CMD_ID_LOG_PRINT, s_help));
        } else {
            Cmd_Token_Parser_Result parse_res = CMD_TOKEN_PARSER_ERROR;
            vector<Cmd_Token *> tokens = Token_Parser.Parse(s_trim, Str_Rem, parse_res);

            tab_cmd_list = TAB_Cmd_List_Get(User_Privilege, Modules, level, input_item.Text_Get(), s_trim, tokens);

            for (int i = 0; i < tokens.size(); i++)
                delete tokens[i];
            tokens.clear();
        }

        if (tab_cmd_list.size()) {
            bool is_prev_newline = false;
            for (int tab_cmd = 0; tab_cmd < tab_cmd_list.size(); tab_cmd++) {
                TAB_Cmd *tab_cmd_ptr = tab_cmd_list[tab_cmd];
                if (tab_cmd_ptr) {
                    switch (tab_cmd_ptr->ID) {
                        case TAB_CMD_ID_LOG_PRINT:
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(tab_cmd_ptr->Text);
                            Cli_Output.Output_NewLine();
                            is_invitation_print = true;
                            if (Log_Is_Active) {
                                Log.push_back(tab_cmd_ptr->Text);
                            }
                            Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().size());
                            is_prev_newline = true;
                            break;
                        case TAB_CMD_ID_INPUT_ADD:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                            if (s_pos_prev == s_prev.size()) {
                                Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr->Text);
                                Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().size());
                                Cli_Output.Output_Str(tab_cmd_ptr->Text);
                            } else {
                                Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr->Text);
                                Cli_Input.Input_End();
                            }
                            is_invitation_print = false;
                            if (Log_Is_Active) {
                                Log.push_back(tab_cmd_ptr->Text);
                            }
                            is_prev_newline = false;
                        }
                            break;
                        case TAB_CMD_ID_INPUT_CHECK_SPACE:
                        {
                            string s_prev = Cli_Input.Input_Str_Get();
                            int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                            bool is_changed = false;
                            if (s_prev.empty() || s_prev[s_prev.size() - 1] != ' ') {
                                Cli_Input.Input_Str_Set(s_prev + " ");
                                is_changed = true;
                                if (Log_Is_Active) {
                                    Log.push_back(" ");
                                }
                            }
                            if (is_changed && s_pos_prev == s_prev.size() && !is_prev_newline) {
                                Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().size());
                                Cli_Output.Output_Str(" ");
                            } else {
                                Cli_Input.Input_End();
                            }
                            is_invitation_print = false;
                            is_prev_newline = false;
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

#endif /* CLI_TAB_PROCESSOR_H */
