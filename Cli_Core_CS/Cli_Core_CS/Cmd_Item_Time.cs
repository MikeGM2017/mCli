using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Time : Cmd_Item_Date
    {
        public Cmd_Item_Time(string text, string help) : base(text, help)
        {
            Type = "Time";
        }

        override public string Debug_Value_Get()
        {
            return "\"12-13-14\"";
        }

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (pos == 6 && c == '"')
                return true; // "HH-MM" - без секунд
            switch (pos)
            {
                case 0:
                case 9:
                    return (c == '"');
                case 3:
                case 6:
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

            // Time
            if (s.Length >= 2)
            {
                int H = s[1] - '0';
                if (H < 0 || H > 2) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                //int HH = atoi(s.c_str() + 1);
                int HH = 0;
                string s_HH = s.Substring(1, 2);
                Int32.TryParse(s_HH, out HH);
                if (HH > 23) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }

            if (s.Length >= 5)
            {
                int M = s[4] - '0';
                if (M < 0 || M > 5) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                //int MM = atoi(s.c_str() + 4);
                int MM = 0;
                string s_MM = s.Substring(4, 2);
                Int32.TryParse(s_MM, out MM);
                if (MM > 59) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }

            if (s.Length >= 8)
            {
                int S = s[7] - '0';
                if (S < 0 || S > 5) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                //int SS = atoi(s.c_str() + 7);
                int SS = 0;
                string s_SS = s.Substring(7, 2);
                Int32.TryParse(s_SS, out SS);
                if (SS > 59) return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
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
            if (s.Length >= 10)
            {
                Cmd_Item_Valid_Result res = Parse(s);
                if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                    return true;
            }
            return false;
        }
    }
}
