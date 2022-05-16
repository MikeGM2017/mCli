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
public class Cmd_Item_Word extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (c >= 'a' && c <= 'z') {
            return true;
        }
        if (c >= 'A' && c <= 'Z') {
            return true;
        }
        if (c == '_') {
            return true;
        }
        //if (pos > 0 && c >= '0' && c <= '9') return true;
        if (c >= '0' && c <= '9') {
            return true;
        }
        return false;
    }

    public Cmd_Item_Word(String text, String help) {
        super(text, help);
        Type = "Word";
    }

    public String Debug_Value_Get() {
        return Text;
    }

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

        if (Text.equals(s)) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        if (s.length() < Text.length()) {
            if (Text.substring(0, s.length()).equals(s)) {
                return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
            }
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
    }

    public List<String> Incomplete_Tail_List_Get(String s) {
        List<String> tail_list = new ArrayList<>();
        if (s.length()< Text.length()) {
            if (Text.substring(0, s.length()).equals(s)) {
                tail_list.add(Text.substring(0, s.length()));
            }
        }
        return tail_list;
    }
}
