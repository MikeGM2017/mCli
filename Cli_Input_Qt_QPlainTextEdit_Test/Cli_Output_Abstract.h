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

class Cli_Output_Abstract {
public:

    Cli_Output_Abstract() {
    }

    virtual ~Cli_Output_Abstract() {
    }
    
    virtual bool Output_Init() = 0;

    virtual bool Output_Close() = 0;

    virtual bool Output_Clear() = 0;

    virtual void Output_Char(QChar c) = 0;

    virtual void Output_Str(QString s) = 0;

    virtual void Output_NewLine() = 0;

    virtual void Output_Return() = 0;
    
    virtual QString Output_Text_Get() = 0;
    
    virtual int Output_TextCursor_Pos_Get() = 0;
    
    virtual void Caret_Pos_Set(int input_str_len, int input_str_pos) = 0;

};

#endif /* CLI_OUTPUT_ABSTRACT_H */
