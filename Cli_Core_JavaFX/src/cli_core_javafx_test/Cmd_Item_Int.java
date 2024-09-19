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
public class Cmd_Item_Int extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (pos == 0) {
            if (c == '+') {
                return true;
            }
            if (c == '-') {
                return true;
            }
        }
        return (c >= '0' && c <= '9');
    }

    protected int Char_To_N(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        }
        return 0;
    }

    public int Value_Int;

    public Cmd_Item_Int(String text, String help) {
        super(text, help);

        Type = "Int";
        Version = "0.02";

        Value_Int = 0;
    }

    @Override
    public String Debug_Value_Get() {
        return "1";
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;
        Value_Int = 0;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        long v = 0;
        long vMax = Integer.MAX_VALUE;
        for (int pos = 0; pos < s.length(); pos++) {
            int n = Char_To_N(s.charAt(pos));
            v = v * 10 + n;
            if (v > vMax) {
                return Cmd_Item_Valid_Result.CMD_ITEM_TOO_LONG;
            }
        }

        Value_Int = (int) v;

        return Cmd_Item_Valid_Result.CMD_ITEM_OK;
    }

    @Override
    public boolean Is_Space_After_Add(String s) {
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
            return true;
        }
        return false;
    }

}
