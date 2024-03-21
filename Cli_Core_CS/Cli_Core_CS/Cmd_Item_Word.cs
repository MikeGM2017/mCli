using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cmd_Item_Word : Cmd_Item_Base
    {

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (c >= 'a' && c <= 'z') return true;
            if (c >= 'A' && c <= 'Z') return true;
            if (c == '_') return true;
            //if (pos > 0 && c >= '0' && c <= '9') return true;
            if (c >= '0' && c <= '9') return true;
            return false;
        }

        public Cmd_Item_Word(string text, string help) : base(text, help)
        {
            Type = "Word";
        }

        override public string Debug_Value_Get()
        {
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

            if (Text == s) return Cmd_Item_Valid_Result.CMD_ITEM_OK;

            if (s.Length < Text.Length)
            {
                if (Text.Substring(0, s.Length) == s)
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
                }
            }

            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        override public List<string> Incomplete_Tail_List_Get(string s)
        {
            List<string> tail_list = new List<string>();
            if (s.Length < Text.Length)
            {
                if (Text.Substring(0, s.Length) == s)
                {
                    tail_list.Add(Text.Substring(s.Length));
                }
            }
            return tail_list;
        }

    }
}
