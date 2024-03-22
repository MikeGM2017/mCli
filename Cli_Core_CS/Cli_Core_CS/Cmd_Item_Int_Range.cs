using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Int_Range : Cmd_Item_Int
    {
        protected int Min;
        protected int Max;

        public Cmd_Item_Int_Range(int min, int max, String text, String help) : base(text, help)
        {
            Min = min;
            Max = max;
            Type = "Int_Range";
        }

        override public String Debug_Value_Get()
        {
            return Min.ToString();
        }

        override public Cmd_Item_Valid_Result Parse(String s)
        {
            Value_Str = s;
            Value_Int = 0;

            if (s.Length == 0)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
            }

            Cmd_Item_Valid_Result res = base.Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK)
            {
                int v = 0;
                Int32.TryParse(s, out v);
                if (v >= Min && v <= Max)
                {
                    Value_Int = v;
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK;
                }
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            return res;
        }

        override public String To_String()
        {
            return "Int_Range: " + Min.ToString() + "..." + Max.ToString() + ": " + base.To_String();
        }
    }
}
