using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Script : Cli_Module
    {
        protected Cli_History History;

        protected Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        protected Ref_Boolean Cmd_Script_Stop;
        protected Ref_Boolean Cmd_Quit;

        protected Cli_CMD_Processor Cli_Command_Processor;

        protected String Str_Rem;

        protected String Script_Thread_FileName = "";
        protected bool Script_Thread_Is_No_History = false;

        Ref_String Script_Command_Str;
        Ref_String Script_Label_Str;

        static Thread Script_Thread = null;

        Ref_String Script_Dir_Str;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_do_script,
            CMD_ID_do_script_no_history,
            CMD_ID_do_script_stop,
            CMD_ID_save_history_as_script,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        static public void Script_Thread_Func(object data)
        {
            Cli_Module_Base_Script main_obj = (Cli_Module_Base_Script)data;
            while (true)
            {
                if (main_obj != null)
                {
                    if (!String.IsNullOrEmpty(main_obj.Script_Thread_FileName))
                    {
                        String filename = main_obj.Script_Thread_FileName;
                        bool is_no_history = main_obj.Script_Thread_Is_No_History;

                        StreamReader inputFile = null;
                        try
                        {
                            inputFile = new StreamReader(filename);

                            if (inputFile != null)
                            {
                                main_obj.Cli_Output.Output_NewLine();
                                main_obj.Cli_Output.Output_NewLine();
                                main_obj.Cli_Output.Output_Str(main_obj.Str_Rem + " Do script " + filename + " - Begin");
                                main_obj.Cli_Output.Output_NewLine();

                                bool is_debug = false;
                                Ref_Boolean debug_res = new Ref_Boolean(false);
                                String s = null;
                                do
                                {
                                    if (!main_obj.Cli_Input.Is_Ctrl_C_Pressed_Get())
                                    {
                                        s = inputFile.ReadLine();
                                        if (!String.IsNullOrEmpty(s))
                                        {
                                            String s_trim = s.Trim();
                                            if (!is_no_history && !is_debug && !String.IsNullOrEmpty(s_trim))
                                            {
                                                main_obj.History.History_Put(s_trim);
                                            }
                                            Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, s_trim);
                                            main_obj.Cli_Output.Output_Str(s_trim);

                                            main_obj.Script_Command_Str.Value = "";
                                            main_obj.Script_Label_Str.Value = "";

                                            main_obj.Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                                            while (main_obj.Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT)
                                            {
                                                main_obj.Cli_Input.Input_sleep(1);
                                            }

                                            if (main_obj.Script_Command_Str.Value.Length > 0)
                                            {
                                                main_obj.Execute_Script_Command(is_debug, debug_res);
                                                main_obj.Script_Command_Str.Value = "";
                                            }

                                            //@Warning: Command "check goto <label>" - special case: is moves file position
                                            if (main_obj.Script_Label_Str.Value.Length > 0)
                                            {
                                                bool label_found = main_obj.Execute_Command_check_goto_label(inputFile, main_obj.Script_Label_Str.Value);
                                                if (!label_found)
                                                {
                                                    main_obj.Cli_Output.Output_NewLine();
                                                    main_obj.Cli_Output.Output_Str("ERROR: label \"" + main_obj.Script_Label_Str.Value + "\" - not found, script stopped");
                                                    main_obj.Cli_Output.Output_NewLine();
                                                    main_obj.Cmd_Script_Stop.Value = true; // Stop - label not found
                                                }
                                                main_obj.Script_Label_Str.Value = "";
                                            }

                                        }
                                    }
                                    else
                                    {
                                        main_obj.Cmd_Script_Stop.Value = true; // Stop By Ctrl+C
                                    }
                                } while (!inputFile.EndOfStream && s != null && !main_obj.Cmd_Script_Stop.Value && !main_obj.Cmd_Quit.Value);

                                if (main_obj.Cli_Input.Is_Ctrl_C_Pressed_Get())
                                {
                                    main_obj.Cli_Output.Output_Str(main_obj.Str_Rem + " Do script " + filename + " - Stopped by Ctrl+C");
                                    main_obj.Cli_Input.Is_Ctrl_C_Pressed_Clear();
                                }
                                else
                                {
                                    main_obj.Cli_Output.Output_Str(main_obj.Str_Rem + " Do script " + filename + " - " + (main_obj.Cmd_Script_Stop.Value ? "Stopped" : "End"));
                                }
                                main_obj.Cli_Output.Output_NewLine();
                                main_obj.Cli_Output.Output_NewLine();
                                main_obj.Cli_Output.Output_Str(main_obj.Cli_Input.Invitation_Full_Get());
                                main_obj.Cli_Input.Input_Str_Set_Empty();
                            }
                            else
                            {
                                main_obj.Cli_Input.Input_sleep(1);
                            }

                        }
                        catch (FileNotFoundException ex)
                        {
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_Str("File \"" + filename + "\" - not found");
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_Str(main_obj.Cli_Input.Invitation_Full_Get());
                            main_obj.Cli_Input.Input_Str_Set_Empty();
                        }
                        catch (IOException ex)
                        {
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_Str("File \"" + filename + "\" - read error");
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_NewLine();
                            main_obj.Cli_Output.Output_Str(main_obj.Cli_Input.Invitation_Full_Get());
                            main_obj.Cli_Input.Input_Str_Set_Empty();
                        }
                        finally
                        {
                            if (inputFile != null)
                            {
                                inputFile.Close();
                            }
                            main_obj.Script_Thread_FileName = "";
                            main_obj.Script_Thread_Is_No_History = false;
                        }
                    }
                    else
                    {
                        main_obj.Cli_Input.Input_sleep(1);
                    }
                }
                System.Threading.Thread.Sleep(1000);
            }
        }

        public Cli_Module_Base_Script(Cli_History history, Cli_Input_CS cli_input, Cli_Output_CS cli_output,
            String str_rem, Ref_Boolean cmd_script_stop, Ref_Boolean cmd_quit,
            Cli_CMD_Processor cli_command_processor,
            Ref_String script_command_str, Ref_String script_label_str, Ref_String script_dir_str) : base("Base Script")
        {

            Version = "0.03";

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

            if (!Directory.Exists(Script_Dir_Str.Value))
            {
                Directory.CreateDirectory(Script_Dir_Str.Value);
            }

            {
                // do script stop // @Attention: Must be before do script "file"
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_do_script_stop);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_do_script);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_do_script_no_history);
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
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_save_history_as_script);
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

            Script_Thread = new Thread(Script_Thread_Func);
            Script_Thread.IsBackground = true; //@Warning
            Script_Thread.Start(this);
        }

        ~Cli_Module_Base_Script()
        {
            Cli_Input.Input_Restore();
        }

        bool script_filename_check(string s)
        {
            if (s.Length == 0) return false; // Failed
            for (int i = 0; i < s.Length; i++)
            {
                char c = s[i];
                if (c >= 'a' && c <= 'z') continue; // Ok
                if (c >= 'A' && c <= 'Z') continue; // Ok
                if (c >= '0' && c <= '9') continue; // Ok
                if (c == '_') continue; // Ok
                return false; // Failed
            }
            return true; // Ok
        }

        bool save_history_as_script(string cmd_filename)
        {
            bool res_filename_check = script_filename_check(cmd_filename);
            if (!res_filename_check)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
                Cli_Output.Output_NewLine();
                return true;
            }

            string filename = Script_Dir_Str.Value + "/" + cmd_filename;
            StreamWriter outputFile = new StreamWriter(filename);
            if (outputFile != null)
            {
                for (int i = 0; i < History.History_Size_Get() - 1; i++) // @Attention : Last cmd not saved!
                {
                    outputFile.WriteLine(History.History_Item_Get(i));
                }
                outputFile.Close();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Script saved from history as " + filename);
                Cli_Output.Output_NewLine();
            }
            else
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("ERROR: can not open file " + filename + " for write");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        bool Execute_Command_check_goto_label(StreamReader inputFile, string label_str)
        {
            bool stop = false;
            bool found = false;
            inputFile.DiscardBufferedData();
            inputFile.BaseStream.Seek(0, System.IO.SeekOrigin.Begin);
            do
            {
                string s = inputFile.ReadLine();
                if (s != null && !inputFile.EndOfStream)
                {
                    string kw_check = "check";
                    int kw_check_index = s.IndexOf(kw_check, 0);
                    if (kw_check_index >= 0)
                    {
                        string kw_label = "label";
                        int kw_label_index = s.IndexOf(kw_label, kw_check_index + kw_check.Length + 1);
                        if (kw_label_index > 0)
                        {
                            int label_str_index = s.IndexOf(label_str, kw_label_index + kw_label.Length + 1);
                            if (label_str_index > 0)
                            {
                                found = true;
                                stop = true; // Ok - Label Found
                            }
                        }
                    }
                }
                else
                {
                    stop = true; // Failed - Label Not Found
                }
            } while (!stop);

            return found;
        }

        public void Execute_Script_Command(bool is_debug, Ref_Boolean debug_res)
        {
            string Script_Command_Str_Trim1 = Script_Command_Str.Value.Trim();
            bool is_commas_found = false;
            if (Script_Command_Str_Trim1.Length >= 2
                    && Script_Command_Str_Trim1[0] == '\"'
                    && Script_Command_Str_Trim1[Script_Command_Str_Trim1.Length - 1] == '\"')
            {
                is_commas_found = true;
            }
            if (Script_Command_Str_Trim1.Length >= 2
                    && Script_Command_Str_Trim1[0] == '\''
                    && Script_Command_Str_Trim1[Script_Command_Str_Trim1.Length - 1] == '\'')
            {
                is_commas_found = true;
            }
            string Script_Command_Str_Trim2;
            if (is_commas_found)
            {
                Script_Command_Str_Trim2 = Script_Command_Str_Trim1.Substring(1, Script_Command_Str_Trim1.Length - 2);
            }
            else
            {
                Script_Command_Str_Trim2 = Script_Command_Str_Trim1;
            }
            Cli_Input_Item input_item2 = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, Script_Command_Str_Trim2);
            Script_Command_Str.Value = "";
            Cli_Command_Processor.Process_Input_Item(input_item2, is_debug, debug_res);
        }

        bool do_script(string cmd_filename, bool is_no_history)
        {
            bool res_filename_check = script_filename_check(cmd_filename);
            if (!res_filename_check)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
                Cli_Output.Output_NewLine();
                return true;
            }

            string filename = Script_Dir_Str.Value + "/" + cmd_filename;

            Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

            Cmd_Script_Stop.Value = false;
            Script_Thread_FileName = filename;
            Script_Thread_Is_No_History = is_no_history;
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            Level_Description level = new Level_Description();
            string parameter;
            if (Levels.Count > 0)
            {
                level = Levels[Levels.Count - 1];
                parameter = level.Parameter;
            }
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_save_history_as_script:
                    if (is_debug) return true;
                    {
                        string filename = cmd.Items[4].Value_Str;
                        return save_history_as_script(filename);
                    }
                case Local_Cmd_ID.CMD_ID_do_script:
                    if (is_debug) return true;
                    {
                        string filename = cmd.Items[2].Value_Str;
                        bool is_no_history = false;
                        return do_script(filename, is_no_history);
                    }
                case Local_Cmd_ID.CMD_ID_do_script_no_history:
                    if (is_debug) return true;
                    {
                        string filename = cmd.Items[2].Value_Str;
                        bool is_no_history = true;
                        return do_script(filename, is_no_history);
                    }
                case Local_Cmd_ID.CMD_ID_do_script_stop:
                    if (is_debug) return true;
                    {
                        Cmd_Script_Stop.Value = true;
                        return true;
                    }
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }
    }
}
