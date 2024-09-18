/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author mike
 */
public class Cmd_Item_Word_List extends Cmd_Item_Word_Range {

    protected boolean Is_Repeat;

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
        if (pos > 0 && c == ',') {
            return true;
        }
        return false;
    }

    public List<String> Values_Str = new ArrayList<>();

    Cmd_Item_Word_List(String text, String help, List<String> words, boolean is_repeat) {
        super(text, help, words);
        Is_Repeat = is_repeat;
        Type = "Word_List";
    }

    Cmd_Item_Word_List(String text, String help, List<String> words) {
        this(text, help, words, false);
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;
        Values_Str.clear();
        //        Values_Incomplete.clear();

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        int s_pos_beg = 0;
        int s_pos_end = 0;
        while (s_pos_end < s.length()) {
            if (s.charAt(s_pos_end) == ',') {
                Values_Str.add(s.substring(s_pos_beg, s_pos_end));
                s_pos_end++;
                s_pos_beg = s_pos_end;
            }
            s_pos_end++;
        }
        if (s_pos_beg <= s_pos_end - 1) {
            //if (s_pos_beg < s_pos_end - 1) {
            //Values_Str.add(s.substring(s_pos_beg, s_pos_end));
            Values_Str.add(s.substring(s_pos_beg));
        }

        if (Values_Str.size() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        Set<String> values_set = new HashSet<>();
        if (!Is_Repeat) {
            for (int i = 0; i < Values_Str.size(); i++) {
                if (!values_set.contains(Values_Str.get(i))) {
                    values_set.add(Values_Str.get(i));
                } else {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            }
        }

        boolean is_equal_all = true;
        int found_count = 0;
        for (int i = 0; i < Values_Str.size(); i++) {
            boolean found = false;
            for (int j = 0; j < Words.size(); j++) {
                if (Values_Str.get(i).equals(Words.get(j))) {
                    found = true;
                    found_count++;
                    break;
                }
            }
            if (!found) {
                is_equal_all = false;
                break;
            }
        }

        if (s.charAt(s.length() - 1) == ',') {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
        }

        if (!Is_Repeat && is_equal_all && found_count == Words.size()) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        if (!Is_Repeat && is_equal_all && found_count < Words.size()) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;
        }
        if (Is_Repeat && is_equal_all) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;
        }

        //        string s_last = Values_Str.back();
        //        for (int i = 0; i < Words.size(); i++) {
        //            if (s_last.size() < Words[i].size()) {
        //                if (Words[i].substr(0, s_last.size()) == s_last)
        //                    Values_Incomplete.push_back(Words[i]);
        //            }
        //        }
        //        if (Values_Incomplete.size() > 0) return CMD_ITEM_INCOMPLETE;
        String s_last = Values_Str.get(Values_Str.size() - 1);
        boolean is_incomplete_found = false;
        for (int i = 0; i < Words.size(); i++) {
            if (s_last.length() < Words.get(i).length()) {
                if (Words.get(i).substring(0, s_last.length()).equals(s_last)) {
                    //Values_Incomplete.push_back(Words[i]);
                    is_incomplete_found = true;
                }
            }
        }
        //if (Values_Incomplete.size() > 0) return CMD_ITEM_INCOMPLETE;
        if (is_incomplete_found) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
        }

        //        bool is_incomplete_found = false;
        //        for (int i = 0; i < Words.size(); i++) {
        //            if (Words[i] == s) return CMD_ITEM_OK;
        //            if (Words[i].substr(0, s.size()) == s) is_incomplete_found = true;
        //        }
        //        if (is_incomplete_found)
        //            return CMD_ITEM_INCOMPLETE;
        //Values.clear();
        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
    }

    @Override
    public List<String> Incomplete_Tail_List_Get(String s) {
        List<String> tail_list = new ArrayList<>();
        Cmd_Item_Valid_Result res = Parse(s);
        if (res == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE) {

            Set<String> values_set = new HashSet<>();
            if (!Is_Repeat) {
                for (int i = 0; i < Values_Str.size(); i++) {
                    if (!values_set.contains(Values_Str.get(i))) {
                        values_set.add(Values_Str.get(i));
                    }
                }
            }

            String s_last = Values_Str.get(Values_Str.size() - 1);
            for (int i = 0; i < Words.size(); i++) {
                if (Words.get(i).substring(0, s_last.length()).equals(s_last)) {
                    if (!values_set.contains(Words.get(i))) {
                        tail_list.add(Words.get(i).substring(s_last.length()));
                    }
                }
            }
        }
        return tail_list;
    }
}
