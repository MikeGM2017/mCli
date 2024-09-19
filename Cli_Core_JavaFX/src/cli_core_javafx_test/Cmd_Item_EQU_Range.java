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
class Cmd_Item_EQU_Range extends Cmd_Item_EQU {

    public List<String> Words = new ArrayList<>();

    public Cmd_Item_EQU_Range(String text, String help, List<String> words) {
        super(text, help);

        Type = "EQU_Range";

        Words = words;
    }

    @Override
    public String Debug_Value_Get() {
        if (Words.size() > 0) {
            return Words.get(0);
        }
        return Text;
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

        boolean is_incomplete_found = false;
        for (int i = 0; i < Words.size(); i++) {
            if (Words.get(i).equals(s)) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OK;
            }
            if (Words.get(i).substring(0, s.length()).equals(s)) {
                is_incomplete_found = true;
            }
        }
        if (is_incomplete_found) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
    }

    @Override
    public boolean Is_Space_After_Add(String s) {
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
            return true;
        }
        return false;
    }

    @Override
    public List<String> Incomplete_Tail_List_Get(String s) {
        List<String> tail_list = new ArrayList<>();
        for (int i = 0; i < Words.size(); i++) {
            if (Words.get(i).substring(0, s.length()).equals(s)) {
                tail_list.add(Words.get(i).substring(s.length()));
            }
        }
        return tail_list;
    }

}
