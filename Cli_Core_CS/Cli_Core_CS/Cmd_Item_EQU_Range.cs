using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_EQU_Range : Cmd_Item_EQU
    {
        public    List<string> Words = new List<string>();

        public Cmd_Item_EQU_Range(string text, string help, List<string> words) : base(text, help)
        {
            Type = "EQU_Range";
            Words = words;
        }

        override public string Debug_Value_Get()
        {
            if (Words.Count > 0)
                return Words[0];
            return Text;
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            bool is_incomplete_found = false;
            for (int i = 0; i < Words.Count; i++)
            {
                if (Words[i] == s) return Cmd_Item_Valid_Result.CMD_ITEM_OK;
                if (Words[i].Substring(0, s.Length) == s) is_incomplete_found = true;
            }
            if (is_incomplete_found)
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;

            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        override public bool Is_Space_After_Add(string s)
        {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                return true;
            return false;
        }

        override public List<string> Incomplete_Tail_List_Get(string s)
        {
            List<string> tail_list = new List<string>();
            for (int i = 0; i < Words.Count; i++)
            {
                if (Words[i].Substring(0, s.Length) == s)
                {
                    tail_list.Add(Words[i].Substring(s.Length));
                }
            }
            return tail_list;
        }
    }
}
