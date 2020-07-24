/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Word_List.h
 * Author: mike
 *
 * Created on July 14, 2020, 2:23 PM
 */

#ifndef CMD_ITEM_WORD_LIST_H
#define CMD_ITEM_WORD_LIST_H

#include <set>

using namespace std;

#include "Cmd_Item_Word_Range.h"

class Cmd_Item_Word_List : public Cmd_Item_Word_Range {
protected:

    bool Is_Repeat;

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c == '_') return true;
        if (pos > 0 && c >= '0' && c <= '9') return true;
        if (pos > 0 && c == ',') return true;
        return false;
    }

public:

    vector<string> Values_Str;

    Cmd_Item_Word_List(string text, string help, vector<string> words, bool is_repeat = false) : Cmd_Item_Word_Range(text, help, words),
    Is_Repeat(is_repeat) {
        Type = "Word_List";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;
        Values_Str.clear();
        //        Values_Incomplete.clear();

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        int s_pos_beg = 0;
        int s_pos_end = 0;
        while (s_pos_end < s.size()) {
            if (s[s_pos_end] == ',') {
                Values_Str.push_back(s.substr(s_pos_beg, s_pos_end - s_pos_beg));
                s_pos_end++;
                s_pos_beg = s_pos_end;
            }
            s_pos_end++;
        }
        if (s_pos_beg <= s_pos_end - 1)
            Values_Str.push_back(s.substr(s_pos_beg, s_pos_end - s_pos_beg));

        if (Values_Str.size() == 0) return CMD_ITEM_ERROR;

        set<string> values_set;
        if (!Is_Repeat) {
            for (int i = 0; i < Values_Str.size(); i++) {
                if (values_set.find(Values_Str[i]) == values_set.end())
                    values_set.insert(Values_Str[i]);
                else
                    return CMD_ITEM_ERROR;
            }
        }

        bool is_equal_all = true;
        int found_count = 0;
        for (int i = 0; i < Values_Str.size(); i++) {
            bool found = false;
            for (int j = 0; j < Words.size(); j++) {
                if (Values_Str[i] == Words[j]) {
                    found = true;
                    found_count++;
                    break;
                }
            }
            if (!found) {
                is_equal_all = false;
                break;
            }
        }

        if (s[s.size() - 1] == ',') return CMD_ITEM_INCOMPLETE;

        if (!Is_Repeat && is_equal_all && found_count == Words.size()) return CMD_ITEM_OK;

        if (!Is_Repeat && is_equal_all && found_count < Words.size()) return CMD_ITEM_OK_CAN_CONTINUE;
        if (Is_Repeat && is_equal_all) return CMD_ITEM_OK_CAN_CONTINUE;

        //        string s_last = Values_Str.back();
        //        for (int i = 0; i < Words.size(); i++) {
        //            if (s_last.size() < Words[i].size()) {
        //                if (Words[i].substr(0, s_last.size()) == s_last)
        //                    Values_Incomplete.push_back(Words[i]);
        //            }
        //        }
        //        if (Values_Incomplete.size() > 0) return CMD_ITEM_INCOMPLETE;

        string s_last = Values_Str.back();
        bool is_incomplete_found = false;
        for (int i = 0; i < Words.size(); i++) {
            if (s_last.size() < Words[i].size()) {
                if (Words[i].substr(0, s_last.size()) == s_last) {
                    //Values_Incomplete.push_back(Words[i]);
                    is_incomplete_found = true;
                }
            }
        }
        //if (Values_Incomplete.size() > 0) return CMD_ITEM_INCOMPLETE;
        if (is_incomplete_found)
            return CMD_ITEM_INCOMPLETE;

        //        bool is_incomplete_found = false;
        //        for (int i = 0; i < Words.size(); i++) {
        //            if (Words[i] == s) return CMD_ITEM_OK;
        //            if (Words[i].substr(0, s.size()) == s) is_incomplete_found = true;
        //        }
        //        if (is_incomplete_found)
        //            return CMD_ITEM_INCOMPLETE;

        //Values.clear();
        return CMD_ITEM_ERROR;
    }

    virtual vector<string> Incomplete_Tail_List_Get(string s) {
        vector<string> tail_list;
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == CMD_ITEM_INCOMPLETE) {

            set<string> values_set;
            if (!Is_Repeat) {
                for (int i = 0; i < Values_Str.size(); i++) {
                    if (values_set.find(Values_Str[i]) == values_set.end())
                        values_set.insert(Values_Str[i]);
                }
            }

            string s_last = Values_Str.back();
            for (int i = 0; i < Words.size(); i++) {
                if (Words[i].substr(0, s_last.size()) == s_last) {
                    if (values_set.find(Words[i]) == values_set.end())
                        tail_list.push_back(Words[i].substr(s_last.size()));
                }
            }
        }
        return tail_list;
    }

};

#endif /* CMD_ITEM_WORD_LIST_H */
