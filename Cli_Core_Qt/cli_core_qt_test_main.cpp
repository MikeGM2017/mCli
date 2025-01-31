/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QApplication>

#include "Cli_Output_Form_QPlainTextEdit.h"
#include "Cli_Output_QPlainTextEdit.h"
//#include "Cli_Input_Test_Key_Processor.h"
#include "Cli_Core_Test_Key_Processor.h"
#include "Cli_Input_Qt.h"

#include <iostream>
#include <sstream>

using namespace std;

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
#include "Cli_Module_Base_Wait_Qt.h"
#include "Cli_Module_Base_Debug.h"

#include "Str_Filter.h"

#include "Cli_CMD_Processor.h"

#include "Cli_TAB_Processor.h"

#include "Cli_Module_Test_Tab_Min_Max.h"
#include "Cli_Module_Test_Terminal.h"

#include "Cli_Module_Check.h"
#include "Cli_Module_Vars.h"

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
                || s == "--h" || s == "--help" || s == "--?"
                || s == "/h" || s == "/help" || s == "/?") {
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

    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    map<string, string> Values_Map;

    // Cli_Input / Cli_Output - Beg
    //Cli_Output_printf Cli_Output;

    //Cli_Input_termios Cli_Input(Cli_Output);

    Cli_Output_Form_QPlainTextEdit Cli_Output_Form;

    //Cli_QPlainTextEdit *cli_PlainTextEdit = Cli_Output_Form.findChild<Cli_QPlainTextEdit *>();
    Cli_QPlainTextEdit *cli_PlainTextEdit = Cli_Output_Form.findChild<Cli_QPlainTextEdit *>("textEdit");

    Cli_Output_QPlainTextEdit Cli_Output_Qt(cli_PlainTextEdit);

    Cli_Output_ofstream Cli_Output_File(Arg_Log_Output_File_Name);
    Cli_Output_Abstract &Cli_Output = (Arg_Log_Output_File_Name.empty() ? (Cli_Output_Abstract &) Cli_Output_Qt : (Cli_Output_Abstract &) Cli_Output_File);

    bool Log_Wait_Enable = true;
    Cli_Input_Qt Cli_Input(Cli_Output, Log_Wait_Enable);

    string Chars_Not_Allowed_Str = "@`|";
    Cli_Input.Chars_Not_Allowed_Str_Set(Chars_Not_Allowed_Str);

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

    Cli_History History;

    bool Cmd_Exit = false;
    bool Cmd_Quit = false;

    //Cli_Input_Test_Key_Processor cli_Key_Processor(Cli_Input, Cli_Output);
    Cli_Core_Test_Key_Processor cli_Key_Processor(CMD_Processor, TAB_Processor, History, Cli_Input, Cli_Output, Cmd_Quit);

    if (cli_PlainTextEdit) {

        QTextDocument *doc = cli_PlainTextEdit->document();
        QFont font = doc->defaultFont();
        font.setFamily("Courier New");
        doc->setDefaultFont(font);

        cli_PlainTextEdit->Key_Processor_Set(&cli_Key_Processor);
    }
    // Cli_Input / Cli_Output - End

    // Modules Add - Begin

    Modules.Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));

    Modules.Add(new Cli_Module_Base_Quit(Cli_Input, Cli_Output, Cmd_Exit, Cmd_Quit));

    char C_Single = '?';
    char C_Multy = '*';
    Str_Filter str_filter(C_Single, C_Multy);
    Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
    Modules.Add(new Cli_Module_Base_Modules(Version, Modules, str_filter, Cli_Input, Cli_Output));

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

    bool Cmd_Wait_Stop = false;
    Modules.Add(new Cli_Module_Base_Wait_Qt(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Test_Tab_Min_Max());
    Modules.Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));

    Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

    Modules.Add((new Cli_Module_Check(Modules, Values_Map, str_filter, Cli_Output, Cmd_Script_Stop)));

    Modules.Add((new Cli_Module_Vars(Modules, Values_Map, str_filter, Cli_Output, C_Single, C_Multy)));

    // Modules Add - End

    //cli_textEdit->setReadOnly(true); // @Attention: TextCursor movement not visible

    //QKeyEvent e(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier); // @Attention: Useful variant
    //cli_PlainTextEdit->keyPressEvent_Force(&e); // @Attention: Useful variant
    //bool is_ctrl;
    //cli_Key_Processor.On_Key_Pressed(Qt::Key_K, is_ctrl = false);

    Cli_Output_Form.setWindowTitle("Cli Core Test (QPlainTextEdit)");

    //Cli_Output.Output_Str("Cli Input Qt QPlainTextEdit started\n");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("mCli: Cli Core Test "); // @Attention: Additional Space
    Cli_Output.Output_Str(" V "); // @Attention: Additional Space
    Cli_Output.Output_Str(Version.c_str());
    Cli_Output.Output_NewLine();
    Cli_Output.Output_NewLine();

    Cli_Input.Title_Set("Cli Core Test");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> "); // @Optional
    Cli_Input.Divider_L_Set("["); // @Optional
    Cli_Input.Divider_R_Set("]"); // @Optional
    Cli_Input.Input_Init();

    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());

    Cli_Output_Form.show();

    int res_app = app.exec();

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

    return res_app;
}
