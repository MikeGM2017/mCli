namespace Cli_Core_CS
{
    class Cmd_Token_Parser_Char_Type_Func
    {
        public static Cmd_Token_Parser_Char_Type Char_Type_Get(char c)
        {
            if (c >= 'a' && c <= 'z') return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
            if (c >= 'A' && c <= 'Z') return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
            if (c == '_') return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA;
            if (c >= '0' && c <= '9') return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT;
            switch (c)
            {
                case ' ':
                case '\t':
                    return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_SPACE;
                case '\n':
                case '\r':
                    return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE;
                case '\"':
                case '\'': // @Attention
                    return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS;
            }
            if (c == '.') return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_POINT;
            return Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_ERROR;
        }
    }
}
