/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Qt.h
 * Author: mike
 *
 * Created on May 24, 2021, 12:53 PM
 */

#ifndef CLI_INPUT_QT_H
#define CLI_INPUT_QT_H

#include "Cli_Input_Abstract.h"

#include "Cli_Output_Abstract.h"

#include <Qt>
#include <QKeyEvent>
#include <QThread>

#include <sstream>

using namespace std;

class Cli_Input_Qt_Wait_Thread : public QThread {

    Q_OBJECT

protected:

    void run() {
        while (1) {
            QThread::sleep(1);
            if (Wait_Count >= 0) {
                emit Wait_Count_Changed_Signal(Wait_Count);
                Wait_Count--;
            }
        }
    }

    int Wait_Count;

public:

    Cli_Input_Qt_Wait_Thread() : Wait_Count(-1) {
    }

    ~Cli_Input_Qt_Wait_Thread() {
    }

    virtual void Wait_Count_Set(int v) {
        Wait_Count = v;
    }

public:
signals:
    void Wait_Count_Changed_Signal(int);

};

class Cli_Input_Qt : public QObject, public Cli_Input_Abstract {
    Q_OBJECT
protected:

    bool &Log_Wait_Enable;

    Cli_Input_Qt_Wait_Thread *Wait_Thread;

public:

    Cli_Input_Qt(Cli_Output_Abstract &cli_output, bool &log_wait_enable) :
    Cli_Input_Abstract(cli_output), Log_Wait_Enable(log_wait_enable), Wait_Thread(NULL) {
    }

    virtual ~Cli_Input_Qt() {
    }

    virtual void Wait_Count_Set(int v) {
        Wait_Count = v;
        if (Wait_Thread) {
            Wait_Thread->Wait_Count_Set(v);
        }
    }

    virtual Cli_Input_Qt_Wait_Thread *Wait_Thread_Get() {
        return Wait_Thread;
    }

    virtual Cli_Input_Item Input_Item_Get() { // Attention: Main Cli Input Method - Blocked
        Cli_Input_Item item(CLI_INPUT_ITEM_TYPE_NO, "NO");
        return item;
    }

    virtual bool Input_Init() {
        bool cli_output_init_res = Cli_Output.Output_Init();
        if (!cli_output_init_res) {
        }
        if (!Wait_Thread) {

            Wait_Thread = new Cli_Input_Qt_Wait_Thread();
            Wait_Thread->start(QThread::NormalPriority);

            QObject::connect(Wait_Thread_Get(), SIGNAL(Wait_Count_Changed_Signal(int)),
                    this, SLOT(Wait_Count_Changed_Slot(int)));

        }
        return true;
    }

    virtual bool Input_Restore() {
        bool cli_output_close_res = Cli_Output.Output_Close();
        if (Wait_Thread) {
            Wait_Thread->terminate();
            delete Wait_Thread;
            Wait_Thread = NULL;
        }
        if (!cli_output_close_res) {

        }
        return true;

    }

    virtual bool Input_sleep(int sleep_sec) {
        QThread::sleep(sleep_sec);
        return true;
    }

    virtual bool Input_kbhit() { // Attention: Not Blocked
        return false;
    }

    virtual bool Is_Char_Valid(string char_str) {
        if (!Chars_Not_Allowed_Str.empty()) {
            for (int i = 0; i < char_str.length(); i++) {
                char c = char_str[i];
                if (Chars_Not_Allowed_Str.find(c, 0) != string::npos) {
                    return false;
                }
            }
        }
        return true;
    }

    virtual void Input_Str_Modified_To_Output(string s_prev) {
        if (Is_Echo_Get()) {
            Input_Str_Pos_Set(Input_Str_Get().size());
            Cli_Output.Caret_Pos_Set(Input_Str.size(), Input_Str.size() - s_prev.size());
            Cli_Output.Output_Str(Input_Str);
            Cli_Output.Caret_Pos_Set(Input_Str.size(), Input_Str_Pos);
        }
    }

