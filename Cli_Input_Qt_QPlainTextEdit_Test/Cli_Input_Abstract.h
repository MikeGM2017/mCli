/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Abstract.h
 * Author: mike
 *
 * Created on June 2, 2020, 9:35 AM
 */

#ifndef CLI_INPUT_ABSTRACT_H
#define CLI_INPUT_ABSTRACT_H

#include <QString>
#include <QTextStream>

#include <iomanip>

using namespace std;

#include <ctype.h>

#include "Cli_Input_Item.h"

#include "Cli_Output_Abstract.h"

#include "Input_Mode_Type.h"

class Cli_Input_Abstract : public QObject {
    Q_OBJECT
protected:

    QString Title;
    QString User;
    QString Level;
    QString Invitation;
    QString Divider_L;
    QString Divider_R;
    QString Input_Str;

    Cli_Output_Abstract &Cli_Output;

    bool Is_Echo;
    int Input_Str_Pos;

    Input_Mode_Type Input_Mode;

    int Wait_Count;

    QString Chars_Not_Allowed_Str;

public:

    Cli_Input_Abstract(Cli_Output_Abstract &cli_output) : Invitation("> "), Divider_L("["), Divider_R("]"),
    Cli_Output(cli_output), Is_Echo(true), Input_Str_Pos(0), Input_Mode(INPUT_MODE_NORMAL), Wait_Count(-1) {
    }

    virtual ~Cli_Input_Abstract() {
    }

    virtual QString Title_Get() {
        return Title;
    }

    virtual void Title_Set(QString title) {
        Title = title;
    }

    virtual QString User_Get() {
        return User;
    }

    virtual void User_Set(QString user) {
        User = user;
    }

    virtual QString Level_Get() {
        return Level;
    }

    virtual void Level_Set(QString level) {
        Level = level;
    }

    virtual QString Invitation_Get() {
        return Invitation;
    }

    virtual void Invitation_Set(QString invitation) {
        Invitation = invitation;
    }

    virtual QString Divider_L_Get() {
        return Divider_L;
    }

    virtual void Divider_L_Set(QString divider_l) {
        Divider_L = divider_l;
    }

    virtual QString Divider_R_Get() {
        return Divider_R;
    }

    virtual void Divider_R_Set(QString divider_r) {
        Divider_R = divider_r;
    }

    virtual QString Invitation_Full_Get() { // Attention: Should be used for print cli invitation
        QString s;
        if (!Title.isEmpty()) {
            s += Divider_L + Title + Divider_R;
        }
        if (!User.isEmpty()) {
            s += Divider_L + User + Divider_R;
        }
        if (!Level.isEmpty()) {
            s += Divider_L + Level + Divider_R;
        }
        if (!Invitation.isEmpty()) {
            s += Invitation;
        }
        return s;
    }

    virtual int Input_Str_Pos_Get() {
        return Input_Str_Pos;
    }

    virtual QString Input_Str_Get() {
        return Input_Str;
    }

    virtual void Input_Str_Set(QString s) {
        Input_Str = s;
    }

    virtual void Input_Str_Set_Empty() {
        Input_Str_Pos = 0;
        Input_Str.clear();
    }

    virtual Input_Mode_Type Input_Mode_Get() {
        return Input_Mode;
    }

    virtual void Input_Mode_Set(Input_Mode_Type mode) {
        Input_Mode = mode;
    }

    virtual int Wait_Count_Get() {
        return Wait_Count;
    }

    virtual void Wait_Count_Set(int v) {
        Wait_Count = v;
    }

    virtual void Chars_Not_Allowed_Str_Set(QString s) {
        Chars_Not_Allowed_Str = s;
    }

    virtual QString Chars_Not_Allowed_Str_Get() {
        return Chars_Not_Allowed_Str;
    }

    virtual bool Input_Init() {
        return Cli_Output.Output_Init();
    }

    virtual bool Input_Restore() {
        return Cli_Output.Output_Close();
    }

    virtual bool Input_Clear() {
        return Cli_Output.Output_Clear();
    }

    virtual bool Is_Echo_Get() {
        return Is_Echo;
    }

    virtual void Is_Echo_On() {
        Is_Echo = true;
    }

    virtual void Is_Echo_Off() {
        Is_Echo = false;
    }

