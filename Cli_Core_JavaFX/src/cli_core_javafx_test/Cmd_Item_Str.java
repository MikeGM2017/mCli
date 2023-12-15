/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

/**
 *
 * @author mike
 */
public class Cmd_Item_Str extends Cmd_Item_Base {

    protected Cmd_Item_Valid_Result Decode(String s_src, Ref_String s_dst) {
        Cmd_Item_Valid_Result decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
        boolean is_in_commas = false;
        char c_commas = '\0';
        char c_last = '\0';
        boolean is_escape = false;
        s_dst.Value = "";
        for (int i = 0; i < s_src.length(); i++) {
            if (i == 0) {
                char c = s_src.charAt(i);
                if (c == '"' || c == '\'') {
                    is_in_commas = true;
                    c_commas = c;
                }
            }
            char c = s_src.charAt(i);
            switch (c) {
                case '\\':
                    decode_res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                    is_escape = true;
                    break;
                default:
                    if (is_escape) {
                        switch (c) {
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
                                c_last = 0; // @Attention: Escaped '"' and '''
                                break;
                            default:
                                c_last = c;
                        }
                    } else {
                        c_last = c;
                    }
                    s_dst.Value += (c);
                    decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                    is_escape = false;
                    break;
            }
        }

        if (is_in_commas && c_commas != c_last) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }

        if (c_last == '"' || c_last == '\'') {
            if (c_last != s_src.charAt(0)) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        if (decode_res == Cmd_Item_Valid_Result.CMD_ITEM_OK && !s_src.isEmpty() && s_src.charAt(0) != '\"' && s_src.charAt(0) != '\'') {
            decode_res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
        }

        return decode_res;
    }

    public Cmd_Item_Str(String text, String help) {
        super(text, help);
        Type = "Str";
    }

    @Override
    public String Debug_Value_Get() {
        return "\"<str>\"";
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY; // @Attention
        }
        //if (s == "\"\"") s = ""; // @Attention

        //if (s.length() >= 2 && s.charAt(0) == '"' && s.charAt(s.length() - 1) == '"')
        //    s = s.substr(1, s.length() - 2);
        //else if (s.length() >= 2 && s.charAt(0) == '\'' && s.charAt(s.length() - 1) == '\'')
        //    s = s.substr(1, s.length() - 2);
        //Value_Str = s; // @Attention: s is not decoded with escapes
        if (s.length() == 2 && s.charAt(0) == '"' && s.charAt(1) == '"') {
            Value_Str = "";
        } else if (s.length() == 2 && s.charAt(0) == '\'' && s.charAt(1) == '\'') {
            Value_Str = "";
        } else {
            Value_Str = s; // @Attention: s is not decoded with escapes
        }

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; // @Attention
        }

        if (s.length() == 1) {
            if (s.charAt(0) == '\n') {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
            if (s.charAt(0) == '\r') {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
            if (s.charAt(0) == '"') {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (s.charAt(0) == '\'') {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (s.charAt(0) != '"' && s.charAt(0) != '\'') {
                return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
            }
        }

        //        if (s.length() >= 1 && s.charAt(0) != '"') {
        //            return INPUT_ERROR;
        //        }
        if (s.length() == 2) {
            if (s.charAt(0) == '"' && s.charAt(1) == '"') {
                return Cmd_Item_Valid_Result.CMD_ITEM_OK;
            }
            if (s.charAt(0) == '\'' && s.charAt(1) == '\'') {
                return Cmd_Item_Valid_Result.CMD_ITEM_OK;
            }
            if (s.charAt(0) == '"' && s.charAt(1) != '"') {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (s.charAt(0) == '\'' && s.charAt(1) != '\'') {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
            }
            if (s.charAt(0) != '\\' && s.charAt(1) != '\\') {
                if (s.charAt(0) != '"' && s.charAt(1) == '"') {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (s.charAt(0) != '\'' && s.charAt(1) == '\'') {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (s.charAt(0) != '"' && s.charAt(1) != '"') {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                }
                if (s.charAt(0) != '\'' && s.charAt(1) != '\'') {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS;
                }
            }
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        //if (s.charAt(0) == '"' && s.charAt(s.length() - 1) != '"') return INPUT_INCOMPLETE;
        //if (s.charAt(0) != '"' && s.charAt(s.length() - 1) == '"') return INPUT_ERROR;
        //return INPUT_OK;
        Ref_String s_dst = new Ref_String(Value_Str);
        Cmd_Item_Valid_Result decode_res = Decode(s, s_dst); // @Attention: s is decoded with escapes
        Value_Str = s_dst.Value;

        return decode_res;

    }

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        return true; // Допустимы все символы в любой позиции
    }

    @Override
    public boolean Is_Space_After_Add(String s) {
        if (s.length() >= 2) {
            if (s.charAt(0) == '\"' && s.charAt(s.length() - 1) == '\"') {
                return true;
            }
            if (s.charAt(0) == '\'' && s.charAt(s.length() - 1) == '\'') {
                return true;
            }
        }
        return false;
    }
}
