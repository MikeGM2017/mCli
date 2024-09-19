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
public class Cmd_Item_Assignment_Mark extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        // =
        if (len == 1 && pos == 0 && c == '=') {
            return true;
        }
        return false;
    }

    public Cmd_Item_Assignment_Mark(String text, String help) {
        super(text, help);

        Type = "Assignment_Mark";

    }

}
