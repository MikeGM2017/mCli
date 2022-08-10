/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;
import javafx.application.Platform;
import javafx.scene.control.TextInputControl;

/**
 *
 * @author mike
 */
public class Cli_Output_JavaFX_Threaded extends Cli_Output_JavaFX {

    protected enum Output_Cmd_ID {
        OUTPUT_CMD_ID_NO,
        OUTPUT_CMD_ID_ADD,
        OUTPUT_CMD_ID_CLEAR,
        OUTPUT_CMD_ID_RETURN,
        OUTPUT_CMD_ID_CARET_POS_SET,
        OUTPUT_CMD_ID_LAST,
        OUTPUT_CMD_ID_UNDEFINED
    }

    protected class Output_Cmd_Item {

        Output_Cmd_ID ID;
        String Text;
        int Input_Str_Len;
        int Input_Str_Pos;

        Output_Cmd_Item(Output_Cmd_ID id) {
            ID = id;
        }

        Output_Cmd_Item(Output_Cmd_ID id, String text) {
            ID = id;
            Text = text;
        }

        Output_Cmd_Item(Output_Cmd_ID id, int input_str_len, int input_str_pos) {
            ID = id;
            Input_Str_Len = input_str_len;
            Input_Str_Pos = input_str_pos;
        }

        Output_Cmd_Item(Output_Cmd_Item cmd) {
            ID = cmd.ID;
            Text = cmd.Text;
            Input_Str_Len = cmd.Input_Str_Len;
            Input_Str_Pos = cmd.Input_Str_Pos;
        }

    }

    protected List<Output_Cmd_Item> Output_Cmd_List = new ArrayList<>();

    protected Runnable Output_Runnable;
    protected Thread Output_Thread;
    protected ReentrantLock Output_Lock = new ReentrantLock();

    Cli_Output_JavaFX_Threaded(TextInputControl object) {
        super(object);
    }

    void Output_Cmd_Item_Execute_Return() {
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

    void Output_Cmd_Item_Execute_Caret_Pos_Set(int input_str_len, int input_str_pos) {
        int output_text_len = textInputControl.getText().length();
        int caret_pos = output_text_len - input_str_len + input_str_pos;
        if (caret_pos < 0) {
            caret_pos = 0;
        }
        textInputControl.positionCaret(caret_pos);
    }

    void Output_Cmd_Item_Execute(Output_Cmd_Item cmd) {
        switch (cmd.ID) {
            case OUTPUT_CMD_ID_ADD:
                textInputControl.appendText(cmd.Text);
                break;
            case OUTPUT_CMD_ID_CLEAR:
                textInputControl.clear();
                break;
            case OUTPUT_CMD_ID_RETURN:
                Output_Cmd_Item_Execute_Return();
                break;
            case OUTPUT_CMD_ID_CARET_POS_SET:
                Output_Cmd_Item_Execute_Caret_Pos_Set(cmd.Input_Str_Len, cmd.Input_Str_Pos);
                break;
        }
    }

    @Override
    boolean Output_Init() {
        Output_Cmd_List.clear();

        Output_Thread = new Thread(new Runnable() {

            @Override
            public void run() {
                Runnable updater = new Runnable() {

                    @Override
                    public void run() {
                        Output_Lock.lock();
                        try {
                            if (!Output_Cmd_List.isEmpty()) {
                                for (int i = 0; i < Output_Cmd_List.size(); i++) {
                                    Output_Cmd_Item cmd = new Output_Cmd_Item(Output_Cmd_List.get(i));
                                    Platform.runLater(() -> {
                                        Output_Cmd_Item_Execute(cmd);
                                    });
                                }
                                Output_Cmd_List.clear();
                            }
                        } finally {
                            Output_Lock.unlock();
                        }
                    }
                };

                while (true) {
                    try {
                        Thread.sleep(1); // ms
                    } catch (InterruptedException ex) {
                    }

                    // UI update is run on the Application thread
                    Platform.runLater(updater);
                }
            }

        });
        // don't let thread prevent JVM shutdown
        Output_Thread.setDaemon(true);
        Output_Thread.start();

        return false;
    }

    protected void Output_Cmd_List_Add(Output_Cmd_Item item) {
        Output_Lock.lock();
        try {
            Output_Cmd_List.add(item);
        } finally {
            Output_Lock.unlock();
        }
    }

    @Override
    boolean Output_Close() {
        Output_Cmd_List.clear();
        return false;
    }

    @Override
    boolean Output_Clear() {
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_CLEAR));
        return true;
    }

    @Override
    void Output_NewLine() {
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_ADD, "\n"));
    }

    @Override
    void Output_Char(char c) {
        String s = "";
        s += c;
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_ADD, s));
    }

    @Override
    void Output_Char(String c) {
        String s = "";
        s += c;
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_ADD, s));
    }

    @Override
    void Output_Str(String s) {
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_ADD, s));
    }

    @Override
    void Output_Return() {
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_RETURN));
    }

    @Override
    void Caret_Pos_Set(int input_str_len, int input_str_pos) {
        Output_Cmd_List_Add(new Output_Cmd_Item(Output_Cmd_ID.OUTPUT_CMD_ID_CARET_POS_SET, input_str_len, input_str_pos));
    }

}
