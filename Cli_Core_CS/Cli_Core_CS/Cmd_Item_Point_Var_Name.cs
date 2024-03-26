using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Point_Var_Name : Cmd_Item_Word
    {
        protected char C_Single;
        protected char C_Multy;

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (len < 2) return false;

            if (pos == 0 && c != '.') return false;
            if (c == '.') return true;
            if (c >= 'a' && c <= 'z') return true;
            if (c >= 'A' && c <= 'Z') return true;
            if (c == '_') return true;
            if (pos > 1 && c >= '0' && c <= '9') return true;
            if (pos > 0 && c == C_Single) return true;
            if (pos > 0 && c == C_Multy) return true;

            return false;
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        public Cmd_Item_Point_Var_Name(string text, string help, char c_single = '?', char c_multy = '*') : base(text, help)
        {
            Type = "Point_Var_Name";
            C_Single = c_single;
            C_Multy = c_multy;
        }

        override public String Debug_Value_Get()
        {
            return ".v";
        }
    }
}
