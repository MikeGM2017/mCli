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

    virtual bool Output_Init() {
        return false;
    }

    virtual bool Output_Close() {
        return false;
    }

    virtual bool Output_Clear() {
        if (textEdit) {
            textEdit->setPlainText("");
            return true;
        }
        return false;
    }

    virtual void Output_Char(char c) {
        if (textEdit) {
            string s;
            s.append(1, c);
            Output_Str(s);
        }
    }

    virtual void Output_Str(string s) {
        if (textEdit) {
            string s1 = textEdit->toPlainText().toStdString();
            int s_len = s1.length();
            int s_pos = s_len;
            if (s_pos > 0 && s1[s_pos - 1] == 0x10) s_pos--;
            if (s_pos >= 0) {
                QTextCursor textCursor = textEdit->textCursor();
                if (s_pos < s_len) {
                    textCursor.setPosition(s_pos);
                }
                textCursor.setPosition(s_len, QTextCursor::KeepAnchor);
                textEdit->setTextCursor(textCursor);
                textEdit->insertPlainText(s.c_str());
            } else {
                textEdit->appendPlainText(s.c_str());
            }
            textEdit->moveCursor(QTextCursor::End);
        }
    }

    virtual void Output_NewLine() {
        if (textEdit) {
            textEdit->appendPlainText(""); //@Attention: appendPlainText(s) appends '\n'!
        }
    }

    virtual void Output_Return() {
        if (textEdit) {
            textEdit->moveCursor(QTextCursor::End);
            QTextCursor textCursor = textEdit->textCursor();
            int pos = textCursor.position();
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
                textCursor.setPosition(pos);
                //textCursor.setPosition(s_len, QTextCursor::KeepAnchor);
                textEdit->setTextCursor(textCursor);
            }
        }
    }

    virtual void Caret_Pos_Set(int input_str_len, int input_str_pos) {
        if (textEdit) {
            QTextCursor textCursor = textEdit->textCursor();
            int output_text_len = textEdit->toPlainText().length();
            int caret_pos = output_text_len - input_str_len + input_str_pos;
            if (caret_pos < 0) {
                caret_pos = 0;
            }
            textCursor.setPosition(caret_pos);
            textEdit->setTextCursor(textCursor);
        }
    }

};

#endif /* CLI_OUTPUT_QPLAINTEXTEDIT_H */
