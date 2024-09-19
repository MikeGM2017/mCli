/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mike
 */
public class Cli_Module_Base_Script_Not_Threaded extends Cli_Module {

    protected Cli_History History;

    protected Cli_Output_JavaFX Cli_Output;

    protected Ref_Boolean Cmd_Script_Stop;
    protected Ref_Boolean Cmd_Quit;

    protected Cli_CMD_Processor Cli_Command_Processor;

    protected String Str_Rem;

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_do_script = 1;
    private final int CMD_ID_do_script_no_history = 2;
    private final int CMD_ID_do_script_stop = 3;
    private final int CMD_ID_save_history_as_script = 4;

    private final int CMD_ID_LAST = 5;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    public Cli_Module_Base_Script_Not_Threaded(Cli_History history, Cli_Output_JavaFX cli_output,
            String str_rem, Ref_Boolean cmd_script_stop, Ref_Boolean cmd_quit,
            Cli_CMD_Processor cli_command_processor) {
        super("Base Script");
        History = history;
        Cli_Output = cli_output;
        Str_Rem = str_rem;
        Cmd_Script_Stop = cmd_script_stop;
        Cmd_Quit = cmd_quit;
        Cli_Command_Processor = cli_command_processor;

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

    }

    boolean save_history_as_script(String filename) {
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
            Logger.getLogger(Cli_Module_Base_Script_Not_Threaded.class.getName()).log(Level.SEVERE, null, ex);
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
                Logger.getLogger(Cli_Module_Base_Script_Not_Threaded.class.getName()).log(Level.SEVERE, null, ex);
                Cli_Output.Output_Str("ERROR: file \"" + filename + "\" - close error");
            }
        }
        return true;
    }

    boolean do_script(String filename, boolean is_no_history) {
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(filename));
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - Begin");
            Cli_Output.Output_NewLine();
            boolean is_debug = false;
            Ref_Boolean debug_res = new Ref_Boolean(false);
            String s;
            Cmd_Script_Stop.Value = false;
            Cmd_Quit.Value = false;
            do {
                s = reader.readLine();
                if (s != null && !s.isEmpty()) {
                    String s_trim = s.trim();
                    if (!is_no_history && !is_debug && !s_trim.isEmpty()) {
                        History.History_Put(s_trim);
                    }
                    Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, s_trim);
                    Cli_Output.Output_Str(s_trim);
                    Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                }
            } while (s != null && !Cmd_Script_Stop.Value && !Cmd_Quit.Value);
            Cli_Output.Output_Str(Str_Rem + " Do script " + filename + " - " + (Cmd_Script_Stop.Value ? "Stopped" : "End"));
            Cli_Output.Output_NewLine();
        } catch (FileNotFoundException ex) {
            Cli_Output.Output_Str("File \"" + filename + "\" - not found");
        } catch (IOException ex) {
            Logger.getLogger(Cli_Module_Base_Script_Not_Threaded.class.getName()).log(Level.SEVERE, null, ex);
            Cli_Output.Output_Str("File \"" + filename + "\" - read error");
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException ex) {
                Logger.getLogger(Cli_Module_Base_Script_Not_Threaded.class.getName()).log(Level.SEVERE, null, ex);
                Cli_Output.Output_Str("File \"" + filename + "\" - close error");
            }
        }
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        switch (cmd_id) {

            case CMD_ID_save_history_as_script:
                if (is_debug) {
                    return true;
                }
                 {
                    String filename = cmd.Items.get(4).Value_Str;
                    return save_history_as_script(filename);
                }
            case CMD_ID_do_script:
                if (is_debug) {
                    return true;
                }
                 {
                    String filename = cmd.Items.get(2).Value_Str;
                    boolean is_no_history = false;
                    return do_script(filename, is_no_history);
                }
            case CMD_ID_do_script_no_history:
                if (is_debug) {
                    return true;
                }
                 {
                    String filename = cmd.Items.get(2).Value_Str;
                    boolean is_no_history = true;
                    return do_script(filename, is_no_history);
                }
            case CMD_ID_do_script_stop:
                if (is_debug) {
                    return true;
                }
                Cmd_Script_Stop.Value = true;
                return true;

        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
