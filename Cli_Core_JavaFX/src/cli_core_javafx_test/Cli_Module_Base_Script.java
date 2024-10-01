/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mike
 */
public class Cli_Module_Base_Script extends Cli_Module {

    protected Cli_History History;

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected Ref_Boolean Cmd_Script_Stop;
    protected Ref_Boolean Cmd_Quit;

    protected Cli_CMD_Processor Cli_Command_Processor;

    protected String Str_Rem;

    Ref_String Script_Command_Str;
    Ref_String Script_Label_Str;

    Ref_String Script_Dir_Str;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_do_script = 1;
    private final int CMD_ID_do_script_no_history = 2;
    private final int CMD_ID_do_script_stop = 3;
    private final int CMD_ID_save_history_as_script = 4;

    private final int CMD_ID_LAST = 5;
    //};

    protected Runnable Script_Runnable;
    protected Thread Script_Thread;
    protected String Script_Thread_FileName;
    protected boolean Script_Thread_Is_No_History;

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Script(Cli_History history, Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output,
            String str_rem, Ref_Boolean cmd_script_stop, Ref_Boolean cmd_quit,
            Cli_CMD_Processor cli_command_processor,
            Ref_String script_command_str, Ref_String script_label_str, Ref_String script_dir_str) {
        super("Base Script");

        Version = "0.04";

        History = history;
        Cli_Input = cli_input;
        Cli_Output = cli_output;
        Str_Rem = str_rem;
        Cmd_Script_Stop = cmd_script_stop;
        Cmd_Quit = cmd_quit;
        Cli_Command_Processor = cli_command_processor;
        Script_Command_Str = script_command_str;
        Script_Label_Str = script_label_str;
        Script_Dir_Str = script_dir_str;

        try {
            Files.createDirectories(Paths.get(Script_Dir_Str.Value));
        } catch (IOException ex) {
        }

        {
            // do script stop // @Attention: Must be before do script "file"
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_do_script_stop);
            cmd.Text_Set("do script stop");
            cmd.Help_Set("stop execute script");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd.Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd.Item_Add(new Cmd_Item_Word("stop", "stop execute script"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>"
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_do_script);
            cmd.Text_Set("do script \"<file>\"");
            cmd.Help_Set("execute script from file");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd.Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd.Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>" no history
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_do_script_no_history);
            cmd.Text_Set("do script \"<file>\" no history");
            cmd.Help_Set("execute script from file, not save to history");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd.Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd.Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            cmd.Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd.Item_Add(new Cmd_Item_Word("history", "not save to history"));
            Cmd_Add(cmd);
        }
        {
            // save history as script "<file>"
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_save_history_as_script);
            cmd.Text_Set("save history as script \"<file>\"");
            cmd.Help_Set("save history as script to file");
            cmd.Is_Global_Set(true);
            cmd.Item_Add(new Cmd_Item_Word("save", "save"));
            cmd.Item_Add(new Cmd_Item_Word("history", "save history"));
            cmd.Item_Add(new Cmd_Item_Word("as", "save history as"));
            cmd.Item_Add(new Cmd_Item_Word("script", "save history as script to file"));
            cmd.Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }

        Script_Runnable = new Runnable() {
            @Override
            public void run() {
                Script_Thread_FileName = "";
                Script_Thread_Is_No_History = false;
                while (true) {
                    if (!Script_Thread_FileName.isEmpty()) {

                        Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

                        String filename = Script_Thread_FileName;
                        boolean is_no_history = Script_Thread_Is_No_History;

                        Script_Thread_FileName = "";
                        Script_Thread_Is_No_History = false;

                        Execute_Script(filename, is_no_history);

                    } else {
                        Cli_Input.Input_sleep(1);
                    }
                }
            }

            private void Execute_Script(String filename, boolean is_no_history) {
                BufferedReader reader = null;
                try {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
                    reader.mark(1);
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - Begin");
                    Cli_Output.Output_NewLine();
                    boolean is_debug = false;
                    Ref_Boolean debug_res = new Ref_Boolean(false);
                    String s = "";
                    Cmd_Script_Stop.Value = false;
                    Cmd_Quit.Value = false;
                    do {
                        if (!Cli_Input.Is_Ctrl_C_Pressed_Get()) {
                            s = reader.readLine();
                            if (s != null && !s.isEmpty()) {
                                String s_trim = s.trim();
                                if (!is_no_history && !is_debug && !s_trim.isEmpty()) {
                                    History.History_Put(s_trim);
                                }
                                Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, s_trim);
                                Cli_Output.Output_Str(s_trim);

                                Script_Command_Str.Value = "";
                                Script_Label_Str.Value = "";
                                Script_Thread_FileName = "";
                                Script_Thread_Is_No_History = false;

                                Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                                while (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT) {
                                    Cli_Input.Input_sleep(1);
                                }

                                if (Script_Command_Str.Value.length() > 0) {
                                    Execute_Script_Command(is_debug, debug_res);
                                    Script_Command_Str.Value = "";
                                }

                                //@Warning: Command "check goto <label>" - special case: is moves file position
                                if (Script_Label_Str.Value.length() > 0) {
                                    String label = Script_Label_Str.Value;
                                    Script_Label_Str.Value = "";
                                    boolean label_found = Execute_Command_check_goto_label(reader, label);
                                    if (!label_found) {
                                        Cli_Output.Output_NewLine();
                                        Cli_Output.Output_Str("ERROR: label \"" + label + "\" - not found, script stopped");
                                        Cli_Output.Output_NewLine();
                                        Cmd_Script_Stop.Value = true; // Stop - label not found
                                    }
                                }

                                if (Script_Thread_FileName.length() > 0) {
                                    String nested_script_filename = Script_Thread_FileName;
                                    boolean nested_script_is_no_history = Script_Thread_Is_No_History;

                                    Script_Thread_FileName = "";
                                    Script_Thread_Is_No_History = false;

                                    Execute_Script(nested_script_filename, nested_script_is_no_history);
                                }

                            }
                        } else {
                            Cmd_Script_Stop.Value = true; // Stop By Ctrl+C
                        }
                    } while (s != null && !Cmd_Script_Stop.Value && !Cmd_Quit.Value);
                    if (Cli_Input.Is_Ctrl_C_Pressed_Get()) {
                        Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - Stopped by Ctrl+C");
                        Cli_Input.Is_Ctrl_C_Pressed_Clear();
                    } else {
                        Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - " + (Cmd_Script_Stop.Value ? "Stopped" : "End"));
                        if (Cmd_Script_Stop.Value) {
                            Cmd_Script_Stop.Value = false;
                        }
                    }
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Input.Input_Str_Set_Empty();
                } catch (FileNotFoundException ex) {
                    Cli_Output.Output_Str("File \"" + filename + "\" - not found");
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Input.Input_Str_Set_Empty();
                } catch (IOException ex) {
                    Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
                    Cli_Output.Output_Str("File \"" + filename + "\" - read error");
                } catch (Exception ex) {
                    Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
                } finally {
                    try {
                        if (reader != null) {
                            reader.close();
                            ///Cli_Output.Output_Str("File \"" + filename + "\" - Ok");
                        }
                    } catch (IOException ex) {
                        Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
                        Cli_Output.Output_Str("File \"" + filename + "\" - close error");
                    } catch (Exception ex) {
                        Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        };

        Script_Thread = new Thread(Script_Runnable);
        Script_Thread.start();

    }

    boolean script_filename_check(String s) {
        if (s.length() == 0) {
            return false; // Failed
        }
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c >= 'a' && c <= 'z') {
                continue; // Ok
            }
            if (c >= 'A' && c <= 'Z') {
                continue; // Ok
            }
            if (c >= '0' && c <= '9') {
                continue; // Ok
            }
            if (c == '_') {
                continue; // Ok
            }
            return false; // Failed
        }
        return true; // Ok
    }

    boolean save_history_as_script(String cmd_filename) {

        boolean res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        boolean is_linux = false;
        String os = System.getProperty("os.name", "generic").toLowerCase(Locale.US);
        if (os.contains("linux")) {
            is_linux = true;
        }

        String filename = Script_Dir_Str.Value + "/" + cmd_filename;
        if (!is_linux) {
            filename = Script_Dir_Str.Value + "\\" + cmd_filename;
        }

        FileWriter writer = null;
        try {
            writer = new FileWriter(filename);
            String ls = System.getProperty("line.separator");
            for (int i = 0; i < History.History_Size_Get() - 1; i++) // @Attention : Last cmd not saved!
            {
                writer.write(History.History_Item_Get(i));
                writer.write(ls);
            }
        } catch (IOException ex) {
            Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
            Cli_Output.Output_Str("ERROR: file \"" + filename + "\" - write error");
        } finally {
            try {
                if (writer != null) {
                    writer.close();
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Script saved from history as " + filename);
                    Cli_Output.Output_NewLine();
                } else {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("ERROR: can not open file " + filename + " for write");
                    Cli_Output.Output_NewLine();
                }
            } catch (IOException ex) {
                Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
                Cli_Output.Output_Str("ERROR: file \"" + filename + "\" - close error");
            }
        }
        return true;
    }

    public boolean Execute_Command_check_goto_label(BufferedReader inputFile, String label_str) {
        boolean stop = false;
        boolean found = false;
        try {

            inputFile.reset();

            do {

                String s = "";
                boolean s_stop = false;
                int c = -1;

                do {
                    try {
                        c = inputFile.read();
                        if (c != -1 && c != '\r' && c != '\n') {
                            s += (char) c;
                        } else if (c == '\r' || c == '\n') {
                            c = 0; // End of line found
                            s_stop = true;
                        } else {
                            c = -1; // EOF Found
                            s_stop = true;
                        }
                    } catch (IOException ex) {
                        c = -1; // Error -> EOF
                        s_stop = true;
                    }
                } while (!s_stop);

                if (s.length() > 0) {
                    String kw_check = "check";
                    int kw_check_index = s.indexOf(kw_check, 0);
                    if (kw_check_index >= 0) {
                        String kw_label = "label";
                        int kw_label_index = s.indexOf(kw_label, kw_check_index + kw_check.length() + 1);
                        if (kw_label_index > 0) {
                            int label_str_index = s.indexOf(label_str, kw_label_index + kw_label.length() + 1);
                            if (label_str_index > 0) {
                                found = true;
                                stop = true; // Ok - Label Found
                            }
                        }
                    }
                } else if (c == -1) {
                    stop = true; // Failed - Label Not Found
                }

            } while (!stop);

        } catch (IOException ex) {
            Logger.getLogger(Cli_Module_Base_Script.class.getName()).log(Level.SEVERE, null, ex);
        }

        return found;
    }

    public void Execute_Script_Command(boolean is_debug, Ref_Boolean debug_res) {
        String Script_Command_Str_Trim1 = Script_Command_Str.Value.trim();
        Script_Command_Str.Value = "";
        boolean is_commas_found = false;
        if (Script_Command_Str_Trim1.length() >= 2
                && Script_Command_Str_Trim1.charAt(0) == '\"'
                && Script_Command_Str_Trim1.charAt(Script_Command_Str_Trim1.length() - 1) == '\"') {
            is_commas_found = true;
        }
        if (Script_Command_Str_Trim1.length() >= 2
                && Script_Command_Str_Trim1.charAt(0) == '\''
                && Script_Command_Str_Trim1.charAt(Script_Command_Str_Trim1.length() - 1) == '\'') {
            is_commas_found = true;
        }
        String Script_Command_Str_Trim2;
        if (is_commas_found) {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1.substring(1, Script_Command_Str_Trim1.length() - 1);
        } else {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1;
        }
        Cli_Input_Item input_item2 = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, Script_Command_Str_Trim2);
        Cli_Command_Processor.Process_Input_Item(input_item2, is_debug, debug_res);
    }

    boolean do_script(String cmd_filename, boolean is_no_history) {
        boolean res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        boolean is_linux = false;
        String os = System.getProperty("os.name", "generic").toLowerCase(Locale.US);
        if (os.contains("linux")) {
            is_linux = true;
        }

        String filename = Script_Dir_Str.Value + "/" + cmd_filename;
        if (!is_linux) {
            filename = Script_Dir_Str.Value + "\\" + cmd_filename;
        }

        Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

        Cmd_Script_Stop.Value = false;
        Script_Thread_FileName = filename;
        Script_Thread_Is_No_History = is_no_history;
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {

            case CMD_ID_save_history_as_script:
                if (is_debug) {
                    return true;
                } else {
                    String filename = cmd.Items.get(4).Value_Str;
                    return save_history_as_script(filename);
                }
            case CMD_ID_do_script:
                if (is_debug) {
                    return true;
                } else {
                    String filename = cmd.Items.get(2).Value_Str;
                    boolean is_no_history = false;
                    return do_script(filename, is_no_history);
                }
            case CMD_ID_do_script_no_history:
                if (is_debug) {
                    return true;
                } else {
                    String filename = cmd.Items.get(2).Value_Str;
                    boolean is_no_history = true;
                    return do_script(filename, is_no_history);
                }
            case CMD_ID_do_script_stop:
                if (is_debug) {
                    return true;
                } else {
                    Cmd_Script_Stop.Value = true;
                    return true;
                }

        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