    virtual void Input_Str_To_Output() {
        if (Is_Echo_Get()) {
            Cli_Output.Output_Return();
            Cli_Output.Output_Str(Invitation_Full_Get());
            if (Input_Str_Pos > 0) {
                Cli_Output.Output_Str(Input_Str.mid(0, Input_Str_Pos));
            }
        }
    }

    virtual void Input_Str_Modified_To_Output(QString s_prev) {
        if (Is_Echo_Get()) {
            QTextStream s_str;
            //s_str << setw(s_prev.size()) << " ";
            s_str << QString(s_prev.size(), ' ');

            Cli_Output.Output_Return();
            Cli_Output.Output_Str(Invitation_Full_Get());
            //Cli_Output.Output_Str(s_str.str());
            Cli_Output.Output_Str(s_str.readAll());

            Cli_Output.Output_Return();
            Cli_Output.Output_Str(Invitation_Full_Get());
            Cli_Output.Output_Str(Input_Str);

            Cli_Output.Output_Return();
            Cli_Output.Output_Str(Invitation_Full_Get());
            if (Input_Str_Pos > 0) {
                Cli_Output.Output_Str(Input_Str.mid(0, Input_Str_Pos));
            }
        }
    }

    virtual void Input_Add(char c, bool is_shift) {
        if (Input_Str_Pos == Input_Str.size()) {
            if (Is_Echo_Get()) {
                Cli_Output.Output_Char(c);
            }
            Input_Str += c;
            Input_Str_Pos++;
        } else {
            QString s_prev = Input_Str;

            QTextStream s_str;
            s_str << Input_Str.mid(0, Input_Str_Pos)
                    << c
                    << Input_Str.mid(Input_Str_Pos, Input_Str.size() - Input_Str_Pos);

            //Input_Str = s_str.str();
            Input_Str = s_str.readAll();
            Input_Str_Pos++;

            Input_Str_Modified_To_Output(s_prev);
        }
    }

    virtual Cli_Input_Item Input_Back() {
        if (!Input_Str.isEmpty() && Input_Str_Pos > 0) {
            QString s_prev = Input_Str;
            if (Input_Str_Pos == Input_Str.size()) {
                Input_Str = s_prev.mid(0, s_prev.size() - 1);
                Input_Str_Pos--;
            } else {
                Input_Str = s_prev.mid(0, Input_Str_Pos - 1)
                        + s_prev.mid(Input_Str_Pos, s_prev.size() - Input_Str_Pos);
                Input_Str_Pos--;
            }
            Input_Str_Modified_To_Output(s_prev);
        }
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_BACK, "");
    }

    virtual Cli_Input_Item Input_Delete() {
        if (!Input_Str.isEmpty() && Input_Str_Pos < Input_Str.size()) {
            QString s_prev = Input_Str;
            Input_Str = s_prev.mid(0, Input_Str_Pos)
                    + s_prev.mid(Input_Str_Pos + 1, s_prev.size() - Input_Str_Pos - 1);
            Input_Str_Modified_To_Output(s_prev);
        }
        return Cli_Input_Item(CLI_INPUT_ITEM_TYPE_DELETE, "");
    }

    virtual void Input_Home() {
        Input_Str_Pos = 0;
        Input_Str_To_Output();
    }

    virtual void Input_End() {
        Input_Str_Pos = Input_Str.size();
        Input_Str_To_Output();
    }

    virtual void Input_Left() {
        if (Input_Str_Pos > 0) {
            Input_Str_Pos--;
            Input_Str_To_Output();
        }
    }

    virtual void Input_Right() {
        if (Input_Str_Pos < Input_Str.size()) {
            Input_Str_Pos++;
            Input_Str_To_Output();
        }
    }

    virtual Cli_Input_Item Input_Item_Get() = 0; // Attention: Main Cli Input Method - Blocked

    virtual bool Input_sleep(int sleep_sec) = 0;

    virtual bool Input_kbhit() = 0; // Attention: Not Blocked

    virtual bool Is_Char_Valid(QString char_str) = 0;

    virtual Cli_Input_Item On_Key_Pressed(int key_code, QString key_str, bool is_ctrl, bool is_shift) = 0; // Attention: Not Blocked

};

#endif /* CLI_INPUT_ABSTRACT_H */
