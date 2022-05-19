/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

/**
 *
 * @author mike
 */
public class Str_Filter {

    protected char C_Single; // @Example: '.' or '?'
    protected char C_Multy; // @Example: '*'

    public Str_Filter(char c_single, char c_multy) {
        C_Single = c_single;
        C_Multy = c_multy;
    }

    protected boolean Is_Match_Internal(String filter, String s) {

        if (filter.isEmpty() && s.isEmpty()) {
            return true;
        }
        if (filter.length() == 1 && filter.charAt(0) == C_Multy) {
            return true;
        }
        if (filter.length() == 3 && filter.charAt(0) == '"' && filter.charAt(1) == C_Multy && filter.charAt(2) == '"') {
            return true;
        }
        if (filter.length() == 3 && filter.charAt(0) == '\'' && filter.charAt(1) == C_Multy && filter.charAt(2) == '\'') {
            return true;
        }

        boolean is_match = true;

        int s_pos = 0;
        int filter_pos = 0;
        for (int i = 0; i < filter.length(); i++) {

            if (s_pos >= s.length()) {
                if (filter_pos == filter.length() - 1 && filter.charAt(filter_pos) == C_Multy) {
                    is_match = true;
                } else {
                    is_match = false;
                }
                break;
            }

            char filter_c = filter.charAt(filter_pos);
            char s_c = s.charAt(s_pos);
            if (filter_c == C_Single) {
                // Match: any_single <-> C_Single
                filter_pos++;
                s_pos++;
                continue;
            } else if (filter_c == C_Multy) {
                // Match: any_sequence <-> C_Multy
                if (filter_pos >= filter.length() - 1) {
                    // Match: Last filter char = C_Multy
                    break;
                }
                char filter_c_next = filter.charAt(filter_pos + 1);

                if (filter_c_next == C_Single) {
                    boolean found = false;
                    s_pos++;
                    if (s_pos < s.length()) {
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

                boolean found = false;
                while (s_pos < s.length() && !found) {
                    // Match: s_c_next = filter_c_next
                    s_pos++;
                    if (s_pos < s.length()) {
                        if (s.charAt(s_pos) == filter_c_next) {
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
                    //continue;
                }
                filter_pos++;
                s_pos++;
                continue;
            }

        }

        if (is_match && filter_pos == filter.length() && filter.charAt(filter_pos - 1) != C_Multy && s_pos < s.length()) {
            is_match = false;
        }

        return is_match;
    }

    public boolean Is_Match(String filter, String s) {

        if (filter.isEmpty() && s.isEmpty()) {
            return true;
        }
        if (filter.length() == 1 && filter.charAt(0) == C_Multy) {
            return true;
        }
        if (filter.length() == 3 && filter.charAt(0) == '"' && filter.charAt(1) == C_Multy && filter.charAt(2) == '"') {
            return true;
        }
        if (filter.length() == 3 && filter.charAt(0) == '\'' && filter.charAt(1) == C_Multy && filter.charAt(2) == '\'') {
            return true;
        }

        if (filter.length() > 0 && filter.charAt(0) == C_Multy) {
            for (int i = 0; i < s.length(); i++) {
                String s_substr = s.substring(i, s.length());
                boolean is_match = Is_Match_Internal(filter, s_substr);
                if (is_match) {
                    return true; // Exit: Is_Match
                }
            }
            return false;
        } else {
            return Is_Match_Internal(filter, s);
        }
    }

}
