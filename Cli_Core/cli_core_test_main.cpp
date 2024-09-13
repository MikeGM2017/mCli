/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_core_test_main.cpp
 * Author: mike
 *
 * Created on June 5, 2020, 10:03 AM
 */

#include <iostream>
#include <fstream>

using namespace std;

#include "Cli_Input_termios.h"
#include "Cli_Input_ifstream.h"

#include "Cli_Output_printf.h"
#include "Cli_Output_ofstream.h"

#include "Cli_Core.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Cli_Module_Base_Rem.h"
#include "Cli_Module_Base_Quit.h"
#include "Cli_Module_Base_Help.h"
#include "Cli_Module_Base_Modules.h"
#include "Cli_Module_Base_History.h"

#include "Cli_Module_Base_Log.h"
#include "Cli_Module_Base_Script.h"
#include "Cli_Module_Base_Wait.h"
#include "Cli_Module_Base_Debug.h"

#include "Str_Filter.h"

#include "Str_Get_Without_Commas.h"

#include "Cli_CMD_Processor.h"

#include "Cli_TAB_Processor.h"

#include "Cli_Module_Test_Tab_Min_Max.h"
#include "Cli_Module_Test_Terminal.h"

#include "Cli_Module_Check.h"
#include "Cli_Module_Vars.h"
#include "Cli_Module_Base_Level.h"
#include "Cli_Module_Lua.h"

#include "Do_Command.h"

const string Version = "0.04";

void Version_Print() {
    cout << "V" << Version << endl;
}

void Help_Print() {
    cout << "Program Cli Core Test V" << Version << endl;
    cout << "Use: cli_core_test [switches]" << endl;
    cout << "-h               - print this help;" << endl;
    cout << "-v               - print version;" << endl;
    cout << "-a               - print arguments;" << endl;
    cout << "-fscript <file>  - set input script file;" << endl;
    cout << "-flog <file>     - set output log file;" << endl;
    cout << "-ftablog <file>  - set output tab log file;" << endl;
    cout << "-fhistory <file> - set output history log file;" << endl;
}

