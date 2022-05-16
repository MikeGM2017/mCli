/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mike
 */
public class Cmd_Token_Parser {

    protected int Skip(Cmd_Token_Parser_Char_Type char_type, String s, int pos) {
        while (pos < s.length() && Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(s.charAt(pos)) == char_type) {
            pos++;
        }
        return pos;
    }

    protected int Get_Val(String s, int pos) {
        while (pos < s.length() && Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(s.charAt(pos)) != Cmd_Token_Parser_Char_Type.CMD_TOKEN_PARSER_CHAR_TYPE_SPACE) {
            pos++;
        }
        return pos;
    }

    protected int Get_Str(String s, int pos, char c_commas) {
        int commas_count = 0;
        boolean is_skip = false;
        do {
            if (pos < s.length()) {
                if (!is_skip) {
                    if (s.charAt(pos) == '\\') {
                        is_skip = true;
                    } else if (s.charAt(pos) == c_commas) {
                        commas_count++;
                    }
                    pos++;
                } else {
                    is_skip = false;
                    pos++;
                }
            }
        } while (pos < s.length() && commas_count < 2);
        return pos;
    }

    public List<Cmd_Token> Parse(String s, String str_rem, Cmd_Token_Parser_Result res_out) {
        List<Cmd_Token> tokens = new ArrayList<>();

        if (s.substring(0, str_rem.length()).equals(str_rem)) {
            res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK;
            Cmd_Token token_ptr = new Cmd_Token(s);
            tokens.add(token_ptr);
            return tokens;
        }

        res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK;

        if (s.length() > 0) {
            int pos = 0;
            int pos_next = 0;
            do {
                boolean found = false;
                char c = s.charAt(pos);
                Cmd_Token_Parser_Char_Type char_type = Cmd_Token_Parser_Char_Type_Func.Char_Type_Get(c);
                switch (char_type) {
                    case CMD_TOKEN_PARSER_CHAR_TYPE_SPACE:
                    case CMD_TOKEN_PARSER_CHAR_TYPE_NEWLINE:
                        pos_next = Skip(char_type, s, pos);
                        found = false;
                        break;
                    case CMD_TOKEN_PARSER_CHAR_TYPE_COMMAS:
                        pos_next = Get_Str(s, pos, c);
                        found = true;
                        break;
                    case CMD_TOKEN_PARSER_CHAR_TYPE_ALPHA:
                    case CMD_TOKEN_PARSER_CHAR_TYPE_DIGIT:
                    case CMD_TOKEN_PARSER_CHAR_TYPE_POINT:
                    default: // @Attention: default: for str filter like *elp 
                        pos_next = Get_Val(s, pos);
                        found = true;
                        break;
                }
                if (pos == pos_next) {
                    res_out = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
                    return tokens;
                }
                if (pos != pos_next && found) {
                    //String s1 = s.substring(pos, pos_next - pos);
                    String s1 = s.substring(pos, pos_next);
                    Cmd_Token token_ptr = new Cmd_Token(s1);
                    tokens.add(token_ptr);
                }
                pos = pos_next;
            } while (pos < s.length());
        }
        return tokens;
    }
}
