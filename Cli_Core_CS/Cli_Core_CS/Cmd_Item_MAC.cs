using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_MAC : Cmd_Item_Base
    {
        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            switch (pos)
            {
                case 2:
                case 5:
                case 8:
                case 11:
                case 14:
                    return (c == ':' || c == '-');
                default:
                    if (c >= '0' && c <= '9')
                        return true;
                    if (c >= 'a' && c <= 'f')
                        return true;
                    if (c >= 'A' && c <= 'F')
                        return true;
                    break;
            }
            return false;
        }

        public    Cmd_Item_MAC(string text, string help) : base(text, help)
        {
            Type = "MAC";
        }

        override public string Debug_Value_Get()
        {
            return "11:22:33:DD:EE:FF";
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            if (s.Length < 17) return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            if (s.Length > 17) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;

            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        override public bool Is_Space_After_Add(string s)
        {
            if (s.Length >= 17)
            {
                Cmd_Item_Valid_Result res = Parse(s);
                if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                    return true;
            }
            return false;
        }
    }
}
