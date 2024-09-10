namespace Cli_Core_CS
{
    class Cmd_Item_Str_Esc : Cmd_Item_Str
    {

        enum ST
        {
            ST_NO,

            ST_STR_NOT_COMMAS,
            ST_STR_NOT_COMMAS_ESC,

            ST_STR_WITH_COMMAS,
            ST_STR_WITH_COMMAS_ESC,
            ST_STR_WITH_COMMAS_END,

            ST_ERROR,
            ST_LAST,
            ST_UNDEFINED
        };

        protected void Append_After_ESC(char c, Ref_String s_decoded)
        {
            if (c == '\\') s_decoded.Value += '\\';
            else if (c == ' ') s_decoded.Value += ' ';
            else if (c == '\\') s_decoded.Value += '\\';
            else if (c == 'n') s_decoded.Value += '\n';
            else if (c == 'r') s_decoded.Value += '\r';
            else if (c == 't') s_decoded.Value += '\t';
            else if (c == '\"') s_decoded.Value += '\"';
            else if (c == '\'') s_decoded.Value += '\'';

            else if (c == 'a') s_decoded.Value += '\a';
            else if (c == 'b') s_decoded.Value += '\b';
            else if (c == 'f') s_decoded.Value += '\f';
            else if (c == 'v') s_decoded.Value += '\v';

            else s_decoded.Value += c;
        }

        protected override Cmd_Item_Valid_Result Decode(string s, Ref_String s_decoded)
        {
            Cmd_Item_Valid_Result res = Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            ST st = ST.ST_NO;
            ST st_next = ST.ST_NO;

            char c_commas = '\0';

            for (int i = 0; i < s.Length; i++)
            {
                char c = s[i];

                switch (st)
                {

                    // ST.ST_NO -> ST.ST_STR_NOT_COMMAS / ST.ST_STR_NOT_COMMAS_ESC
                    case ST.ST_NO:
                        {
                            if (c != '\"' && c != '\'')
                            {
                                if (c != '\\')
                                {
                                    st_next = ST.ST_STR_NOT_COMMAS;
                                    s_decoded.Value += c;
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                }
                                else
                                {
                                    st_next = ST.ST_STR_NOT_COMMAS_ESC;
                                    //s_decoded.Value += c; // Skip
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                                }
                            }
                            else
                            {
                                c_commas = c;
                                st_next = ST.ST_STR_WITH_COMMAS;
                                //s_decoded.Value += c; // Skip
                                res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                            }
                        }
                        break;

                    // ST.ST_STR_NOT_COMMAS -> ST.ST_STR_NOT_COMMAS / ST.ST_STR_NOT_COMMAS_ESC / ST.ST_ERROR
                    case ST.ST_STR_NOT_COMMAS:
                        {
                            if (c != '\\')
                            {
                                if (c != '\"' && c != '\'')
                                {
                                    st_next = ST.ST_STR_NOT_COMMAS;
                                    s_decoded.Value += c;
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                }
                                else
                                {
                                    st_next = ST.ST_ERROR;
                                    s_decoded.Value += c;
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                                }
                            }
                            else
                            {
                                st_next = ST.ST_STR_NOT_COMMAS_ESC;
                                //s_decoded.Value += c; // Skip
                                res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                            }
                        }
                        break;

                    // ST.ST_STR_NOT_COMMAS_ESC -> ST.ST_STR_NOT_COMMAS
                    case ST.ST_STR_NOT_COMMAS_ESC:
                        {
                            st_next = ST.ST_STR_NOT_COMMAS;
                            Append_After_ESC(c, s_decoded);
                            res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //Cmd_Item_Valid_Result.CMD_ITEM_OK;
                        }
                        break;

                    // ST.ST_STR_WITH_COMMAS -> ST.ST_STR_WITH_COMMAS / ST.ST_STR_WITH_COMMAS_ESC
                    case ST.ST_STR_WITH_COMMAS:
                        {
                            if (c != c_commas)
                            {
                                if (c != '\\')
                                {
                                    st_next = ST.ST_STR_WITH_COMMAS;
                                    s_decoded.Value += c;
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                                }
                                else
                                {
                                    st_next = ST.ST_STR_WITH_COMMAS_ESC;
                                    //s_decoded.Value += c; // Skip
                                    res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                                }

                            }
                            else
                            {
                                st_next = ST.ST_STR_WITH_COMMAS_END;
                                //s_decoded.Value += c; // Skip
                                res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                            }
                        }
                        break;

                    // ST.ST_STR_WITH_COMMAS_ESC -> ST.ST_STR_WITH_COMMAS
                    case ST.ST_STR_WITH_COMMAS_ESC:
                        {
                            st_next = ST.ST_STR_WITH_COMMAS;
                            Append_After_ESC(c, s_decoded);
                            res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                        }
                        break;

                    // ST.ST_STR_WITH_COMMAS_END -> ST.ST_ERROR
                    case ST.ST_STR_WITH_COMMAS_END:
                        {
                            st_next = ST.ST_ERROR;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                        }
                        break;

                    // ST.ST_ERROR -> ST.ST_ERROR
                    default:
                        {
                            st_next = ST.ST_ERROR;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                        }
                        break;

                }

                st = st_next;

            }

            return res;
        }

        public Cmd_Item_Str_Esc(string text, string help) : base(text, help)
        {
            Type = "Str_Esc";
            Version = "0.02";
        }

        public override Cmd_Item_Valid_Result Parse(string s)
        {
            Ref_String s_decoded = new Ref_String("");
            Cmd_Item_Valid_Result res = Decode(s, s_decoded);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK || res == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
            {
                Value_Str = s_decoded.Value;
            }
            else
            {
                Value_Str = s; // Error or Incomplete
            }
            return res;
        }

        override protected bool Is_Char_Valid(char c, int pos, int len)
        {
            return true; // Допустимы все символы в любой позиции
        }

        public override bool Is_Space_After_Add(string s)
        {
            if (s.Length >= 2)
            {
                if (s[0] == '\"' && s[s.Length - 1] == '\"') return true;
                if (s[0] == '\'' && s[s.Length - 1] == '\'') return true;
            }
            return false;
        }

    };
}
