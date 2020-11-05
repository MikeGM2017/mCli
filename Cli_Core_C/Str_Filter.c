/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Str_Filter.h"

static int Str_Filter_Is_Match_Internal(struct Str_Filter *str_filter, char *filter, int filter_size, char *s, int s_size) {
    int i;

    if (filter[0] == '\0' && s[0] == '\0')
        return 1;
    if (filter_size == 1 && filter[0] == str_filter->C_Multy)
        return 1;
    if (filter_size == 3 && filter[0] == '"' && filter[1] == str_filter->C_Multy && filter[2] == '"')
        return 1;
    if (filter_size == 3 && filter[0] == '\'' && filter[1] == str_filter->C_Multy && filter[2] == '\'')
        return 1;

    int is_match = 1;

    int s_pos = 0;
    int filter_pos = 0;
    for (i = 0; i < filter_size; i++) {

        if (s_pos >= s_size) {
            if (filter_pos == filter_size - 1 && filter[filter_pos] == str_filter->C_Multy) {
                is_match = 1;
            } else {
                is_match = 0;
            }
            break;
        }

        char filter_c = filter[filter_pos];
        char s_c = s[s_pos];
        if (filter_c == str_filter->C_Single) {
            // Match: any_single <-> str_filter->C_Single
            filter_pos++;
            s_pos++;
            continue;
        } else if (filter_c == str_filter->C_Multy) {
            // Match: any_sequence <-> str_filter->C_Multy
            if (filter_pos >= filter_size - 1) {
                // Match: Last filter char = str_filter->C_Multy
                break;
            }
            char filter_c_next = filter[filter_pos + 1];

            if (filter_c_next == str_filter->C_Single) {
                int found = 0;
                s_pos++;
                if (s_pos < s_size) {
                    found = 1;
                }
                if (found) {
                    filter_pos++;
                    continue;
                } else {
                    is_match = 0; // Failed
                    break;
                }
            }

            int found = 0;
            while (s_pos < s_size && !found) {
                // Match: s_c_next = filter_c_next
                s_pos++;
                if (s_pos < s_size) {
                    if (s[s_pos] == filter_c_next) {
                        found = 1;
                    }
                }
            }
            if (found) {
                filter_pos++;
                continue;
            } else {
                is_match = 0; // Failed
                break;
            }
        } else {
            // Match: s_c = filter_c
            if (s_c != filter_c) {
                // @BUG: Здесь было рассчитано на одно попадание
                is_match = 0; // Failed
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

    if (is_match && filter_pos == filter_size && filter[filter_pos - 1] != str_filter->C_Multy && s_pos < s_size) {
        is_match = 0;
    }

    return is_match;
}

int Str_Filter_Is_Match(struct Str_Filter *str_filter, char *filter, char *s) {
    int i;

    int filter_size = strlen(filter);
    int s_size = strlen(s);

    if (filter[0] == '\0' && s[0] == '\0')
        return 1;
    if (filter_size == 1 && filter[0] == str_filter->C_Multy)
        return 1;
    if (filter_size == 3 && filter[0] == '"' && filter[1] == str_filter->C_Multy && filter[2] == '"')
        return 1;
    if (filter_size == 3 && filter[0] == '\'' && filter[1] == str_filter->C_Multy && filter[2] == '\'')
        return 1;
    
    // get substring without commas
    
    char s_without_commas[] = "";

    if (filter_size && filter[0] == str_filter->C_Multy) {
        for (i = 0; i < s_size; i++) {
            //string s_substr = s.substr(i, s_size - i);
            //int is_match = Str_Filter_Is_Match_Internal(str_filter, filter, s_substr);
            int is_match = Str_Filter_Is_Match_Internal(str_filter, filter, filter_size, s + i, s_size - i);
            if (is_match) return 1; // Exit: Is_Match
        }
        return 0;
    } else {
        return Str_Filter_Is_Match_Internal(str_filter, filter, filter_size, s, s_size);
    }
}

struct Str_Filter Str_Filter_Init(char c_single, char c_multy) {
    struct Str_Filter filter;
    filter.C_Single = c_single;
    filter.C_Multy = c_multy;
    return filter;
}
