using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Int : Cmd_Item_Base
    {
        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (pos == 0)
            {
                if (c == '+') return true;
                if (c == '-') return true;
            }
            return (c >= '0' && c <= '9');
        }

        protected int Char_To_N(char c)
        {
            if (c >= '0' && c <= '9')
            {
                return c - '0';
            }
            return 0;
        }

        public int Value_Int;

        public Cmd_Item_Int(String text, String help) : base(text, help)
        {
            Value_Int = 0;
            Type = "Int";
            Version = "0.02";
        }

        override public String Debug_Value_Get()
        {
            return "1";
        }

        override public Cmd_Item_Valid_Result Parse(String s)
        {
            Value_Str = s;
            Value_Int = 0;

            if (s.Length == 0)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
            }

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length))
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            }

            long v = 0;
            long vMax = Int32.MaxValue;
            for (int pos = 0; pos < s.Length; pos++)
            {
                int n = Char_To_N(s[pos]);
                v = v * 10 + n;
                if (v > vMax)
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_TOO_LONG;
                }
            }

            Value_Int = (int)v;

            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        override public bool Is_Space_After_Add(String s)
        {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
            {
                return true;
            }
            return false;
        }
    }
}
