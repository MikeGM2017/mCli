
#ifndef CLI_MODULE_BASE_SCRIPT_H
#define CLI_MODULE_BASE_SCRIPT_H

#include <fstream>

using namespace std;

#include "Cli_Module.h"

class Cli_Module_Base_Script : public Cli_Module {
protected:

    Cli_History &History;

    Cli_Input_win32api &Cli_Input;
    Cli_Output_win32api &Cli_Output;

    bool &Cmd_Script_Stop;
    bool &Cmd_Quit;

    char *Script_Buf;
    int Script_Buf_Size;

    Cli_CMD_Processor &Cli_Command_Processor;

    string Str_Rem;

    string Script_Thread_FileName;
    bool Script_Thread_Is_No_History;

    string &Script_Command_Str;
    string &Script_Label_Str;

    string &Script_Dir_Str;

    Str_Filter_Abstract &Str_Filter;

    HANDLE Script_Thread;
    DWORD Script_Thread_ID;

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_do_script,
        CMD_ID_do_script_no_history,
        CMD_ID_do_script_stop,
        CMD_ID_save_history_as_script,

        CMD_ID_LAST
    };

public:

    // DEBUG
    stringstream Debug_S_Str;
    int Debug_Count;

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    static DWORD WINAPI Script_Thread_Func(LPVOID data) {
        Cli_Module_Base_Script *main_obj = (Cli_Module_Base_Script *) data;
        while (true) {
            if (main_obj != 0) {
                if (!main_obj->Script_Thread_FileName.empty()) {
                    main_obj->Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

                    string filename = main_obj->Script_Thread_FileName;
                    bool is_no_history = main_obj->Script_Thread_Is_No_History;

                    main_obj->Script_Thread_FileName = "";
                    main_obj->Script_Thread_Is_No_History = false;

                    // DEBUG
                    main_obj->Debug_S_Str.clear();
                    main_obj->Debug_S_Str.str("");
                    main_obj->Debug_S_Str << " Script_Start:";
                    main_obj->Debug_Count = 0;

                    Execute_Script(main_obj, filename, is_no_history);
                } else {
                    main_obj->Cli_Input.Input_sleep(1);
                }
            } else {
                Sleep(1000);
            }
        }
    }

    static string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() ? (s.size() - 1) : 0;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    static void Execute_Script(Cli_Module_Base_Script *main_obj, string filename, bool is_no_history) {

        ifstream inputFile;

        inputFile.open(filename.c_str());

        if (inputFile.is_open()) {
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_Str(main_obj->Str_Rem + " Do script " + filename + " - Begin");
            main_obj->Cli_Output.Output_NewLine();

            bool is_debug = false;
            bool debug_res = false;
            string s;
            do {
                // DEBUG
                main_obj->Debug_Count++;
                main_obj->Debug_S_Str << " " << main_obj->Debug_Count;
                if (!main_obj->Cli_Input.Is_Ctrl_C_Pressed_Get()) {

                    inputFile.getline(main_obj->Script_Buf, main_obj->Script_Buf_Size);
                    s = main_obj->Script_Buf;
                    // DEBUG
                    main_obj->Debug_S_Str << "a";
                    if (!s.empty()) {
                        // DEBUG
                        main_obj->Debug_S_Str << "b";
                        string s_trim = Str_Trim(s);
                        if (!is_no_history && !is_debug && !s_trim.empty()) {
                            // DEBUG
                            main_obj->Debug_S_Str << "c";
                            main_obj->History.History_Put(s_trim);
                        }
                        // DEBUG
                        main_obj->Debug_S_Str << "d";
                        Cli_Input_Item input_item(CLI_INPUT_ITEM_TYPE_STR, s_trim);
                        main_obj->Cli_Output.Output_Str(s_trim);

                        main_obj->Script_Command_Str = "";
                        main_obj->Script_Label_Str = "";
                        main_obj->Script_Thread_FileName = "";
                        main_obj->Script_Thread_Is_No_History = false;

                        main_obj->Cli_Command_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                        while (main_obj->Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                            // DEBUG
                            main_obj->Debug_S_Str << "e";
                            main_obj->Cli_Input.Input_sleep(1);
                        }

                        if (main_obj->Script_Command_Str.length() > 0) {
                            // DEBUG
                            main_obj->Debug_S_Str << "f";
                            main_obj->Execute_Script_Command(is_debug, debug_res);
                            main_obj->Script_Command_Str = "";
                        }

                        //@Warning: Command "check goto <label>" - special case: is moves file position
                        if (main_obj->Script_Label_Str.length() > 0) {
                            // DEBUG
                            main_obj->Debug_S_Str << "g";
                            string label = main_obj->Script_Label_Str;
                            main_obj->Script_Label_Str = "";
                            bool label_found = main_obj->Execute_Command_check_goto_label(inputFile, label);
                            if (!label_found) {
                                // DEBUG
                                main_obj->Debug_S_Str << "h";
                                main_obj->Cli_Output.Output_NewLine();
                                main_obj->Cli_Output.Output_Str("ERROR: label \"" + label + "\" - not found, script stopped");
                                main_obj->Cli_Output.Output_NewLine();
                                main_obj->Cmd_Script_Stop = true; // Stop - label not found
                            }
                        }

                        if (main_obj->Script_Thread_FileName.length() > 0) {
                            // DEBUG
                            main_obj->Debug_S_Str << "j";
                            string nested_script_filename = main_obj->Script_Thread_FileName;
                            bool nested_script_is_no_history = main_obj->Script_Thread_Is_No_History;

                            main_obj->Script_Thread_FileName = "";
                            main_obj->Script_Thread_Is_No_History = false;

                            Execute_Script(main_obj, nested_script_filename, nested_script_is_no_history);
                        }

                    }
                } else {
                    // DEBUG
                    main_obj->Debug_S_Str << "A";
                    main_obj->Cmd_Script_Stop = true; // Stop By Ctrl+C
                }
            } while (!inputFile.eof()
                    //&& s != null
                    && !main_obj->Cmd_Script_Stop && !main_obj->Cmd_Quit);

            inputFile.close();

            if (main_obj->Cli_Input.Is_Ctrl_C_Pressed_Get()) {
                main_obj->Cli_Output.Output_Str(main_obj->Str_Rem + " Do script " + filename + " - Stopped by Ctrl+C");
                main_obj->Cli_Input.Is_Ctrl_C_Pressed_Clear();
            } else {
                main_obj->Cli_Output.Output_Str(main_obj->Str_Rem + " Do script " + filename + " - " + (main_obj->Cmd_Script_Stop ? "Stopped" : "End"));
                if (main_obj->Cmd_Script_Stop) {
                    main_obj->Cmd_Script_Stop = false;
                }
            }
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_Str(main_obj->Cli_Input.Invitation_Full_Get());
            main_obj->Cli_Input.Input_Str_Set_Empty();
        } else {
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_Str("File \"" + filename + "\" - not found");
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_NewLine();
            main_obj->Cli_Output.Output_Str(main_obj->Cli_Input.Invitation_Full_Get());
            main_obj->Cli_Input.Input_Str_Set_Empty();

            main_obj->Cli_Input.Input_sleep(1);
        }

    }

    BOOL DirectoryExists(LPCTSTR szPath) {
        DWORD dwAttrib = GetFileAttributes(szPath);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
                (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    Cli_Module_Base_Script(Cli_History &history, Cli_Input_win32api &cli_input, Cli_Output_win32api &cli_output,
            string str_rem, bool &cmd_script_stop, bool &cmd_quit, int script_buf_size,
            Cli_CMD_Processor &cli_command_processor,
            string &script_command_str, string &script_label_str, string &script_dir_str,
            Str_Filter_Abstract &str_filter) : Cli_Module("Base Script"),
    History(history), Cli_Input(cli_input), Cli_Output(cli_output),
    Str_Rem(str_rem), Cmd_Script_Stop(cmd_script_stop), Cmd_Quit(cmd_quit), Script_Buf_Size(script_buf_size),
    Cli_Command_Processor(cli_command_processor),
    Script_Command_Str(script_command_str), Script_Label_Str(script_label_str), Script_Dir_Str(script_dir_str),
    Str_Filter(str_filter),
    Script_Thread(0), Script_Thread_ID(0) {

        Version = "0.04";

        Script_Buf = new char[Script_Buf_Size];

        Script_Thread_Is_No_History = false;

        string s = "./" + Script_Dir_Str + "/";
        if (!DirectoryExists(s.c_str())) {
            //Directory.CreateDirectory(s.c_str());
            CreateDirectory(s.c_str(), NULL);
        }

        {
            // do script stop // @Attention: Must be before do script "file"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_stop);
            cmd->Text_Set("do script stop");
            cmd->Help_Set("stop execute script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "stop execute script"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script);
            cmd->Text_Set("do script \"<file>\"");
            cmd->Help_Set("execute script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }
        {
            // do script "<file>" no history
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_do_script_no_history);
            cmd->Text_Set("do script \"<file>\" no history");
            cmd->Help_Set("execute script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("do", "execute"));
            cmd->Item_Add(new Cmd_Item_Word("script", "execute script"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "not save to history"));
            Cmd_Add(cmd);
        }
        {
            // save history as script "<file>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_save_history_as_script);
            cmd->Text_Set("save history as script \"<file>\"");
            cmd->Help_Set("save history as script to file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("save", "save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "save history"));
            cmd->Item_Add(new Cmd_Item_Word("as", "save history as"));
            cmd->Item_Add(new Cmd_Item_Word("script", "save history as script to file"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file>\"", "script filename"));
            Cmd_Add(cmd);
        }

        Script_Thread = CreateThread(
                NULL, // default security attributes
                0, // use default stack size
                Script_Thread_Func, // thread function name
                this, // argument to thread function
                0, // use default creation flags
                &Script_Thread_ID);
    }

    virtual ~Cli_Module_Base_Script() {
        delete[] Script_Buf;
        Cli_Input.Input_Restore();
    }

    bool script_filename_check(string s) {
        if (s.length() == 0) return false; // Failed
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') continue; // Ok
            if (c >= 'A' && c <= 'Z') continue; // Ok
            if (c >= '0' && c <= '9') continue; // Ok
            if (c == '_') continue; // Ok
            return false; // Failed
        }
        return true; // Ok
    }

    bool save_history_as_script(string cmd_filename) {

        bool res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        string filename = "./" + Script_Dir_Str + "/" + cmd_filename;
        FILE *h = fopen(filename.c_str(), "wt");
        if (h) {
            for (int i = 0; i < History.History_Size_Get() - 1; i++) // @Attention : Last cmd not saved!
                fprintf(h, "%s\n", History.History_Item_Get(i).c_str());
            fclose(h);
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Script saved from history as " + filename);
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not open file " + filename + " for write");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool Execute_Command_check_goto_label(ifstream &inputFile, string label_str) {
        bool stop = false;
        bool found = false;
        inputFile.seekg(0, std::ios::beg);
        do {
            inputFile.getline(Script_Buf, Script_Buf_Size);
            string s = Script_Buf;

            if (!inputFile.eof()) {
                string kw_check = "check";
                char *kw_check_ptr = strstr(s.c_str(), kw_check.c_str());
                if (kw_check_ptr >= 0) {
                    string kw_label = "label";
                    char *kw_label_ptr = strstr(kw_check_ptr, kw_label.c_str());
                    if (kw_label_ptr != 0) {
                        char *label_str_prt = strstr(kw_label_ptr, label_str.c_str());
                        if (label_str_prt != 0) {
                            found = true;
                            stop = true; // Ok - Label Found
                        }
                    }
                }
            } else {
                stop = true; // Failed - Label Not Found
            }
        } while (!stop);

        return found;
    }

    bool Execute_Command_check_goto_label(FILE *h, string &label_str) {
        bool stop = false;
        bool found = false;
        char *s;
        fseek(h, 0, SEEK_SET);
        do {
            s = fgets(Script_Buf, Script_Buf_Size, h);
            if (s) {
                char *s1 = strstr(s, "check");
                if (s1) {
                    char *s2 = strstr(s1, "label");
                    if (s2) {
                        char *s3 = strstr(s2, label_str.c_str());
                        if (s3) {
                            found = true;
                            stop = true; // Ok - Label Found
                        }
                    }
                }
            } else {
                stop = true; // Failed - Label Not Found
            }
        } while (!stop);
        return found;
    }

    void Execute_Script_Command(bool is_debug, bool &debug_res) {
        string Script_Command_Str_Trim1 = Str_Trim(Script_Command_Str);
        Script_Command_Str = "";
        bool is_commas_found = false;
        if (Script_Command_Str_Trim1.length() >= 2
                && Script_Command_Str_Trim1[0] == '\"'
                && Script_Command_Str_Trim1[Script_Command_Str_Trim1.length() - 1] == '\"') {
            is_commas_found = true;
        }
        if (Script_Command_Str_Trim1.length() >= 2
                && Script_Command_Str_Trim1[0] == '\''
                && Script_Command_Str_Trim1[Script_Command_Str_Trim1.length() - 1] == '\'') {
            is_commas_found = true;
        }
        string Script_Command_Str_Trim2;
        if (is_commas_found) {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1.substr(1, Script_Command_Str_Trim1.length() - 2);
        } else {
            Script_Command_Str_Trim2 = Script_Command_Str_Trim1;
        }
        Cli_Input_Item input_item2(CLI_INPUT_ITEM_TYPE_STR, Script_Command_Str_Trim2);
        Cli_Command_Processor.Process_Input_Item(input_item2, is_debug, debug_res);
    }

    bool do_script(string cmd_filename, bool is_no_history) {
        bool res_filename_check = script_filename_check(cmd_filename);
        if (!res_filename_check) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: can not process file " + cmd_filename + " - incorrect script file name");
            Cli_Output.Output_NewLine();
            return true;
        }

        string filename = "./" + Script_Dir_Str + "/" + cmd_filename;

        Cli_Input.Is_Ctrl_C_Pressed_Clear(); // Before starting script - clear stop flag

        Cmd_Script_Stop = false;
        Script_Thread_FileName = filename;
        Script_Thread_Is_No_History = is_no_history;
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        Level_Description level;
        string parameter;
        if (Levels.size() > 0) {
            level = Levels.back();
            parameter = level.Parameter;
        }
        switch (cmd_id) {
            case CMD_ID_save_history_as_script:
                if (is_debug) return true;
            {
                string filename = cmd->Items[4]->Value_Str;
                return save_history_as_script(filename);
            }
            case CMD_ID_do_script:
                if (is_debug) return true;
            {
                string filename = cmd->Items[2]->Value_Str;
                bool is_no_history = false;
                return do_script(filename, is_no_history);
            }
            case CMD_ID_do_script_no_history:
                if (is_debug) return true;
            {
                string filename = cmd->Items[2]->Value_Str;
                bool is_no_history = true;
                return do_script(filename, is_no_history);
            }
            case CMD_ID_do_script_stop:
                if (is_debug) return true;
            {
                Cmd_Script_Stop = true;
                return true;
            }
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }
};

#endif /* CLI_MODULE_BASE_SCRIPT_H */
