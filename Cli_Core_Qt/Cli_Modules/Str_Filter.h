/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_Filter.h
 * Author: mike
 *
 * Created on August 31, 2018, 3:08 PM
 */

#ifndef STR_FILTER_H
#define STR_FILTER_H

#include "Str_Filter_Abstract.h"

class Str_Filter : public Str_Filter_Abstract {
protected:
    char C_Single; // @Example: '.' or '?'
    char C_Multy; // @Example: '*'
public:

    Str_Filter(char c_single, char c_multy) : C_Single(c_single), C_Multy(c_multy) {
    }

    virtual bool Is_Match_Internal(string filter, string s) {

        if (filter == "" && s == "")
            return true;
        if (filter.size() == 1 && filter[0] == C_Multy)
            return true;
        if (filter.size() == 3 && filter[0] == '"' && filter[1] == C_Multy && filter[2] == '"')
            return true;
        if (filter.size() == 3 && filter[0] == '\'' && filter[1] == C_Multy && filter[2] == '\'')
            return true;

        bool is_match = true;

        int s_pos = 0;
        int filter_pos = 0;
        for (int i = 0; i < filter.size(); i++) {

            if (s_pos >= s.size()) {
                if (filter_pos == filter.size() - 1 && filter[filter_pos] == C_Multy) {
                    is_match = true;
                } else {
                    is_match = false;
                }
                break;
            }

            char filter_c = filter[filter_pos];
            char s_c = s[s_pos];
            if (filter_c == C_Single) {
                // Match: any_single <-> C_Single
                filter_pos++;
                s_pos++;
                continue;
            } else if (filter_c == C_Multy) {
                // Match: any_sequence <-> C_Multy
                if (filter_pos >= filter.size() - 1) {
                    // Match: Last filter char = C_Multy
                    break;
                }
                char filter_c_next = filter[filter_pos + 1];

                if (filter_c_next == C_Single) {
                    bool found = false;
                    s_pos++;
                    if (s_pos < s.size()) {
                        found = true;
                    }
                    if (found) {
                        filter_pos++;
                        continue;
                    } else {
                        is_match = false; // Failed
                        break;
                    }
                }

                bool found = false;
                while (s_pos < s.size() && !found) {
                    // Match: s_c_next = filter_c_next
                    s_pos++;
                    if (s_pos < s.size()) {
                        if (s[s_pos] == filter_c_next) {
                            found = true;
                        }
                    }
                }
                if (found) {
                    filter_pos++;
                    continue;
                } else {
                    is_match = false; // Failed
                    break;
                }
            } else {
                // Match: s_c = filter_c
                if (s_c != filter_c) {
                    // @BUG: Здесь было рассчитано на одно попадание
                    is_match = false; // Failed
                    break;
                    // @BUG: Может быть несколько попаданий, если не совпало - продолжаем искать по стороке, фильтр нужно сбросить - это не сделано
                    //if (filter_pos > 0)
                    //    filter_pos--;
                    //s_pos++;
                    continue;
                }
                filter_pos++;
                s_pos++;
                continue;
            }

        }

        if (is_match && filter_pos == filter.size() && filter.size() >= 1 && filter[filter_pos - 1] != C_Multy && s_pos < s.size()) {
            is_match = false;
        }

        return is_match;
    }

    virtual bool Is_Match(string filter, string s) {

        if (filter == "" && s == "")
            return true;
        if (filter.size() == 1 && filter[0] == C_Multy)
            return true;
        if (filter.size() == 3 && filter[0] == '"' && filter[1] == C_Multy && filter[2] == '"')
            return true;
        if (filter.size() == 3 && filter[0] == '\'' && filter[1] == C_Multy && filter[2] == '\'')
            return true;

        if (filter.size() && filter[0] == C_Multy) {
            for (int i = 0; i < s.size(); i++) {
                string s_substr = s.substr(i, s.size() - i);
                bool is_match = Is_Match_Internal(filter, s_substr);
                if (is_match) return true; // Exit: Is_Match
            }
            return false;
        } else {
            return Is_Match_Internal(filter, s);
        }
    }

};

#endif /* STR_FILTER_H */
