/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.Locale;
import java.util.function.UnaryOperator;
import javafx.application.Platform;
import javafx.scene.control.TextFormatter;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;

/**
 *
 * @author mike
 */
class Cli_Input_JavaFX extends Cli_Core_JavaFX_Test {

    static String Invitation_DEF = "> ";
    static String Divider_L_DEF = "[";
    static String Divider_R_DEF = "]";

    protected String Title;
    protected String User;
    protected String Level;
    protected String Invitation;
    protected String Divider_L;
    protected String Divider_R;
    protected String Input_Str;

    protected String Prompt_Str;

    protected boolean Is_Echo;

    protected int Input_Str_Pos;

    protected boolean Is_Quit;

    protected Cli_Output_JavaFX Cli_Output;

    protected String Chars_Not_Allowed_Str;

    protected boolean Is_Input_Str_Pos_Too_Left;

    protected Input_Mode_Type Input_Mode;

    protected Runnable Wait_Runnable;
    protected Thread Wait_Thread;
    protected int Wait_Count;

    public Cli_Input_JavaFX(Cli_Output_JavaFX cli_output, String chars_not_allowed_str) {
        Cli_Output = cli_output;
        Chars_Not_Allowed_Str = chars_not_allowed_str;

        Is_Echo = true;
        Input_Str = "";
        Input_Str_Pos = 0;
        Prompt_Str = "";

        Is_Input_Str_Pos_Too_Left = false;

        Input_Mode = Input_Mode_Type.INPUT_MODE_NORMAL;
        Wait_Count = -1;
    }

    public void Title_Set(String s) {
        Title = s;
    }

    public String Title_Get() {
        return Title;
    }

    public void User_Set(String s) {
        User = s;
    }

    public String User_Get() {
        return User;
    }

    public void Level_Set(String s) {
        Level = s;
    }

    public String Level_Get() {
        return Level;
    }

    public void Invitation_Set(String s) {
        Invitation = s;
    }

    public String Invitation_Get() {
        return Invitation;
    }

    public void Divider_L_Set(String s) {
        Divider_L = s;
    }

    public String Divider_L_Get() {
        return Divider_L;
    }

    public void Divider_R_Set(String s) {
        Divider_R = s;
    }

    public String Divider_R_Get() {
        return Divider_R;
    }

    public void Prompt_Str_Set(String s) {
        Prompt_Str = s;
    }

    public String Prompt_Str_Get() {
        return Prompt_Str;
    }

    public void Is_Echo_Set(boolean v) {
        Is_Echo = v;
    }

    public boolean Is_Echo_Get() {
        return Is_Echo;
    }

    public void Input_Str_Pos_Set(int v) {
        Input_Str_Pos = v;
    }

    public int Input_Str_Pos_Get() {
        return Input_Str_Pos;
    }

    public void Chars_Not_Allowed_Str_Set(String s) {
        Chars_Not_Allowed_Str = s;
    }

    public String Chars_Not_Allowed_Str_Get() {
        return Chars_Not_Allowed_Str;
    }

    public void Input_Mode_Set(Input_Mode_Type input_mode) {
        Input_Mode = input_mode;
    }

    public Input_Mode_Type Input_Mode_Get() {
        return Input_Mode;
    }

    public boolean Input_Init() {

        boolean cli_ouput_init_res = Cli_Output.Output_Init();

        UnaryOperator<TextFormatter.Change> filter = change -> {
            if (change.isAdded()) {
                String s1 = change.getText();
                String s2 = s1;

                if (Input_Mode == Input_Mode_Type.INPUT_MODE_PASSWD) {
                    s2 = "";
                    for (int i = 0; i < s1.length(); i++) {
                        if (s1.charAt(i) == '\n') {
                            Input_Mode = Input_Mode_Type.INPUT_MODE_NORMAL;
                            s2 = "\n";
                            break;
                        }
                    }
                    change.setText(s2);
                } else if (Input_Mode == Input_Mode_Type.INPUT_MODE_WAIT) {
                    s2 = s1;
                    for (int i = 0; i < s1.length(); i++) {
                        if (s1.charAt(i) == '\n') {
                            //Input_Mode = Input_Mode_Type.INPUT_MODE_NORMAL;
                            s2 = "\n";
                            break;
                        }
                    }
                    change.setText(s2);
                    if (Wait_Count <= 0) {
                        Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);
                    }
                } else {
                    // remove illegal characters:
                    boolean found_not_valid = false;
                    for (int i = 0; i < s2.length(); i++) {
                        String c = Character.toString(s2.charAt(i));
                        if (!Is_Char_Valid(c)) {
                            found_not_valid = true;
                            s2 = s2.replace(c, "");
                        }
                    }

                    if (!found_not_valid) {
                        return change;
                    }
                    if (s2.length() != s1.length()) {
                        change.setText(s2);
                    }
                }
                // modify caret position if size of text changed:
                int delta = s2.length() - s1.length();
                change.setCaretPosition(change.getCaretPosition() + delta);
                change.setAnchor(change.getAnchor() + delta);
            }
            return change;
        };

