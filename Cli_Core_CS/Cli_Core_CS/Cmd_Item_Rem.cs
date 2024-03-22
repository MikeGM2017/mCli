using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Rem : Cmd_Item_Base
    {
        public Cmd_Item_Rem(string str_rem, string help) : base(str_rem, help)
        {
            Type = "Rem";
        }

        override public string Debug_Value_Get()
        {
            return Text + " - rem";
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            if (s.Substring(0, Text.Length) == Text) return Cmd_Item_Valid_Result.CMD_ITEM_OK;

            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }
    }
}
