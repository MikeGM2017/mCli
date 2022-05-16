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
public class Cmd_Token {

    protected String Text;

    public Cmd_Token(String text) {
        Text = text;
    }

    public String Text_Get() {
        return Text;
    }

    public String Text_Get_Without_COMMAS() {
        if (Text.length() >= 2 && Text.charAt(0) == '\"' && Text.charAt(Text.length() - 1) == '\"') {
            return Text.substring(1, Text.length() - 2);
        }
        if (Text.length() >= 2 && Text.charAt(0) == '\'' && Text.charAt(Text.length() - 1) == '\'') {
            return Text.substring(1, Text.length() - 2);
        }
        return Text;
    }

    public String To_String() {
        return "Text:" + Text;
    }

}
