using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_EQU : Cmd_Item_Word
    {
        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            // == != < > <= >= & | && ||

            if (len > 2) return false;

            if (pos == 0)
            {
                if (c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|') return true;
            }
            else if (pos == 1)
            {
                if (c == '=' || c == '&' || c == '|') return true;
            }

            return false;
        }

        public Cmd_Item_EQU(string text, string help) : base(text, help)
        {
            Type = "EQU";
        }

    }
}
