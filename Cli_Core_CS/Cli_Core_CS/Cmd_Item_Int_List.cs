using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cmd_Item_Int_List : Cmd_Item_Int_Range
    {
        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            if (c >= '0' && c <= '9')
                return true;
            if (pos > 0)
            {
                if (c == ',')
                    return true;
                if (c == '-')
                    return true;
            }
            return false;
        }

        public List<Cmd_Item_Int_List_Item> Values_Int_List_Items = new List<Cmd_Item_Int_List_Item>();

        public Cmd_Item_Int_List(int min, int max, string text, string help) : base(min, max, text, help)
        {
            Type = "Int_List";
        }

        override public String Debug_Value_Get()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(Min).Append("-").Append(Max);
            return sb.ToString ();
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;
            Values_Int_List_Items.Clear();

            if (String.IsNullOrEmpty(s)) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }

            int n = 0;
            int n_beg = 0;
            bool n_beg_Valid = false;
            bool prev_is_digit = false;
            bool prev_is_minus = false;
            for (int pos = 0; pos < s.Length; pos++)
            {
                char c = s[pos];
                if (c >= '0' && c <= '9')
                {
                    n = n * 10 + Char_To_N(c);
                    prev_is_digit = true;
                    prev_is_minus = false;
                    //n_beg_Valid = false;
                }
                else if (c == '-')
                {
                    if (prev_is_digit)
                    {
                        if (n < Min || n > Max)
                        {
                            return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                        }
                        n_beg = n;
                        n = 0;
                        prev_is_digit = false;
                        prev_is_minus = true;
                        n_beg_Valid = true;
                    }
                    else
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                }
                else if (c == ',')
                {
                    if (prev_is_minus)
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                    if (!prev_is_digit)
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                    // Повтор для последнего значения - Beg
                    if (n_beg_Valid && prev_is_digit)
                    {
                        if (n < Min || n > Max)
                        {
                            return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                        }
                        //if (n_beg <= n) { @Attention
                        if (n_beg < n)
                        {
                            Values_Int_List_Items.Add(new Cmd_Item_Int_List_Item(n_beg, n));
                            n = 0;
                            prev_is_digit = false;
                            prev_is_minus = false;
                            n_beg_Valid = false;
                        }
                        else
                        {
                            return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_ORDER;
                        }
                    }
                    else if (prev_is_digit)
                    {
                        if (n < Min || n > Max)
                        {
                            return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                        }
                        Values_Int_List_Items.Add(new Cmd_Item_Int_List_Item(n, n));
                        n = 0;
                        prev_is_digit = false;
                        prev_is_minus = false;
                        n_beg_Valid = false;
                    }
                    // Повтор для последнего значения - End

                }
            }
            // Последнее значение
            if (prev_is_minus)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (!prev_is_digit)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            // Повтор для последнего значения - Beg
            if (n_beg_Valid && prev_is_digit)
            {
                if (n < Min || n > Max)
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
                //if (n_beg <= n) { @Attention
                if (n_beg < n)
                {
                    Values_Int_List_Items.Add(new Cmd_Item_Int_List_Item(n_beg, n));
                    n = 0;
                    prev_is_digit = false;
                    prev_is_minus = false;
                    n_beg_Valid = false;
                }
                else
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_ORDER;
                }
            }
            else if (prev_is_digit)
            {
                if (n < Min || n > Max)
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
                Values_Int_List_Items.Add(new Cmd_Item_Int_List_Item(n, n));
                n = 0;
                prev_is_digit = false;
                prev_is_minus = false;
                n_beg_Valid = false;
            }
            // Повтор для последнего значения - End

            if (s[s.Length - 1] == ',')
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (s[s.Length - 1] == '-')
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }

            return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;
        }

        override public string To_String()
        {
            StringBuilder sb = new StringBuilder();
            Cmd_Item_Base cmd_item_base = (Cmd_Item_Base)this;
            sb.Append("Int_List: ").Append(Min).Append("...").Append(Max).Append(": ").Append(cmd_item_base.To_String()).Append(" ");
            for (int i = 0; i < Values_Int_List_Items.Count; i++)
            {
                Cmd_Item_Int_List_Item item = Values_Int_List_Items[i];
                if (i > 0)
                {
                    sb.Append(",");
                }
                if (item.Min == item.Max)
                {
                    sb.Append(item.Min);
                }
                else
                {
                    sb.Append(item.Min).Append("-").Append(item.Max);
                }
            }
            return sb.ToString();
        }
    }
}
