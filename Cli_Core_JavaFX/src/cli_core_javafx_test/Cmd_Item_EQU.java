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
public class Cmd_Item_EQU extends Cmd_Item_Word {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        // == != < > <= >= & | && ||

        if (len > 2) {
            return false;
        }

        if (pos == 0) {
            if (c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|') {
                return true;
            }
        } else if (pos == 1) {
            if (c == '=' || c == '&' || c == '|') {
                return true;
            }
        }

        return false;
    }

    public Cmd_Item_EQU(String text, String help) {
        super(text, help);
        Type = "EQU";
    }

}
