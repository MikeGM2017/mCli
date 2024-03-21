using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cmd_Token_Parser
    {

        protected virtual int Skip(Cmd_Token_Parser_Char_Type char_type, string s, int pos)
        {
            while (pos < s.Length && Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(s[pos]) == char_type)
                pos++;
            return pos;
        }

        protected virtual int Get_Val(string s, int pos)
        {
            while (pos < s.Length && Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(s[pos]) != Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_SPACE)
                pos++;
            return pos;
        }

        protected virtual int Get_Str(string s, int pos, char c_commas)
        {
            int commas_count = 0;
            bool is_skip = false;
            do
            {
                if (pos < s.Length)
                {
                    if (!is_skip)
                    {
                        if (s[pos] == '\\')
                        {
                            is_skip = true;
                        }
                        else if (s[pos] == c_commas)
                        {
                            commas_count++;
                        }
                        pos++;
                    }
                    else
                    {
                        is_skip = false;
                        pos++;
                    }
                }
            } while (pos < s.Length && commas_count < 2);
            return pos;
        }

        public virtual List<Cmd_Token> Parse(string s, string str_rem, out Cmd_Token_Parser_Result res_out)
        {
            List<Cmd_Token> tokens = new List<Cmd_Token>();

            if (s.Substring(0, str_rem.Length) == str_rem)
            {
                res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK;
                Cmd_Token token_ptr = new Cmd_Token(s);
                tokens.Add(token_ptr);
                return tokens;
            }

            res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK;

            if (s.Length > 0)
            {
                int pos = 0;
                int pos_next = 0;
                do
                {
                    bool found = false;
                    char c = s[pos];
                    Cmd_Token_Parser_Char_Type char_type = Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(c);
                    switch (char_type)
                    {
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_SPACE:
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE:
                            pos_next = Skip(char_type, s, pos);
                            found = false;
                            break;
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS:
                            pos_next = Get_Str(s, pos, c);
                            found = true;
                            break;
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA:
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT:
                        case Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_POINT:
                        default: // @Attention: default: for str filter like *elp 
                            pos_next = Get_Val(s, pos);
                            found = true;
                            break;
                    }
                    if (pos == pos_next)
                    {
                        res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
                        return tokens;
                    }
                    if (pos != pos_next && found)
                    {
                        string s1 = s.Substring(pos, pos_next - pos);
                        Cmd_Token token_ptr = new Cmd_Token(s1);
                        tokens.Add(token_ptr);
                    }
                    pos = pos_next;
                } while (pos < s.Length);
            }
            return tokens;
        }

    }
}
