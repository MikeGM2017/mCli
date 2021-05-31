/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_QPlainTextEdit.h
 * Author: mike
 *
 * Created on May 12, 2021, 8:55 AM
 */

#ifndef CLI_QPLAINTEXTEDIT_H
#define CLI_QPLAINTEXTEDIT_H

#include <QtWidgets/QPlainTextEdit>

#include <Qt>
#include <QKeyEvent>

#include "Cli_Key_Processor_Abstract.h"

class Cli_QPlainTextEdit : public QPlainTextEdit {
protected:

    Cli_Key_Processor_Abstract *Key_Processor;

    virtual void keyPressEvent(QKeyEvent *e) {

        if (Key_Processor) {
            int key_code = e->key();

            bool is_ctrl = false;
            if (e->modifiers() & Qt::ControlModifier) {
                is_ctrl = true;
            }

            Key_Processor->On_Key_Pressed(key_code, is_ctrl);

        } else {
            QPlainTextEdit::keyPressEvent(e);
        }

    }

public:

    Cli_QPlainTextEdit(QWidget *parent = 0) : QPlainTextEdit(parent), Key_Processor(NULL) {
    }

    virtual ~Cli_QPlainTextEdit() {
    }

    virtual void Key_Processor_Set(Cli_Key_Processor_Abstract *output_processor) {
        Key_Processor = output_processor;
    }

    virtual void keyPressEvent_Force(QKeyEvent *e) { // @Attention: Useful variant
        keyPressEvent(e);
    }

};

#endif /* CLI_QPLAINTEXTEDIT_H */
