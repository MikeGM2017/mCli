/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_Form_QPlainTextEdit.h
 * Author: mike
 *
 * Created on May 4, 2021, 4:40 PM
 */

#ifndef _CLI_OUTPUT_FORM_QPLAINTEXTEDIT_H
#define _CLI_OUTPUT_FORM_QPLAINTEXTEDIT_H

#include "ui_Cli_Output_Form_QPlainTextEdit.h"

class Cli_Output_Form_QPlainTextEdit : public QWidget {
    Q_OBJECT
public:
    Cli_Output_Form_QPlainTextEdit();
    virtual ~Cli_Output_Form_QPlainTextEdit();
private:
    Ui::Cli_Output_Form_QPlainTextEdit widget;
};

#endif /* _CLI_OUTPUT_FORM_QPLAINTEXTEDIT_H */
