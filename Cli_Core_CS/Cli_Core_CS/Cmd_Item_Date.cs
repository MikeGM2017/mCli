using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Date : Cmd_Item_Str
    {
        public    Cmd_Item_Date(string text, string help) : base(text, help)
        {
            Type = "Date";
        }

        override public string Debug_Value_Get()
        {
            return "\"2018-01-02\"";
        }

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            switch (pos)
            {
                case 0:
                case 11:
                    return (c == '"');
                case 5:
                case 8:
                    return (c == '-' || c == ':');
            }
            return (c >= '0' && c <= '9');
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            if (s.Length == 1 && s[0] == '"') return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            if (s.Length >= 1 && s[0] != '"') return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            // Date
            if (s.Length >= 7)
            {
                int m = s[6] - '0';
                if (m < 0 || m > 1) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                if (s.Length >= 8)
                {
                    //int mm = atoi(s.c_str() + 6);
                    int mm = 0;
                    string s_mm = s.Substring(6, 2);
                    Int32.TryParse(s_mm, out mm);
                    if (mm == 0 || mm > 12) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
            }

            if (s.Length >= 10)
            {
                int d = s[9] - '0';
                if (d < 0 || d > 3) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                if (s.Length >= 11)
                {
                    //int dd = atoi(s.c_str() + 9);
                    int dd = 0;
                    string s_dd = s.Substring(9, 2);
                    Int32.TryParse(s_dd, out dd);
                    if (dd == 0 || dd > 31) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
            }

            if (s.Length == 2)
            {
                if (s[0] == '"' && s[1] == '"') return Cmd_Item_Valid_Result.CMD_ITEM_ERROR; //Cmd_Item_Valid_Result.CMD_ITEM_OK;
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }

            if (s[s.Length - 1] != '"') return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;

            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        override public bool Is_Space_After_Add(string s)
        {
            if (s.Length >= 12)
            {
                Cmd_Item_Valid_Result res = Parse(s);
                if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                    return true;
            }
            return false;
        }
    }
}
