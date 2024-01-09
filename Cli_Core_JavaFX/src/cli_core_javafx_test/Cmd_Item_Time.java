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
public class Cmd_Item_Time extends Cmd_Item_Date {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (pos == 6 && c == '"') {
            return true; // "HH-MM" - без секунд
        }
        switch (pos) {
            case 0:
            case 9:
                return (c == '"');
            case 3:
            case 6:
                return (c == '-' || c == ':');
        }
        return (c >= '0' && c <= '9');
    }

    Cmd_Item_Time(String text, String help) {
        super(text, help);
        Type = "Time";
    }

    @Override
    public String Debug_Value_Get() {
        return "\"12-13-14\"";
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

        // Time
        if (s.length() >= 2) {
            int H = s.charAt(1) - '0';
            if (H < 0 || H > 2) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_HH;
            if (s.length() > 2) {
                s_HH = s.substring(1, 3);
            } else {
                s_HH = s.substring(1, 2);
            }
            int HH = Integer.parseInt(s_HH);
            if (HH > 23) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.length() >= 5) {
            int M = s.charAt(4) - '0';
            if (M < 0 || M > 5) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_MM;
            if (s.length() > 5) {
                s_MM = s.substring(4, 6);
            } else {
                s_MM = s.substring(4, 5);
            }
            int MM = Integer.parseInt(s_MM);
            if (MM > 59) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
        }

        if (s.length() >= 8) {
            int S = s.charAt(7) - '0';
            if (S < 0 || S > 5) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            String s_SS;
            if (s.length() > 8) {
                s_SS = s.substring(7, 9);
            } else {
                s_SS = s.substring(7, 8);
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
        if (s.length() >= 10) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
                return true;
            }
        }
        return false;
    }
}
