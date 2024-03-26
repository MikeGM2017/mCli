using System;
using System.Collections.Generic;
using System.Net;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_IP4 : Cmd_Item_Base
    {
        public Cmd_Item_IP4(string text, string help) : base(text, help)
        {
            Type = "IP4";
        }

        override public string Debug_Value_Get()
        {
            return "1.2.3.4";
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            IPAddress ip_address;
            if (!IPAddress.TryParse(s, out ip_address)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;

            if (ip_address.AddressFamily != System.Net.Sockets.AddressFamily.InterNetwork)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            Value_Str = ip_address.ToString();

            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            return true; // @Warning: All chars allowed: IPAddress.TryParse(...) used
        }

        override public bool Is_Space_After_Add(string s)
        {
            if (s.Length >= 7)
            {
                Cmd_Item_Valid_Result res = Parse(s);
                if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                    return true;
            }
            return false;
        }
    }
}
