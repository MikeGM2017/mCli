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
#include "Cli_Input_Test_Key_Processor.h"
#include "Cli_Input_Qt.h"

#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    Cli_Output_Form_QPlainTextEdit Cli_Output_Form;

    //Cli_QPlainTextEdit *cli_PlainTextEdit = Cli_Output_Form.findChild<Cli_QPlainTextEdit *>();
    Cli_QPlainTextEdit *cli_PlainTextEdit = Cli_Output_Form.findChild<Cli_QPlainTextEdit *>("textEdit");

    Cli_Output_QPlainTextEdit Cli_Output(cli_PlainTextEdit);
    Cli_Input_Qt Cli_Input(Cli_Output);
    QString Chars_Not_Allowed_Str = "@`|";
    Cli_Input.Chars_Not_Allowed_Str_Set(Chars_Not_Allowed_Str);

    Cli_Input_Test_Key_Processor cli_Key_Processor(Cli_Input, Cli_Output);

    if (cli_PlainTextEdit) {
        cli_PlainTextEdit->Key_Processor_Set(&cli_Key_Processor);
    }
    //cli_textEdit->setReadOnly(true); // @Attention: TextCursor movement not visible

    //QKeyEvent e(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier); // @Attention: Useful variant
    //cli_PlainTextEdit->keyPressEvent_Force(&e); // @Attention: Useful variant
    //bool is_ctrl;
    //cli_Key_Processor.On_Key_Pressed(Qt::Key_K, is_ctrl = false);

    Cli_Output_Form.setWindowTitle("Cli Input Test (QPlainTextEdit)");

    Cli_Output.Output_Str("Cli Input Qt QPlainTextEdit started\n");
    Cli_Output.Output_NewLine();

    Cli_Input.Title_Set("cli demo");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());

    Cli_Output_Form.show();

    return app.exec();
}
