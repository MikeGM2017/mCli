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
public class Cmd_Item_MAC extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        switch (pos) {
            case 2:
            case 5:
            case 8:
            case 11:
            case 14:
                return (c == ':' || c == '-');
            default:
                if (c >= '0' && c <= '9') {
                    return true;
                }
                if (c >= 'a' && c <= 'f') {
                    return true;
                }
                if (c >= 'A' && c <= 'F') {
                    return true;
                }
        }
        return false;
    }

    Cmd_Item_MAC(String text, String help) {
        super(text, help);
        Type = "MAC";
    }

    @Override
    public String Debug_Value_Get() {
        return "11:22:33:DD:EE:FF";
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        if (s.length() < 17) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (s.length() > 17) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
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
