using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Word_List : Cmd_Item_Word_Range
    {
        protected    bool Is_Repeat = false;

       override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (c >= 'a' && c <= 'z') return true;
            if (c >= 'A' && c <= 'Z') return true;
            if (c == '_') return true;
            //if (pos > 0 && c >= '0' && c <= '9') return true;
            if (c >= '0' && c <= '9') return true;
            if (pos > 0 && c == ',') return true;
            return false;
        }

        public     List<string> Values_Str = new List<string>();

        public Cmd_Item_Word_List(string text, string help, List<string> words, bool is_repeat = false) : base(text, help, words)
        {
            Type = "Word_List";
            Is_Repeat = is_repeat;
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;
            Values_Str.Clear();
            //        Values_Incomplete.clear();

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            int s_pos_beg = 0;
            int s_pos_end = 0;
            while (s_pos_end < s.Length)
            {
                if (s[s_pos_end] == ',')
                {
                    Values_Str.Add(s.Substring(s_pos_beg, s_pos_end - s_pos_beg));
                    s_pos_end++;
                    s_pos_beg = s_pos_end;
                }
                s_pos_end++;
            }
            if (s_pos_beg <= s_pos_end - 1)
            {
                //Values_Str.Add(s.Substring(s_pos_beg, s_pos_end - s_pos_beg));
                Values_Str.Add(s.Substring(s_pos_beg));
            }

            if (Values_Str.Count == 0) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;

            List<string> values_set = new List<string>();
            if (!Is_Repeat)
            {
                for (int i = 0; i < Values_Str.Count; i++)
                {
                    if (!values_set.Contains(Values_Str[i]))
                        values_set.Add(Values_Str[i]);
                    else
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            }

            bool is_equal_all = true;
            int found_count = 0;
            for (int i = 0; i < Values_Str.Count; i++)
            {
                bool found = false;
                for (int j = 0; j < Words.Count; j++)
                {
                    if (Values_Str[i] == Words[j])
                    {
                        found = true;
                        found_count++;
                        break;
                    }
                }
                if (!found)
                {
                    is_equal_all = false;
                    break;
                }
            }

            if (s[s.Length - 1] == ',') return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;

            if (!Is_Repeat && is_equal_all && found_count == Words.Count) return Cmd_Item_Valid_Result.CMD_ITEM_OK;

            if (!Is_Repeat && is_equal_all && found_count < Words.Count) return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;
            if (Is_Repeat && is_equal_all) return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;

            //        string s_last = Values_Str.back();
            //        for (int i = 0; i < Words.Count; i++) {
            //            if (s_last.Length < Words[i].Count) {
            //                if (Words[i].Substring(0, s_last.Length) == s_last)
            //                    Values_Incomplete.Add(Words[i]);
            //            }
            //        }
            //        if (Values_Incomplete.Length > 0) return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;

            string s_last = Values_Str[Values_Str.Count - 1];
            bool is_incomplete_found = false;
            for (int i = 0; i < Words.Count; i++)
            {
                if (s_last.Length < Words[i].Length)
                {
                    if (Words[i].Substring(0, s_last.Length) == s_last)
                    {
                        //Values_Incomplete.Add(Words[i]);
                        is_incomplete_found = true;
                    }
                }
            }
            //if (Values_Incomplete.Length > 0) return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
            if (is_incomplete_found)
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;

            //        bool is_incomplete_found = false;
            //        for (int i = 0; i < Words.Count; i++) {
            //            if (Words[i] == s) return Cmd_Item_Valid_Result.CMD_ITEM_OK;
            //            if (Words[i].Substring(0, s.Length) == s) is_incomplete_found = true;
            //        }
            //        if (is_incomplete_found)
            //            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;

            //Values.clear();
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        override public List<string> Incomplete_Tail_List_Get(string s)
        {
            List<string> tail_list = new List<string>();
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE)
            {

                List<string> values_set = new List<string>();
                if (!Is_Repeat)
                {
                    for (int i = 0; i < Values_Str.Count; i++)
                    {
                        if (!values_set.Contains(Values_Str[i]))
                            values_set.Add(Values_Str[i]);
                    }
                }

                string s_last = Values_Str[Values_Str.Count - 1];
                for (int i = 0; i < Words.Count; i++)
                {
                    if (Words[i].Substring(0, s_last.Length) == s_last)
                    {
                        if (!values_set.Contains(Words[i]))
                            tail_list.Add(Words[i].Substring(s_last.Length));
                    }
                }
            }
            return tail_list;
        }
    }
}
