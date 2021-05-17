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

#include <sstream>
#include <iomanip>

using namespace std;

class Cli_QPlainTextEdit : public QPlainTextEdit {
protected:

    virtual void keyPressEvent(QKeyEvent *e) {
        int key = e->key();

        string key_text;

        bool Is_Ctrl = false;
        if (e->modifiers() & Qt::ControlModifier) {
            Is_Ctrl = true;
        }

        if (Is_Ctrl && key == Qt::Key_C) {
            key_text = "Ctrl+C";
        } else if (Is_Ctrl && key == Qt::Key_Z) {
            key_text = "Ctrl+Z";
        } else if (Is_Ctrl && key == Qt::Key_Backslash) {
            key_text = "Ctrl+BACKSLASH";

        } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            key_text = "ENTER";
        } else if (key == Qt::Key_Tab) {
            key_text = "TAB";
        } else if (key == Qt::Key_Up) {
            key_text = "UP";
        } else if (key == Qt::Key_Down) {
            key_text = "DOWN";
        } else if (key == Qt::Key_Left) {
            key_text = "LEFT";
        } else if (key == Qt::Key_Right) {
            key_text = "RIGHT";
        } else if (key == Qt::Key_Home) {
            key_text = "HOME";
        } else if (key == Qt::Key_End) {
            key_text = "END";
        } else if (key == Qt::Key_Right) {
            key_text = "DOWN";
        } else if (key == Qt::Key_Delete) {
            key_text = "DELETE";
        } else if (key == Qt::Key_Backspace) {
            key_text = "BACK";
        }

        stringstream s_str;
        s_str << " 0x" << hex << uppercase << setw(2) << key;
        if (key_text.length()) {
            s_str << " " << key_text;
        }
        this->appendPlainText(s_str.str().c_str()); // QPlainTextEdit
        //this->append(s_str.str().c_str()); // QTextEdit
    }

public:

    Cli_QPlainTextEdit(QWidget *parent = 0) : QPlainTextEdit(parent) {
    }

    virtual ~Cli_QPlainTextEdit() {
    }

};

#endif /* CLI_QPLAINTEXTEDIT_H */
