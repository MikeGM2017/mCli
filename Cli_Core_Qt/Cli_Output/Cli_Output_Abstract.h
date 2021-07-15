/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_Abstract.h
 * Author: mike
 *
 * Created on May 24, 2021, 9:50 AM
 */

#ifndef CLI_OUTPUT_ABSTRACT_H
#define CLI_OUTPUT_ABSTRACT_H

#include <QString>

#include <string>

using namespace std;

class Cli_Output_Abstract {
public:

    Cli_Output_Abstract() {
    }

    virtual ~Cli_Output_Abstract() {
    }

    virtual bool Output_Init() = 0;

    virtual bool Output_Close() = 0;

    virtual bool Output_Clear() = 0;

    virtual void Output_Char_Qt(QChar c) = 0;

    virtual void Output_Str_Qt(QString s) = 0;

    virtual void Output_Str(string s) { // @Compat: string -> QString
        QString str_qt = s.c_str();
        Output_Str_Qt(str_qt);
    }

    virtual void Output_NewLine() = 0;

    virtual void Output_Return() = 0;

    virtual QString Output_Text_Get() = 0;

    virtual void Output_Text_Set(QString s) = 0;

    virtual int Output_TextCursor_Pos_Get() = 0;

    virtual void Caret_Pos_Set(int input_str_len, int input_str_pos) = 0;

};

#endif /* CLI_OUTPUT_ABSTRACT_H */
