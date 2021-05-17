/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_Form_QTextEdit.h
 * Author: mike
 *
 * Created on May 4, 2021, 4:40 PM
 */

#ifndef _CLI_OUTPUT_FORM_QTEXTEDIT_H
#define _CLI_OUTPUT_FORM_QTEXTEDIT_H

#include "ui_Cli_Output_Form_QTextEdit.h"

class Cli_Output_Form_QTextEdit : public QWidget {
    Q_OBJECT
public:
    Cli_Output_Form_QTextEdit();
    virtual ~Cli_Output_Form_QTextEdit();
private:
    Ui::Cli_Output_Form_QTextEdit widget;
};

#endif /* _CLI_OUTPUT_FORM_QTEXTEDIT_H */
