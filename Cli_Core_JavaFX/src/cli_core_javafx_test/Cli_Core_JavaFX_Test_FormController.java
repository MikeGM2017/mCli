/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextInputControl;
import javafx.scene.input.KeyEvent;
import javafx.scene.text.Font;

/**
 *
 * @author mike
 */
public class Cli_Core_JavaFX_Test_FormController implements Initializable {

    @FXML
    protected TextArea Cli_Input_TextArea;

    protected Cli_Output_JavaFX Cli_Output;
    protected Cli_Input_JavaFX Cli_Input;

    protected List<Level_Description> Levels;

    protected Cmd_Token_Parser Token_Parser;

    protected String Str_Rem_DEF;

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege = new Ref_Cli_Cmd_Privilege_ID(Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_USER_DEF);

    protected Cli_Modules Modules;

    protected Cli_CMD_Processor CMD_Processor;
    protected Cli_TAB_Processor TAB_Processor;

    protected Ref_Boolean Cmd_Exit = new Ref_Boolean(false);
    protected Ref_Boolean Cmd_Quit = new Ref_Boolean(false);
    protected Ref_Boolean Cmd_Script_Stop = new Ref_Boolean(false);
    protected Ref_Boolean Cmd_Wait_Stop = new Ref_Boolean(false);
    protected Ref_Boolean Log_Wait_Enable = new Ref_Boolean(true);

    protected Cli_History History = new Cli_History();

    protected boolean is_invitation_print = false;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        Cli_Input_TextArea.setFont(Font.font("monospace"));
        Cli_Input_TextArea.appendText("\nCli Core JavaFX Test started\n");

        Cli_Output = new Cli_Output_JavaFX_Threaded(Cli_Input_TextArea);
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

        Levels = new ArrayList<>();

        Token_Parser = new Cmd_Token_Parser();

        Str_Rem_DEF = "$";

        User_Privilege.Value = Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF;

        Modules = new Cli_Modules();

        boolean tab_log_is_active = false;//!Arg_TAB_Log_Output_File_Name.empty();

        CMD_Processor = new Cli_CMD_Processor(User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
        TAB_Processor = new Cli_TAB_Processor(User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF, tab_log_is_active);

        Modules.Module_Add(new Cli_Module_Base_Quit(Cmd_Exit, Cmd_Quit));

        Modules.Module_Add(new Cli_Module_Base_History(History, Cli_Output));

        Modules.Module_Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

        char C_Single = '?';
        char C_Multy = '*';
        Str_Filter str_filter = new Str_Filter(C_Single, C_Multy);
        Modules.Module_Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
        Modules.Module_Add(new Cli_Module_Base_Modules(User_Privilege, Modules, str_filter, Cli_Output));

        Modules.Module_Add(new Cli_Module_Base_Log(Cli_Input));

        Modules.Module_Add(new Cli_Module_Base_Script_Threaded(History, Cli_Input, Cli_Output,
                Str_Rem_DEF, Cmd_Script_Stop, Cmd_Quit,
                CMD_Processor));
        Modules.Module_Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));
        Modules.Module_Add(new Cli_Module_Base_Wait(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));

        Modules.Module_Add(new Cli_Module_Test_Tab_Min_Max());

        Modules.Module_Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));
    }

    @FXML
    public void On_Key_Pressed_Action(KeyEvent event) {
        boolean is_cmd_back = false;
        boolean is_cmd_delete = false;

        TextInputControl TextInputObj = (TextInputControl) event.getSource();

        if (null != TextInputObj) {

            Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());

            Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(event);

            if (input_item != null) {

                switch (input_item.Type_Get()) {
                    case INPUT_CMD_ENTER:

                        if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL) {

                            if (input_item.Type == Input_Cmd_Type.INPUT_CMD_ENTER) {

                                boolean is_no_history = false;
                                boolean is_debug = false;

                                String s_trim = input_item.Text_Get().trim();

                                if (!is_no_history && !is_debug && !s_trim.isEmpty()) {
                                    History.History_Put(s_trim);
                                }

                                Ref_Boolean debug_res = new Ref_Boolean(false);
                                CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);

                                if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL) {
                                    Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                                    Cli_Input.Input_Str_Set_Empty();
                                }

                            }

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PROMPT) {
                            Cli_Output.Output_NewLine();
                            if (input_item.Text_Get().equals("Y") || input_item.Text_Get().equals("y")
                                    || input_item.Text_Get().equals("YES") || input_item.Text_Get().equals("Yes") || input_item.Text_Get().equals("yes")) {
                                Cli_Output.Output_Str("Answer: Yes");
                            } else {
                                Cli_Output.Output_Str("Answer: No");
                            }
                            Cli_Output.Output_NewLine();

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PASSWD) {
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str("Password:" + input_item.Text_Get());
                            Cli_Output.Output_NewLine();

                        } else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT) {
                            Cmd_Wait_Stop.Value = true;
                            Cli_Input.Wait_Count_Set(-1);
                            Cli_Output.Output_Str("Wait stopped");
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Input.Input_Str_Set_Empty();
                        }

                        break;
                    case INPUT_CMD_TAB:
                        Ref_Boolean is_invitation_print_tab = new Ref_Boolean(true);
                        TAB_Processor.Process_Input_Item(input_item, is_invitation_print_tab);
                        is_invitation_print = is_invitation_print_tab.Value;

                        if (is_invitation_print) {
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        }

                        Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str.length());
                        Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
                        break;
                    case INPUT_CMD_UP:
                        String s_prev_up = Cli_Input.Input_Str_Get();
                        Cli_Input.Input_Str_Set(History.History_Up());
                        Cli_Input.Input_Str_Modified_To_Output(s_prev_up);
                        Cli_Input.Input_End();
                        is_invitation_print = false;
                        break;
                    case INPUT_CMD_DOWN:
                        String s_prev_down = Cli_Input.Input_Str_Get();
                        Cli_Input.Input_Str_Set(History.History_Down());
                        Cli_Input.Input_Str_Modified_To_Output(s_prev_down);
                        Cli_Input.Input_End();
                        is_invitation_print = false;
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
                            Cmd_Script_Stop.Value = true;
                            Cmd_Wait_Stop.Value = true;
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
                        String s = input_item.Type_Get().toString() + ":\"" + input_item.Text_Get() + "\"";
                        System.out.println(s);
                        break;
                }

                if (Cmd_Exit.Value) {
                    Cli_Output.Output_Str("Exit - Processed");
                    Cli_Output.Output_NewLine();
                    Platform.exit();
                    System.exit(0);
                }
                if (Cmd_Quit.Value) {
                    Cli_Output.Output_Str("Quit - Processed");
                    Cli_Output.Output_NewLine();
                    Platform.exit();
                    System.exit(0);
                }

            }

        }

        if (!is_cmd_back && !is_cmd_delete) {
            event.consume();
        }

    }

}
