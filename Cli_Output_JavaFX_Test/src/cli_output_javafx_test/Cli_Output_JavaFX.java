/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_output_javafx_test;

import javafx.scene.control.TextInputControl;

/**
 *
 * @author mike
 */
class Cli_Output_JavaFX {

    TextInputControl textInputControl;

    Cli_Output_JavaFX(TextInputControl object) {
        textInputControl = object;
        //textInputControl.setEditable(false);
    }

    boolean Output_Init() {
        return false;
    }

    boolean Output_Close() {
        return false;
    }

    boolean Output_Clear() {
        textInputControl.clear();
        return true;
    }

    void Output_NewLine() {
        textInputControl.appendText("\n");
    }

    void Output_Char(char c) {
        String s = "";
        s += c;
        textInputControl.appendText(s);
    }

    void Output_Str(String s) {
        textInputControl.appendText(s);
    }

    void Output_Return() {
        String s = textInputControl.getText();
        int pos = s.length() - 1;
        for (pos = s.length() - 1; pos >= 0; pos--) {
            char c = s.charAt(pos);
            if (c == '\n') {
                pos++;
                break;
            }
        }
        textInputControl.positionCaret(pos);
    }

}
