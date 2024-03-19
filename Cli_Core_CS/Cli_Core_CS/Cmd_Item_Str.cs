namespace Cli_Core_CS
{
    public class Cmd_Item_Str : Cmd_Item_Base
    {

        protected Cmd_Item_Valid_Result Decode(string s_src, Ref_String s_dst)
        {
            Cmd_Item_Valid_Result decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
            bool is_in_commas = false;
            char c_commas = '\0';
            char c_last = '\0';
            bool is_escape = false;
            s_dst.Value = "";
            for (int i = 0; i < s_src.Length; i++)
            {
                if (i == 0)
                {
                    char c1 = s_src[i];
                    if (c1 == '"' || c1 == '\'')
                    {
                        is_in_commas = true;
                        c_commas = c1;
                    }
                }
                char c = s_src[i];
                switch (c)
                {
                    case '\\':
                        decode_res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                        is_escape = true;
                        break;
                    default:
                        if (is_escape)
                        {
                            switch (c)
                            {
                                case 'n':
                                    c = '\n';
                                    c_last = c;
                                    break;
                                case 'r':
                                    c = '\r';
                                    c_last = c;
                                    break;
                                case 't':
                                    c = '\t';
                                    c_last = c;
                                    break;
                                case '\"':
                                case '\'':
                                    c_last = '\0'; // @Attention: Escaped '"' and '''
                                    break;
                                default:
                                    c_last = c;
                                    break;
                            }
                        }
                        else
                        {
                            c_last = c;
                        }
                        s_dst.Value += (c);
                        decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                        is_escape = false;
                        break;
                }
            }

            if (is_in_commas && c_commas != c_last)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }

            if (c_last == '"' || c_last == '\'')
            {
                if (c_last != s_src[0])
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            }

            if (decode_res == Cmd_Item_Valid_Result.CMD_ITEM_OK && s_src.Length > 0 && s_src[0] != '\"' && s_src[0] != '\'')
            {
                decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }

            return decode_res;
        }

        public Cmd_Item_Str(string text, string help) : base(text, help)
        {
            Type = "Str";
        }

        override public string Debug_Value_Get()
        {
            return "\"<str>\"";
        }

        override public Cmd_Item_Valid_Result Parse(string s)
        {
            if (s.Length == 0)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY; // @Attention
            }
            //if (s == "\"\"") s = ""; // @Attention

            //if (s.Length >= 2 && s[0] == '"' && s[s.Length - 1] == '"')
            //    s = s.substr(1, s.Length - 2);
            //else if (s.Length >= 2 && s[0] == '\'' && s[s.Length - 1] == '\'')
            //    s = s.substr(1, s.Length - 2);
            //Value_Str = s; // @Attention: s is not decoded with escapes
            if (s.Length == 2 && s[0] == '"' && s[1] == '"')
            {
                Value_Str = "";
            }
            else if (s.Length == 2 && s[0] == '\'' && s[1] == '\'')
            {
                Value_Str = "";
            }
            else
            {
                Value_Str = s; // @Attention: s is not decoded with escapes
            }

            if (s.Length == 0)
            {
                return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; // @Attention
            }

            if (s.Length == 1)
            {
                if (s[0] == '\n')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (s[0] == '\r')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (s[0] == '"')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                }
                if (s[0] == '\'')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                }
                if (s[0] != '"' && s[0] != '\'')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                }
            }

            //        if (s.Length >= 1 && s[0] != '"') {
            //            return INPUT_ERROR;
            //        }
            if (s.Length == 2)
            {
                if (s[0] == '"' && s[1] == '"')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK;
                }
                if (s[0] == '\'' && s[1] == '\'')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK;
                }
                if (s[0] == '"' && s[1] != '"')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                }
                if (s[0] == '\'' && s[1] != '\'')
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                }
                if (s[0] != '\\' && s[1] != '\\')
                {
                    if (s[0] != '"' && s[1] == '"')
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                    if (s[0] != '\'' && s[1] == '\'')
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                    if (s[0] != '"' && s[1] != '"')
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                    }
                    if (s[0] != '\'' && s[1] != '\'')
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                    }
                }
            }

            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length))
                {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            }

            //if (s[0] == '"' && s[s.Length - 1] != '"') return INPUT_INCOMPLETE;
            //if (s[0] != '"' && s[s.Length - 1] == '"') return INPUT_ERROR;
            //return INPUT_OK;
            Ref_String s_dst = new Ref_String(Value_Str);
            Cmd_Item_Valid_Result decode_res = Decode(s, s_dst); // @Attention: s is decoded with escapes
            Value_Str = s_dst.Value;

            return decode_res;

        }

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            return true; // Допустимы все символы в любой позиции
        }

        override public bool Is_Space_After_Add(string s)
        {
            if (s.Length >= 2)
            {
                if (s[0] == '\"' && s[s.Length - 1] == '\"')
                {
                    return true;
                }
                if (s[0] == '\'' && s[s.Length - 1] == '\'')
                {
                    return true;
                }
            }
            return false;
        }
    }

}
