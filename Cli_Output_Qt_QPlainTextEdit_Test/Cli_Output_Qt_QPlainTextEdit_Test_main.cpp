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
#include "Cli_Key_Processor_Abstract.h"

class Cli_Output_Form_QPlainTextEdit_Access : public Cli_Output_Form_QPlainTextEdit {
public:

    Cli_Output_Form_QPlainTextEdit_Access() {
    }

    virtual ~Cli_Output_Form_QPlainTextEdit_Access() {
    }

    Ui::Cli_Output_Form_QPlainTextEdit& widget_Get() {
        return widget;
    }

};

class Cli_Output_Test_Key_Processor : public Cli_Key_Processor_Abstract {
protected:

    int State;

    void Test_State_0() {
        Cli_Output.Output_Clear();
        Cli_Output.Output_Char('X');
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(" - Ok");
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("End");
        Cli_Output.Output_Return();
    }

    void Test_State_1() {
        bool res_clear;
        res_clear = Cli_Output.Output_Clear();
        if (res_clear) {
            Cli_Output.Output_Str("Cleared");
        } else {
            Cli_Output.Output_Str("Not Cleared");
        }
    }

    void Test_State_2() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Finished");
        Cli_Output.Output_NewLine();
    }

    void Test_State_3() {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Exit");
        Cli_Output.Output_NewLine();
        exit(0);
    }

public:

    Cli_Output_Test_Key_Processor(Cli_Output_Abstract &cli_output) : Cli_Key_Processor_Abstract(cli_output), State(0) {
    }

    virtual ~Cli_Output_Test_Key_Processor() {
    }

    virtual void On_Key_Pressed(int key_code, bool is_ctrl) {
        switch (State) {
            case 0:
                Test_State_0();
                State = 1;
                break;
            case 1:
                Test_State_1();
                State = 2;
                break;
            case 2:
                Test_State_2();
                State = 3;
                break;
            case 3:
                Test_State_3();
                State = 0;
                break;
        }
    }

};

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    Cli_Output_Form_QPlainTextEdit_Access Cli_Output_Form;

    Ui::Cli_Output_Form_QPlainTextEdit &widget = Cli_Output_Form.widget_Get();
    Cli_QPlainTextEdit *cli_textEdit = widget.textEdit;

    Cli_Output_QPlainTextEdit Cli_Output(cli_textEdit);

    Cli_Output_Test_Key_Processor cli_Key_Processor(Cli_Output);

    cli_textEdit->Key_Processor_Set(&cli_Key_Processor);
    //cli_textEdit->setReadOnly(true); // @Attention: TextCursor movement not visible

    QKeyEvent e(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier); // @Attention: Useful variant
    cli_textEdit->keyPressEvent_Force(&e); // @Attention: Useful variant
    //bool is_ctrl;
    //cli_Key_Processor.On_Key_Pressed(Qt::Key_K, is_ctrl = false);

    Cli_Output_Form.setWindowTitle("Cli Output Test (QPlainTextEdit)");
    
    Cli_Output_Form.show();

    return app.exec();
}
