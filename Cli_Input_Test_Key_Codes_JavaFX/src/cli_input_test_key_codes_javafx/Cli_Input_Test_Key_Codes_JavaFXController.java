/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_input_test_key_codes_javafx;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextInputControl;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;

/**
 *
 * @author mike
 */
public class Cli_Input_Test_Key_Codes_JavaFXController implements Initializable {
    
    @FXML
    private TextArea Cli_Input_TextArea;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        Cli_Input_TextArea.setEditable(false);
        Cli_Input_TextArea.appendText("\nCli Input Key Codes JavaFX started\n");
    }    
    
    @FXML
    public void On_Key_Pressed_Action(KeyEvent event) {
        TextInputControl TextInputObj = (TextInputControl) event.getSource();
        if (null != TextInputObj) {

            KeyCode keyCode = event.getCode();
            
            if (event.isControlDown() && keyCode == KeyCode.C) {
                TextInputObj.appendText("Ctrl+C\n");
            } else if (event.isControlDown() && keyCode == KeyCode.Z) {
                TextInputObj.appendText("Ctrl+Z\n");
            } else if (event.isControlDown() && keyCode == KeyCode.BACK_SLASH) {
                TextInputObj.appendText("Ctrl+Backslash\n");
            } else {

                switch (keyCode) {
                    case ENTER:
                        TextInputObj.appendText("ENTER\n");
                        break;
                    case TAB:
                        TextInputObj.appendText("TAB\n");
                        break;
                    case UP:
                        TextInputObj.appendText("UP\n");
                        break;
                    case DOWN:
                        TextInputObj.appendText("DOWN\n");
                        break;
                    case RIGHT:
                        TextInputObj.appendText("RIGHT\n");
                        break;
                    case LEFT:
                        TextInputObj.appendText("LEFT\n");
                        break;
                    case BACK_SPACE:
                        TextInputObj.appendText("BACK\n");
                        break;
                    case DELETE:
                        TextInputObj.appendText("DELETE\n");
                        break;
                    case HOME:
                        TextInputObj.appendText("HOME\n");
                        break;
                    case END:
                        TextInputObj.appendText("END\n");
                        break;
                    default:
                        TextInputObj.appendText(event.getText());
                        break;
                }

            }

        }
        event.consume();
    }
    
}
