/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_output_javafx_test;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextInputControl;
import javafx.scene.input.KeyEvent;

/**
 *
 * @author mike
 */
public class Cli_Output_JavaFX_TestController implements Initializable {

    @FXML
    private TextArea Cli_Input_TextArea;

    private Cli_Output_JavaFX Cli_Output;

    int State;

    private void Test_State_0() {
        Cli_Output.Output_Clear();
        Cli_Output.Output_Char('X');
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(" - Ok");
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("End");
        Cli_Output.Output_Return();
    }

    private void Test_State_1() {
        boolean res_clear;
        res_clear = Cli_Output.Output_Clear();
        if (res_clear) {
            Cli_Output.Output_Str("Cleared");
        } else {
            Cli_Output.Output_Str("Not Cleared");
        }
    }

    private void Test_State_2() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Finished");
        Cli_Output.Output_NewLine();
    }
    
    private void Test_State_3() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Exit");
        Cli_Output.Output_NewLine();
        Platform.exit();
        System.exit(0);
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        Cli_Input_TextArea.setEditable(false);
        Cli_Input_TextArea.appendText("\nCli Input JavaFX started\n");

        Cli_Output = new Cli_Output_JavaFX(Cli_Input_TextArea);

        Test_State_0();
        State = 1;
    }

    @FXML
    public void On_Key_Pressed_Action(KeyEvent event) {
        TextInputControl TextInputObj = (TextInputControl) event.getSource();
        if (null != TextInputObj) {

            switch (State) {
                case 0:
                    Test_State_0();
                    State = 1;
                    break;
                case 1:
                    Test_State_1();
                    State = 2;
                    break;
                case 2:
                    Test_State_2();
                    State = 3;
                    break;
                case 3:
                    Test_State_3();
                    State = 0;
                    break;
            }

        }
        event.consume();
    }

}