int main(int argc, char *argv[]) {

    int error_code = 0; // Ok

    bool Arg_Help_Print = false;
    bool Arg_Version_Print = false;
    bool Arg_Arguments_Print = false;
    string Arg_Script_File_Name;
    string Arg_Log_Output_File_Name;
    string Arg_TAB_Log_Output_File_Name;
    string Arg_HISTORY_Log_Output_File_Name;

    for (int i = 1; i < argc; i++) {
        string s = argv[i];
        if (s == "-h" || s == "-help" || s == "-?"
                || s == "-h" || s == "-help" || s == "-?"
                || s == "-h" || s == "-help" || s == "-?") {
            Arg_Help_Print = true;
        } else if (s == "-v" || s == "--v"
                || s == "-version" || s == "--version") {
            Arg_Version_Print = true;
        } else if (s == "-a") {
            Arg_Arguments_Print = true;
        } else if (s == "-fscript") {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_Script_File_Name = argv[i];
            } else {
                cout << "ERROR: switch \"" << s << "\" without argument" << endl;
                exit(1); // Error
            }
        } else if (s == "-flog") {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_Log_Output_File_Name = argv[i];
            } else {
                cout << "ERROR: switch \"" << s << "\" without argument" << endl;
                exit(1); // Error
            }
        } else if (s == "-ftablog") {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_TAB_Log_Output_File_Name = argv[i];
            } else {
                cout << "ERROR: switch \"" << s << "\" without argument" << endl;
                exit(1); // Error
            }
        } else if (s == "-fhistory") {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_HISTORY_Log_Output_File_Name = argv[i];
            } else {
                cout << "ERROR: switch \"" << s << "\" without argument" << endl;
                exit(1); // Error
            }
        }
    }

    //if (argc == 1) {
    //    Arg_Help_Print = true;
    //}

    if (Arg_Version_Print) {
        Version_Print();
        exit(error_code); // Ok
    }

    if (Arg_Help_Print) {
        Help_Print();
        exit(error_code); // Ok
    }

    if (Arg_Arguments_Print) {
        cout << "Arguments:" << endl;
        cout << "         Arg_Script_File_Name:" << Arg_Script_File_Name << endl;
        cout << "     Arg_Log_Output_File_Name:" << Arg_Log_Output_File_Name << endl;
        cout << " Arg_TAB_Log_Output_File_Name:" << Arg_TAB_Log_Output_File_Name << endl;
    }

    map<string, string> Values_Map;

    //    Cli_Output_Abstract *Cli_Output_Printf_ptr = new Cli_Output_printf();
    //    Cli_Output_Abstract *Cli_Output_File_ptr = new Cli_Output_file(Arg_Log_Output_File_Name);
    //    Cli_Output_Abstract &Cli_Output = (Arg_Log_Output_File_Name.empty() ? *Cli_Output_Printf_ptr : *Cli_Output_File_ptr);

    Cli_Output_printf Cli_Output_Printf;
    Cli_Output_ofstream Cli_Output_File(Arg_Log_Output_File_Name);
    Cli_Output_Abstract &Cli_Output = (Arg_Log_Output_File_Name.empty() ? (Cli_Output_Abstract &) Cli_Output_Printf : (Cli_Output_Abstract &) Cli_Output_File);

    //    Cli_Input_Abstract *Cli_Input_Keyboard_ptr = new Cli_Input_termios(Cli_Output);
    //    Cli_Input_Abstract *Cli_Input_File_ptr = new Cli_Input_file(Arg_Script_File_Name, Cli_Output);
    //    Cli_Input_Abstract &Cli_Input = (Arg_Script_File_Name.empty() ? *Cli_Input_Keyboard_ptr : *Cli_Input_File_ptr);

    Cli_Input_termios Cli_Input_Keyboard(Cli_Output);
    Cli_Input_ifstream Cli_Input_File(Arg_Script_File_Name, Cli_Output);
    Cli_Input_Abstract &Cli_Input = (Arg_Script_File_Name.empty() ? (Cli_Input_Abstract &) Cli_Input_Keyboard : (Cli_Input_Abstract &) Cli_Input_File);

    vector<Level_Description> Levels;

    Cmd_Token_Parser Token_Parser;

    const string Str_Rem_DEF = "$";

    Cli_Cmd_Privilege_ID User_Privilege = CMD_PRIVILEGE_ROOT_DEF;
    Cli_Modules Modules;

    bool tab_log_is_active = !Arg_TAB_Log_Output_File_Name.empty();

    Cli_CMD_Processor CMD_Processor
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
    Cli_TAB_Processor TAB_Processor
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF, tab_log_is_active);
    Cli_Core Cli
            (User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);

    // Modules Add - Begin

    string level_root = "top level";

    Modules.Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));

    bool Cmd_Exit = false;
    bool Cmd_Quit = false;
    Modules.Add(new Cli_Module_Base_Quit(Cli_Input, Cli_Output, Cmd_Exit, Cmd_Quit));

    char C_Single = '?';
    char C_Multy = '*';
    Str_Filter str_filter(C_Single, C_Multy);
    Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
    Modules.Add(new Cli_Module_Base_Modules(Modules, str_filter, Cli_Input, Cli_Output));

    Cli_History History;
    Modules.Add(new Cli_Module_Base_History(History, Cli_Output));

    Modules.Add(new Cli_Module_Base_Log(Cli_Input));

    bool Cmd_Script_Stop = false;
    int Script_Buf_Size = 1024;
    string Script_Command_Str;
    string Script_Label_Str;
    string Script_Dir_Str = "./scripts";
    Cli_Module_Base_Script Module_Script(History, Cli_Input, Cli_Output,
            Str_Rem_DEF, Cmd_Script_Stop, Cmd_Quit, Script_Buf_Size,
            CMD_Processor, Script_Command_Str, Script_Label_Str, Script_Dir_Str);
    Modules.Add(&Module_Script);
    Do_Command Do_Command_Object(Module_Script);

    bool Log_Wait_Enable = true;
    bool Cmd_Wait_Stop = false;
    Modules.Add(new Cli_Module_Base_Wait(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Test_Tab_Min_Max());
    Modules.Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

    Str_Get_Without_Commas str_without_commas;

    Modules.Add((new Cli_Module_Check(Modules, Values_Map, str_filter, str_without_commas,
            Cli_Output, Cmd_Script_Stop, Script_Command_Str, Script_Label_Str,
            Do_Command_Object)));

    Modules.Add((new Cli_Module_Vars(Modules, Values_Map, str_filter, str_without_commas,
            Cli_Output, C_Single, C_Multy)));

    Modules.Add(new Cli_Module_Base_Level(Cli_Input, level_root));

    Modules.Add(new Cli_Module_Lua(Values_Map, str_filter, Cli_Input, Cli_Output));

    // Modules Add - End

    Cli_Input.Title_Set("Cli Core Test");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set(level_root);
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("mCli: Cli Core Test");
    Cli_Output.Output_Str(" V");
    Cli_Output.Output_Str(Version);
    Cli_Output.Output_NewLine();
    Cli_Output.Output_NewLine();

    bool stop = false;
    bool is_invitation_print = true;
    do {
        if (is_invitation_print) {
            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
        }
        is_invitation_print = true;
        Cli_Input_Item input_item = Cli_Input.Input_Item_Get();
        switch (input_item.Type_Get()) {
            case CLI_INPUT_ITEM_TYPE_STR:
            {
                bool is_no_history = false;
                bool is_debug = false;

                string s_trim = Cli.Str_Trim(input_item.Text_Get());

                if (!is_no_history && !is_debug && !s_trim.empty()) {
                    History.History_Put(s_trim);
                }

                bool debug_res = false;
                CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                Cli_Output.Output_NewLine();
            }
                break;
            case CLI_INPUT_ITEM_TYPE_TAB:
            {
                TAB_Processor.Process_Input_Item(input_item, is_invitation_print);
            }
                break;
            case CLI_INPUT_ITEM_TYPE_UP:
            {
                string s_prev = Cli_Input.Input_Str_Get();
                Cli_Input.Input_Str_Set(History.History_Up());
                Cli_Input.Input_Str_Modified_To_Output(s_prev);
                Cli_Input.Input_End();
                is_invitation_print = false;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_DOWN:
            {
                string s_prev = Cli_Input.Input_Str_Get();
                Cli_Input.Input_Str_Set(History.History_Down());
                Cli_Input.Input_Str_Modified_To_Output(s_prev);
                Cli_Input.Input_End();
                is_invitation_print = false;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_QUIT:
            {
                Cli_Output.Output_Str("Quit - Processed");
                Cli_Output.Output_NewLine();
                stop = true; // Quit
            }
                break;
        }

        if (Cmd_Exit) {
            Cli_Output.Output_Str("Exit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Exit
        }
        if (Cmd_Quit) {
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Quit
        }

    } while (!stop);

    if (tab_log_is_active) {
        fstream f_out;
        f_out.open(Arg_TAB_Log_Output_File_Name.c_str(), ios_base::out);
        if (f_out.is_open()) {
            int history_size = TAB_Processor.Log_Size_Get();
            for (int i = 0; i < history_size; i++) {
                string s = TAB_Processor.Log_Item_Get(i);
                f_out << s << endl;
            }
            f_out.close();
        } else {
            Cli_Output.Output_Str("ERROR: can not open file \"" + Arg_TAB_Log_Output_File_Name + "\" for write");
            Cli_Output.Output_NewLine();
        }
    }

    if (!Arg_HISTORY_Log_Output_File_Name.empty()) {
        fstream f_out;
        f_out.open(Arg_HISTORY_Log_Output_File_Name.c_str(), ios_base::out);
        if (f_out.is_open()) {
            int history_size = History.History_Size_Get();
            for (int i = 0; i < history_size; i++) {
                string s = History.History_Item_Get(i);
                f_out << s << endl;
            }
            f_out.close();
        } else {
            Cli_Output.Output_Str("ERROR: can not open file \"" + Arg_HISTORY_Log_Output_File_Name + "\" for write");
            Cli_Output.Output_NewLine();
        }
    }

    Cli_Input.Input_Restore();

    //    delete Cli_Output_Printf_ptr;
    //    delete Cli_Output_File_ptr;
    //    delete Cli_Input_Keyboard_ptr;
    //    delete Cli_Input_File_ptr;

    return error_code;
}
