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
public class Cmd_Item_Point_Var_Name extends Cmd_Item_Word {

    protected char C_Single;
    protected char C_Multy;

    @Override
    public boolean Is_Char_Valid(char c, int pos, int len) {

        if (len < 2) {
            return false;
        }

        if (pos == 0 && c != '.') {
            return false;
        }
        if (c == '.') {
            return true;
        }
        if (c >= 'a' && c <= 'z') {
            return true;
        }
        if (c >= 'A' && c <= 'Z') {
            return true;
        }
        if (c == '_') {
            return true;
        }
        if (pos > 1 && c >= '0' && c <= '9') {
            return true;
        }
        if (pos > 0 && c == C_Single) {
            return true;
        }
        if (pos > 0 && c == C_Multy) {
            return true;
        }

        return false;
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

        return Cmd_Item_Valid_Result.CMD_ITEM_OK;
    }

    public Cmd_Item_Point_Var_Name(String text, String help, char c_single, char c_multy) {
        super(text, help);

        Type = "Point_Var_Name";

        C_Single = c_single;
        C_Multy = c_multy;
    }

    public Cmd_Item_Point_Var_Name(String text, String help) {
        this(text, help, '?', '*');
    }

    @Override
    public String Debug_Value_Get() {
        return ".v";
    }

}
