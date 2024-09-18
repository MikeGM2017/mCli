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
public class Cmd_Item_Base {

    protected String Type;
    protected String Text;
    protected String Help;
    protected String Version;

    protected boolean Is_Char_Valid(char c, int pos, int len) {
        return true; // Допустимы любые символы в любой позиции
    }

    public String Value_Str;

    public Cmd_Item_Base(String text, String help) {
        Type = "Base";
        Version = "0.01"; //@Warning: Dummy value - Version is not set
        Text = text;
        Help = help;
        Value_Str = "";
    }

    public String Debug_Value_Get() {
        return Text;
    }

    public String Type_Get() {
        return Type;
    }

    public String Text_Get() {
        return Text;
    }

    public String Help_Get() {
        return Help;
    }

    public String Version_Get() {
        return Version;
    }

    public boolean Is_Str_Valid(String s) {
        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return false;
            }
        }
        return true;
    }

    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        if (Text.equals(s)) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
    }

    public String To_String() {
        String s = Type + ": Text:\"" + Text_Get() + "\" "
                + ": Value_Str:\"" + Value_Str + "\" ";
        return s;
    }

    public List<String> Incomplete_Tail_List_Get(String s) {
        List<String> tail_list = new ArrayList<>();
        return tail_list;
    }

    public boolean Is_Space_After_Add(String s) {
        return true;
    }

}
