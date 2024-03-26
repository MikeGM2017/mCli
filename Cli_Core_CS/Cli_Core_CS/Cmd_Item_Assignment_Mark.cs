using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Assignment_Mark : Cmd_Item_Base
    {
        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            // =
            if (len == 1 && pos == 0 && c == '=') return true;
            return false;
        }

        public Cmd_Item_Assignment_Mark(string text, string help) : base(text, help)
        {
            Type = "Assignment_Mark";
        }
    }
}
