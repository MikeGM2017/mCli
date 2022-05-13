/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_input_javafx_test;

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
public class Cli_Input_JavaFX_TestController implements Initializable {

    @FXML
    private TextArea Cli_Input_TextArea;

    private Cli_Output_JavaFX Cli_Output;
    private Cli_Input_JavaFX Cli_Input;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        Cli_Input_TextArea.appendText("\nCli Input JavaFX started\n");

        Cli_Output = new Cli_Output_JavaFX(Cli_Input_TextArea);
        String Chars_Not_Allowed_Str = "@`|";
        Cli_Input = new Cli_Input_JavaFX(Cli_Output, Chars_Not_Allowed_Str);

        Cli_Input.Title_Set("cli demo");
        Cli_Input.User_Set("root");
        Cli_Input.Level_Set("top level");
        Cli_Input.Invitation_Set("> ");
        Cli_Input.Divider_L_Set("[");
        Cli_Input.Divider_R_Set("]");
        Cli_Input.Input_Init();

        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
    }

    @FXML
    public void On_Key_Pressed_Action(KeyEvent event) {
        boolean is_cmd_back = false;
        boolean is_cmd_delete = false;

        TextInputControl TextInputObj = (TextInputControl) event.getSource();

        if (null != TextInputObj) {

            Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());

            Cli_Input_Item item = Cli_Input.On_Key_Pressed(event);

            if (item != null) {

                switch (item.Type_Get()) {
                    case INPUT_CMD_ENTER:

                        if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL) {

                            Cli_Output.Output_NewLine();

                            if (item.Text_Get().equals("Q") || item.Text_Get().equals("quit")) {
                                System.out.println("Quit - Processed");
                                Platform.exit();
                                System.exit(0);
                            } else if (item.Text_Get().equals("C") || item.Text_Get().equals("clear")) {
                                Cli_Output.Output_Clear();
                                Cli_Output.Output_Str("Clear - Processed");
                                Cli_Output.Output_NewLine();
                            } else if (item.Text_Get().equals("A") || item.Text_Get().equals("ask")) {
                                Cli_Output.Output_Str("Is it right?(yes/no)");
                                Cli_Input.Input_Str_Set_Empty();
                                Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
                                break;
                            } else if (item.Text_Get().equals("P") || item.Text_Get().equals("passwd")) {
                                Cli_Output.Output_Str("Password:");
                                Cli_Input.Input_Str_Set_Empty();
                                Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PASSWD);
                                break;
                            } else if (item.Text_Get().equals("W") || item.Text_Get().equals("wait")) {
                                Cli_Output.Output_Str("Wait (Press Enter to stop):");
                                Cli_Output.Output_NewLine();
                                Cli_Input.Input_Str_Set_Empty();
                                Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_WAIT);
                                Cli_Input.Wait_Count_Set(10);
                                break;
                            } else if (item.Text_Get().equals("H") || item.Text_Get().equals("help")) {
                                Help_Print();
                                Cli_Output.Output_NewLine();
                            } else if (item.Text_Get().length() > 0) {
                                Cli_Output.Output_Str(item.Text_Get() + " - Not Processed");
                                Cli_Output.Output_NewLine();
                            }

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PROMPT) {
                            Cli_Output.Output_NewLine();
                            if (item.Text_Get().equals("Y") || item.Text_Get().equals("y")
                                    || item.Text_Get().equals("YES") || item.Text_Get().equals("Yes") || item.Text_Get().equals("yes")) {
                                Cli_Output.Output_Str("Answer: Yes");
                            } else {
                                Cli_Output.Output_Str("Answer: No");
                            }
                            Cli_Output.Output_NewLine();

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PASSWD) {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Password:" + item.Text_Get());
                            Cli_Output.Output_NewLine();

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT) {
                            Cli_Input.Wait_Count_Set(-1);
                            Cli_Output.Output_Str("Wait stopped");
                            Cli_Output.Output_NewLine();
                        }

                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);

                        break;
                    case INPUT_CMD_TAB:
                        Cli_Output.Output_NewLine();
                        //Cli_Output.Output_Str("TAB: \"" + item.Text_Get() + "\" - Not Processed");
                        Help_Print();
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        break;
                    case INPUT_CMD_UP:
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("UP: \"" + item.Text_Get() + "\" - Not Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        break;
                    case INPUT_CMD_DOWN:
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("DOWN: \"" + item.Text_Get() + "\" - Not Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        break;
                    case INPUT_CMD_BACK:
                        is_cmd_back = true;
                        break;
                    case INPUT_CMD_DELETE:
                        is_cmd_delete = true;
                        break;
                    case INPUT_CMD_CTRL_C:
                    case INPUT_CMD_CTRL_Z:
                    case INPUT_CMD_CTRL_BACKSLASH:
                        if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT) {
                            Cli_Input.Wait_Count_Set(-1);
                            Cli_Output.Output_Str("Wait stopped");
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);
                        } else {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Input.Input_Str_Set_Empty();
                        }
                        break;
                    default:
                        String s = item.Type_Get().toString() + ":\"" + item.Text_Get() + "\"";
                        System.out.println(s);
                        break;
                }

            }

        }

        if (!is_cmd_back && !is_cmd_delete) {
            event.consume();
        }

    }

    protected void Help_Print() {
        Cli_Output.Output_Str("Help: Q - quit, C - clear, H - help, A - prompt(y/n), P - password(no echo), W - wait");
    }

}
