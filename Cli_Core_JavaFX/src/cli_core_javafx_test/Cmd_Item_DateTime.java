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
public class Cmd_Item_DateTime extends Cmd_Item_Date {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (pos == 11 && c == ' ') {
            return true; // "yyyy-mm-dd HH-MM-SS"
        }
        if (pos == 11 && c == '"') {
            return true; // "yyyy-mm-dd" - без времени
        }
        if (pos == 17 && c == '"') {
            return true; // "yyyy-mm-dd HH-MM" - без секунд
        }
        switch (pos) {
            case 0:
            case 20:
                return (c == '"');
            case 5:
            case 8:
            case 14:
            case 17:
                return (c == '-');
            case 11:
                return (c == ' ');
        }
        return (c >= '0' && c <= '9');
    }

    public Cmd_Item_DateTime(String text, String help) {
        super(text, help);
        Type = "DateTime";
    }

    @Override
    public String Debug_Value_Get() {
        return "\"2018-01-02 12-13-14\"";
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

        // Time
        if (s.length() >= 13) {
            int H = s.charAt(12) - '0';
            if (H < 0 || H > 2) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_HH;
            if (s.length() > 13) {
                s_HH = s.substring(12, 14);
            } else {
                s_HH = s.substring(12, 14);
            }
            int HH = Integer.parseInt(s_HH);
            if (HH > 23) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.length() >= 16) {
            int M = s.charAt(15) - '0';
            if (M < 0 || M > 5) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_MM;
            if (s.length() > 16) {
                s_MM = s.substring(15, 17);
            } else {
                s_MM = s.substring(15, 16);
            }
            int MM = Integer.parseInt(s_MM);
            if (MM > 59) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.length() >= 19) {
            int S = s.charAt(18) - '0';
            if (S < 0 || S > 5) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_SS;
            if (s.length() > 19) {
                s_SS = s.substring(18, 20);
            } else {
                s_SS = s.substring(18, 19);
            }
            int SS = Integer.parseInt(s_SS);
            if (SS > 59) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
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

    @Override
    public boolean Is_Space_After_Add(String s) {
        if (s.length() >= 17) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
                return true;
            }
        }
        return false;
    }

}
