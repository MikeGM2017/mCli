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
public class Cmd_Item_Str_Esc extends Cmd_Item_Str {

    enum ST {
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

    protected void Append_After_ESC(char c, Ref_String s_decoded) {
        if (c == '\\') {
            s_decoded.Value += '\\';
        } else if (c == ' ') {
            s_decoded.Value += ' ';
        } else if (c == '\\') {
            s_decoded.Value += '\\';
        } else if (c == 'n') {
            s_decoded.Value += '\n';
        } else if (c == 'r') {
            s_decoded.Value += '\r';
        } else if (c == 't') {
            s_decoded.Value += '\t';
        } else if (c == '\"') {
            s_decoded.Value += '\"';
        } else if (c == '\'') {
            s_decoded.Value += '\'';
        } else if (c == 'a') {
            s_decoded.Value += 0x07; //'\a';
        } else if (c == 'b') {
            s_decoded.Value += '\b';
        } else if (c == 'f') {
            s_decoded.Value += '\f';
        } else if (c == 'v') {
            s_decoded.Value += 0x0b; //'\v';
        } else {
            s_decoded.Value += c;
        }
    }

    @Override
    protected Cmd_Item_Valid_Result Decode(String s, Ref_String s_decoded) {
        Cmd_Item_Valid_Result res = Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

        ST st = ST.ST_NO;
        ST st_next = ST.ST_NO;

        char c_commas = '\0';

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            switch (st) {

                // ST_NO -> ST_STR_NOT_COMMAS / ST_STR_NOT_COMMAS_ESC
                case ST_NO: {
                    if (c != '\"' && c != '\'') {
                        if (c != '\\') {
                            st_next = ST.ST_STR_NOT_COMMAS;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                        } else {
                            st_next = ST.ST_STR_NOT_COMMAS_ESC;
                            //s_decoded.Value += c; // Skip
                            res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                        }
                    } else {
                        c_commas = c;
                        st_next = ST.ST_STR_WITH_COMMAS;
                        //s_decoded.Value += c; // Skip
                        res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                    }
                }
                break;

                // ST_STR_NOT_COMMAS -> ST_STR_NOT_COMMAS / ST_STR_NOT_COMMAS_ESC / ST_ERROR
                case ST_STR_NOT_COMMAS: {
                    if (c != '\\') {
                        if (c != '\"' && c != '\'') {
                            st_next = ST.ST_STR_NOT_COMMAS;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                        } else {
                            st_next = ST.ST_ERROR;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                        }
                    } else {
                        st_next = ST.ST_STR_NOT_COMMAS_ESC;
                        //s_decoded.Value += c; // Skip
                        res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                    }
                }
                break;

                // ST_STR_NOT_COMMAS_ESC -> ST_STR_NOT_COMMAS
                case ST_STR_NOT_COMMAS_ESC: {
                    st_next = ST.ST_STR_NOT_COMMAS;
                    Append_After_ESC(c, s_decoded);
                    res = Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS; //CMD_ITEM_OK;
                }
                break;

                // ST_STR_WITH_COMMAS -> ST_STR_WITH_COMMAS / ST_STR_WITH_COMMAS_ESC
                case ST_STR_WITH_COMMAS: {
                    if (c != c_commas) {
                        if (c != '\\') {
                            st_next = ST.ST_STR_WITH_COMMAS;
                            s_decoded.Value += c;
                            res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                        } else {
                            st_next = ST.ST_STR_WITH_COMMAS_ESC;
                            //s_decoded.Value += c; // Skip
                            res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                        }

                    } else {
                        st_next = ST.ST_STR_WITH_COMMAS_END;
                        //s_decoded.Value += c; // Skip
                        res = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                    }
                }
                break;

                // ST_STR_WITH_COMMAS_ESC -> ST_STR_WITH_COMMAS
                case ST_STR_WITH_COMMAS_ESC: {
                    st_next = ST.ST_STR_WITH_COMMAS;
                    Append_After_ESC(c, s_decoded);
                    res = Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
                }
                break;

                // ST_STR_WITH_COMMAS_END -> ST_ERROR
                case ST_STR_WITH_COMMAS_END: {
                    st_next = ST.ST_ERROR;
                    s_decoded.Value += c;
                    res = Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                break;

                // ST_ERROR -> ST_ERROR
                default: {
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

    public Cmd_Item_Str_Esc(String text, String help) {
        super(text, help);

        Type = "Str_Esc";
        Version = "0.02";

    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Ref_String s_decoded = new Ref_String("");
        Cmd_Item_Valid_Result res = Decode(s, s_decoded);
        if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK || res == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
            Value_Str = s_decoded.Value;
        } else {
            Value_Str = s; // Error or Incomplete
        }
        return res;
    }

    @Override
    public boolean Is_Char_Valid(char c, int pos, int len) {
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
