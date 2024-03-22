using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Str_Filter
    {
        protected char C_Single; // @Example: '.' or '?'
        protected char C_Multy; // @Example: '*'

        public Str_Filter(char c_single, char c_multy)
        {
            C_Single = c_single;
            C_Multy = c_multy;
        }

        protected bool Is_Match_Internal(String filter, String s)
        {

            if (filter.Length == 0 && s.Length == 0)
            {
                return true;
            }
            if (filter.Length == 1 && filter[0] == C_Multy)
            {
                return true;
            }
            if (filter.Length == 3 && filter[0] == '"' && filter[1] == C_Multy && filter[2] == '"')
            {
                return true;
            }
            if (filter.Length == 3 && filter[0] == '\'' && filter[1] == C_Multy && filter[2] == '\'')
            {
                return true;
            }

            bool is_match = true;

            int s_pos = 0;
            int filter_pos = 0;
            for (int i = 0; i < filter.Length; i++)
            {

                if (s_pos >= s.Length)
                {
                    if (filter_pos == filter.Length - 1 && filter[filter_pos] == C_Multy)
                    {
                        is_match = true;
                    }
                    else
                    {
                        is_match = false;
                    }
                    break;
                }

                char filter_c = filter[filter_pos];
                char s_c = s[s_pos];
                if (filter_c == C_Single)
                {
                    // Match: any_single <-> C_Single
                    filter_pos++;
                    s_pos++;
                    continue;
                }
                else if (filter_c == C_Multy)
                {
                    // Match: any_sequence <-> C_Multy
                    if (filter_pos >= filter.Length - 1)
                    {
                        // Match: Last filter char = C_Multy
                        break;
                    }
                    char filter_c_next = filter[filter_pos + 1];

                    if (filter_c_next == C_Single)
                    {
                        bool found_single = false;
                        s_pos++;
                        if (s_pos < s.Length)
                        {
                            found_single = true;
                        }
                        if (found_single)
                        {
                            filter_pos++;
                            continue;
                        }
                        else
                        {
                            is_match = false; // Failed
                            break;
                        }
                    }

                    bool found = false;
                    while (s_pos < s.Length && !found)
                    {
                        // Match: s_c_next = filter_c_next
                        s_pos++;
                        if (s_pos < s.Length)
                        {
                            if (s[s_pos] == filter_c_next)
                            {
                                found = true;
                            }
                        }
                    }
                    if (found)
                    {
                        filter_pos++;
                        continue;
                    }
                    else
                    {
                        is_match = false; // Failed
                        break;
                    }
                }
                else
                {
                    // Match: s_c = filter_c
                    if (s_c != filter_c)
                    {
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

            if (is_match && filter_pos == filter.Length && filter.Length >= 1 && filter[filter_pos - 1] != C_Multy && s_pos < s.Length)
            {
                is_match = false;
            }

            return is_match;
        }

        public bool Is_Match(String filter, String s)
        {

            if (filter.Length == 0 && s.Length == 0)
            {
                return true;
            }
            if (filter.Length == 1 && filter[0] == C_Multy)
            {
                return true;
            }
            if (filter.Length == 3 && filter[0] == '"' && filter[1] == C_Multy && filter[2] == '"')
            {
                return true;
            }
            if (filter.Length == 3 && filter[0] == '\'' && filter[1] == C_Multy && filter[2] == '\'')
            {
                return true;
            }

            if (filter.Length > 0 && filter[0] == C_Multy)
            {
                for (int i = 0; i < s.Length; i++)
                {
                    String s_substr = s.Substring(i, s.Length - i);
                    bool is_match = Is_Match_Internal(filter, s_substr);
                    if (is_match)
                    {
                        return true; // Exit: Is_Match
                    }
                }
                return false;
            }
            else
            {
                return Is_Match_Internal(filter, s);
            }
        }
    }
}