    virtual Cli_Input_Item Input_Add(string key_str, bool is_shift) {

        if (!Is_Char_Valid(key_str)) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_NO_ACTION, "");
        }

        if (Input_Str_Pos == Input_Str.size()) {
            if (Is_Echo_Get()) {
                //Cli_Output.Output_Char(c);
            }
            Input_Str += key_str;
            Input_Str_Pos += key_str.length();
        } else {
            string s_prev = Input_Str;
            string s1 = "";
            string s2 = "";
            if (Input_Str_Pos > 0)
                s1 = s_prev.substr(0, Input_Str_Pos);
            if (Input_Str_Pos < Input_Str.size())
                s2 = s_prev.substr(Input_Str_Pos, s_prev.size() - Input_Str_Pos);
            Input_Str = s1 + key_str + s2;
            Input_Str_Pos += key_str.length();
            //Input_Str_Modified_To_Output(s_prev);
        }
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_CHAR_ADD, "");
    }

    virtual void Input_Left() {
        if (Input_Str_Pos > 0) {
            Input_Str_Pos--;
            //Input_Str_To_Output();
        }
    }

    virtual void Input_Right() {
        if (Input_Str_Pos < Input_Str.size()) {
            Input_Str_Pos++;
            //Input_Str_To_Output();
        }
    }

    virtual void Input_Home() {
        Input_Str_Pos = 0;
        //Input_Str_To_Output();
    }

    virtual void Input_End() {
        Input_Str_Pos = Input_Str.size();
        //Input_Str_To_Output();
    }

    virtual Cli_Input_Item Input_Back() {
        if (!Input_Str.empty() && Input_Str_Pos > 0) {
            string s_prev = Input_Str;
            if (Input_Str_Pos == Input_Str.size()) {
                Input_Str = s_prev.substr(0, s_prev.size() - 1);
                Input_Str_Pos--;
            } else {
                string s1 = s_prev.substr(0, Input_Str_Pos - 1);
                string s2 = s_prev.substr(Input_Str_Pos, s_prev.size() - Input_Str_Pos);
                Input_Str = s1 + s2;
                Input_Str_Pos--;
            }
            //Input_Str_Modified_To_Output(s_prev);
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_BACK, "");
        }
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_NO_ACTION, "");
    }

    virtual Cli_Input_Item Input_Delete() {
        if (!Input_Str.empty() && Input_Str_Pos < Input_Str.size()) {
            string s_prev = Input_Str;
            string s1 = "";
            string s2 = "";
            if (Input_Str_Pos > 0)
                s1 = s_prev.substr(0, Input_Str_Pos);
            if (Input_Str_Pos < Input_Str.size())
                s2 = s_prev.substr(Input_Str_Pos + 1, s_prev.size() - Input_Str_Pos - 1);
            //Input_Str_Modified_To_Output(s_prev);
            Input_Str = s1 + s2;
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_DELETE, "");
        }
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_NO_ACTION, "");
    }

    virtual Cli_Input_Item On_Key_Pressed(int key_code, string key_str, bool is_ctrl, bool is_shift) { // Attention: Not Blocked

        if (key_code == Qt::Key_Control) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_CTRL, "NO");
        }
        if (key_code == Qt::Key_Shift) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_SHIFT, "NO");
        }

        if (is_ctrl && key_code == Qt::Key_C) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_CTRL_C, "");
        } else if (is_ctrl && key_code == Qt::Key_Z) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_CTRL_Z, "");
        } else if (is_ctrl && key_code == Qt::Key_Backslash) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH, "");
        } else if (key_code == Qt::Key_Enter || key_code == Qt::Key_Return) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_STR, Input_Str_Get());
        } else if (key_code == Qt::Key_Tab) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_TAB, Input_Str_Get());
        } else if (key_code == Qt::Key_Up) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_UP, Input_Str_Get());
        } else if (key_code == Qt::Key_Down) {
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_DOWN, Input_Str_Get());
        } else if (key_code == Qt::Key_Left) {
            Input_Left();
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_LEFT, "");
        } else if (key_code == Qt::Key_Right) {
            Input_Right();
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_RIGHT, "");
        } else if (key_code == Qt::Key_Home) {
            Input_Home();
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_HOME, "");
        } else if (key_code == Qt::Key_End) {
            Input_End();
            return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_END, "");
        } else if (key_code == Qt::Key_Backspace) {
            return Input_Back();
        } else if (key_code == Qt::Key_Delete) {
            return Input_Delete();
        } else {
            return Input_Add(key_str, is_shift);
        }

        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_NO, "NO");
    }

public slots:
    // To communicate with Gui Thread
    // we need to emit a signal

    void Wait_Count_Changed_Slot(int v) {
        if (v > 0) {
            stringstream s_str;
            s_str << v;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Wait " + s_str.str());
        } else {
            Input_Str_Set_Empty();
            Input_Mode_Set(INPUT_MODE_NORMAL);
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(Invitation_Full_Get());
        }
        Wait_Count = v; // @Warning: Do Not Use Wait_Count_Set(v) - Cycled Settings -> Endless Wait Loop!
    }

};

#endif /* CLI_INPUT_QT_H */
