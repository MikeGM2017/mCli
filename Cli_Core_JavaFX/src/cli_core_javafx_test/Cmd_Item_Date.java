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
public class Cmd_Item_Date extends Cmd_Item_Str {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        switch (pos) {
            case 0:
            case 11:
                return (c == '"');
            case 5:
            case 8:
                return (c == '-');
        }
        return (c >= '0' && c <= '9');
    }

    public Cmd_Item_Date(String text, String help) {
        super(text, help);
        Type = "Date";
    }

    @Override
    public String Debug_Value_Get() {
        return "\"2018-01-02\"";
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        if (s.length() == 1 && s.charAt(0) == '"') {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (s.length() >= 1 && s.charAt(0) != '"') {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        // Date
        if (s.length() >= 7) {
            int m = s.charAt(6) - '0';
            if (m < 0 || m > 1) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            if (s.length() >= 8) {
                String s_mm = s.substring(6, 8);
                int mm = Integer.parseInt(s_mm);
                if (mm == 0 || mm > 12) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
            }
        }

        if (s.length() >= 10) {
            int d = s.charAt(9) - '0';
            if (d < 0 || d > 3) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            if (s.length() >= 11) {
                String s_dd = s.substring(9, 11);
                int dd = Integer.parseInt(s_dd);
                if (dd == 0 || dd > 31) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
            }
        }

        if (s.length() == 2) {
            if (s.charAt(0) == '"' && s.charAt(1) == '"') {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR; //Cmd_Item_Valid_Result.CMD_ITEM_OK;
            }
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }

        if (s.charAt(s.length() - 1) != '"') {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_OK;
    }

}
