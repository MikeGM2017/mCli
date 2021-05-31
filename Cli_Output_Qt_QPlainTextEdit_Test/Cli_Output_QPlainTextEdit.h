/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_Qt_QPlainTextEdit.h
 * Author: mike
 *
 * Created on May 18, 2021, 1:44 PM
 */

#ifndef CLI_OUTPUT_QPLAINTEXTEDIT_H
#define CLI_OUTPUT_QPLAINTEXTEDIT_H

#include "Cli_Output_Abstract.h"

#include <QPlainTextEdit>

class Cli_Output_QPlainTextEdit : public Cli_Output_Abstract {
protected:

    QPlainTextEdit *textEdit;

public:

    Cli_Output_QPlainTextEdit(QPlainTextEdit *text_edit) : textEdit(text_edit) {
    }

    virtual ~Cli_Output_QPlainTextEdit() {
    }

    virtual bool Output_Clear() {
        if (textEdit) {
            textEdit->setPlainText("");
            return true;
        }
        return false;
    }

    virtual void Output_Char(QChar c) {
        Output_Str(c);
    }

    virtual void Output_Str(QString s) {
        if (textEdit) {
            QString s1 = textEdit->toPlainText();
            int s_len = s1.length();
            int s_pos = s_len - 1;
            while (s_pos >= 0 && s1[s_pos] == 0x10) s_pos--;
            if (s_pos >= 0) {
                QString s2 = s1.left(s_pos);
                QString s3 = s;
                QString s4 = s2 + s3;
                textEdit->setPlainText(s4);
            } else {
                textEdit->appendPlainText(s);
            }
            textEdit->moveCursor(QTextCursor::End);
        }
    }

    virtual void Output_NewLine() {
        if (textEdit) {
            textEdit->appendPlainText("\n");
        }
    }

    virtual void Output_Return() {
        if (textEdit) {
            QTextCursor text_cursor = textEdit->textCursor();
            int pos = text_cursor.position();
            QString s1 = textEdit->toPlainText();
            int s_len = s1.length();
            int s_pos = s_len - 1;
            while (s_pos >= 0 && s1[s_pos] == 0xA) {
                s_pos--;
                pos--;
            }
            while (s_pos >= 0 && s1[s_pos] != 0xA) {
                s_pos--;
                pos--;
            }
            if (pos >= 0) {
                text_cursor.setPosition(pos);
                textEdit->setTextCursor(text_cursor);
            }
        }
    }

};

#endif /* CLI_OUTPUT_QPLAINTEXTEDIT_H */