        Cli_Output.textInputControl.setTextFormatter(new TextFormatter<String>(filter));

        if (Wait_Thread == null) {
            Wait_Thread = new Thread(new Runnable() {

                @Override
                public void run() {
                    Runnable updater = new Runnable() {

                        @Override
                        public void run() {

                            Cli_Output.Output_Str("Wait " + Integer.toString(Wait_Count));
                            Cli_Output.Output_NewLine();

                        }
                    };

                    while (true) {

                        if (Wait_Count > 0) {
                            Platform.runLater(updater);

                            try {
                                Thread.sleep(1000);
                            } catch (InterruptedException ex) {
                            }

                            Wait_Count--;

                            if (Wait_Count <= 0) {
                                Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);
                                if (Wait_Count == 0) {
                                    //Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str(Invitation_Full_Get());
                                }
                            }

                        } else {

                            try {
                                Thread.sleep(1); // ms
                            } catch (InterruptedException ex) {
                            }

                        }

                        // UI update is run on the Application thread
                    }

                }

            });
            // don't let thread prevent JVM shutdown
            Wait_Thread.setDaemon(true);
            Wait_Thread.start();
        }

        return cli_ouput_init_res;
    }

    public boolean Input_Restore() {
        return Cli_Output.Output_Close();
    }

    public boolean Input_Clear() {
        return Cli_Output.Output_Clear();
    }

    public String Invitation_Full_Get() { // Attention: Should be used for print cli invitation

        if (!Prompt_Str.isEmpty()) {
            return Prompt_Str;
        }

        String s = "";
        if (!Title.isEmpty()) {
            s += Divider_L + Title + Divider_R;
        }

        if (!User.isEmpty()) {
            s += Divider_L + User + Divider_R;
        }

        if (!Level.isEmpty()) {
            s += Divider_L + Level + Divider_R;
        }

        if (!Invitation.isEmpty()) {
            s += Invitation;
        }

        return s;
    }

    public void Invitation_Print() {
        Cli_Output.Output_Str(Invitation_Full_Get());
    }

    public String Input_Str_Get() {
        return Input_Str;
    }

    public void Input_Str_Set(String s) {
        Input_Str = s;
    }

    public void Input_Str_Set_Empty() {
        Input_Str = "";
        Input_Str_Pos = 0;
    }

    public void Wait_Count_Set(int v) {
        Wait_Count = v;
    }

    public int Wait_Count_Get() {
        return Wait_Count;
    }

    public void Input_Add_Char_To_End(String s) {
        Input_Str += s;
        Input_Str_Pos = Input_Str.length();
    }

    public void Input_Add_Char_Middle(String s) {
        String s1 = "";
        if (Input_Str_Pos > 0) {
            s1 = Input_Str.substring(0, Input_Str_Pos);
        }

        String s2 = "";
        if (Input_Str_Pos < Input_Str.length()) {
            s2 = Input_Str.substring(Input_Str_Pos, Input_Str.length());
        }

        Input_Str = s1 + s + s2;
        Input_Str_Pos++;
    }

    public void Input_Back() {
        if (Input_Str_Pos == 0) {
            Is_Input_Str_Pos_Too_Left = true;
        } else {
            Is_Input_Str_Pos_Too_Left = false;
        }
        if (Input_Str_Pos < 0) {
            Input_Str_Pos = 0;
        }
        if (Input_Str_Pos > Input_Str.length()) {
            Input_Str_Pos = Input_Str.length();
        }
        if (Input_Str.length() > 0 && Input_Str_Pos > 0) {
            if (Input_Str_Pos == Input_Str.length()) {
                Input_Str = Input_Str.substring(0, Input_Str_Pos - 1);
                Input_Str_Pos = Input_Str.length();
            } else {
                String s1 = Input_Str.substring(0, Input_Str_Pos - 1);
                String s2 = Input_Str.substring(Input_Str_Pos, Input_Str.length());
                Input_Str = s1 + s2;
                Input_Str_Pos--;
            }
        }
    }

    public void Input_Delete() {
        if (Input_Str_Pos < 0) {
            Input_Str_Pos = 0;
        }
        if (Input_Str_Pos > Input_Str.length()) {
            Input_Str_Pos = Input_Str.length();
        }
        if (Input_Str.length() > 0 && Input_Str_Pos < Input_Str.length()) {
            String s1 = Input_Str.substring(0, Input_Str_Pos);
            String s2 = Input_Str.substring(Input_Str_Pos + 1, Input_Str.length());
            Input_Str = s1 + s2;
            //Input_Str_Pos = Input_Str_Pos_prev; // Not changed
        }
    }

    public void Input_Str_To_Output() {
        if (Is_Echo_Get()) {
            Cli_Output.Output_Return();
            Cli_Output.Output_Str(Invitation_Full_Get());
            if (Input_Str_Pos > 0) {
                Cli_Output.Output_Str(Input_Str.substring(0, Input_Str_Pos));
            }
            Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
        }
    }

    public void Input_Str_Modified_To_Output(String s_prev) {
        if (Is_Echo_Get()) {
            int text_len = Cli_Output.textInputControl.getLength();
            Cli_Output.textInputControl.replaceText(text_len - s_prev.length(), text_len, Input_Str);
            Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
        }
    }

    public void Input_End() {
        Input_Str_Pos = Input_Str.length();
        //Input_Str_To_Output();
        Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
    }

    protected void On_Key_RIGHT() {
        if (Input_Str_Pos < Input_Str.length()) {
            Input_Str_Pos++;
        }
        Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
    }

    protected void On_Key_LEFT() {
        if (Input_Str_Pos > 0) {
            Input_Str_Pos--;
        }
        Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
    }

    protected void On_Key_HOME() {
        Input_Str_Pos = 0;
        Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
    }

    protected void On_Key_END() {
        Input_Str_Pos = Input_Str.length();
        Cli_Output.Caret_Pos_Set(Input_Str.length(), Input_Str_Pos);
    }

    protected void On_Key_BACK() {
        Input_Back();
    }

    protected void On_Key_DELETE() {
        Input_Delete();
    }

    protected void On_Key_CTRL_C() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(Invitation_Full_Get());
        Input_Str_Set_Empty();
    }

    protected void On_Key_CTRL_Z() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(Invitation_Full_Get());
        Input_Str_Set_Empty();
    }

    protected void On_Key_CTRL_Backslash() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(Invitation_Full_Get());
        Input_Str_Set_Empty();
    }

    public boolean Is_Char_Valid(String char_str) {
        if (!Chars_Not_Allowed_Str.isEmpty()) {
            if (Chars_Not_Allowed_Str.contains(char_str)) {
                return false;
            }
        }
        return true;
    }

    protected boolean On_Key_Any(String s) {
        if (Is_Char_Valid(s)) {
            if (Input_Str_Get().length() == Input_Str_Pos_Get()) {
                Input_Add_Char_To_End(s);
            } else {
                Input_Add_Char_Middle(s);
            }
            return true;
        }
        return false;
    }

    public Cli_Input_Item On_Key_Pressed(KeyEvent event) {
        Cli_Input_Item item = null;

        KeyCode keyCode = event.getCode();

        if (event.isControlDown() && keyCode == KeyCode.C) {
            //On_Key_CTRL_C();
            item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_C, Input_Str_Get());
        } else if (event.isControlDown() && keyCode == KeyCode.Z) {
            //On_Key_CTRL_Z();
            item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_Z, Input_Str_Get());
        } else if (event.isControlDown() && keyCode == KeyCode.BACK_SLASH) {
            //On_Key_CTRL_Backslash();
            item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_BACKSLASH, Input_Str_Get());
        } else {

            switch (keyCode) {
                case ENTER:
                    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, Input_Str_Get());
                    break;
                case TAB:
                    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_TAB, Input_Str_Get());
                    break;
                case UP:
                    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_UP, Input_Str_Get());
                    break;
                case DOWN:
                    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_DOWN, Input_Str_Get());
                    break;
                case RIGHT:
                    On_Key_RIGHT();
                    break;
                case LEFT:
                    On_Key_LEFT();
                    break;
                case HOME:
                    On_Key_HOME();
                    break;
                case END:
                    On_Key_END();
                    break;
                case BACK_SPACE:
                    On_Key_BACK();
                    if (!Is_Input_Str_Pos_Too_Left) {
                        item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_BACK, Input_Str_Get());
                    }
                    break;
                case DELETE:
                    On_Key_DELETE();
                    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_DELETE, Input_Str_Get());
                    break;
                default:
                    boolean is_linux = false;
                    String os = System.getProperty("os.name", "generic").toLowerCase(Locale.US);
                    if (os.contains("linux")) {
                        is_linux = true;
                    }
                    if (is_linux) {

                        if (!On_Key_Any(event.getText())) {
                            //item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_INVALID_CHAR, Input_Str_Get());
                        }

                    } else {

                        // Windows only
                        String s = event.getText();
                        if (s.length() > 0) {
                            char c = s.charAt(0);
                            if (Character.isUpperCase(c) && event.isShiftDown()) {
                                s = event.getText().toLowerCase();
                            } else if (event.isShiftDown()) {
                                s = event.getText().toUpperCase();
                            }
                            if (!On_Key_Any(s)) {
                                //item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_INVALID_CHAR, Input_Str_Get());
                            }
                        }

                    }
                    break;
            }

        }

        return item;
    }

    public void Input_sleep(int sleep_sec) {
        try {
            Thread.sleep(sleep_sec * 1000);
        } catch (InterruptedException ex) {
            System.out.println("Input_sleep() - Failed");
        }
    }

}
