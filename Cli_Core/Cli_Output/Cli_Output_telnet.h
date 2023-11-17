/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_telnet.h
 * Author: mike
 *
 * Created on May 22, 2023, 4:57 PM
 */

#ifndef CLI_OUTPUT_TELNET_H
#define CLI_OUTPUT_TELNET_H

#include <unistd.h>

#include <string>

using namespace std;

#include "Cli_Output_Abstract.h"

class Cli_Output_telnet : public Cli_Output_Abstract {
protected:

    int &Telnet_Sock;

public:

    Cli_Output_telnet(int &telnet_sock) :
    Telnet_Sock(telnet_sock) {
    }

    virtual bool Output_Init() {
        return true;
    }

    virtual bool Output_Close() {
        return true;
    }

    virtual bool Output_Clear() {
        return false; // can not clear
    }

    virtual void Output_NewLine() {
        if (Telnet_Sock >= 0) {
            write(Telnet_Sock, "\r\n", 2);
        }
    }

    virtual void Output_Char(char c) {
        if (Telnet_Sock >= 0) {
            write(Telnet_Sock, &c, 1);
        }
    }

    virtual void Output_Str(string s) {
        if (Telnet_Sock >= 0) {
            write(Telnet_Sock, s.c_str(), s.size());
        }
    }

    virtual void Output_Return() {
        if (Telnet_Sock >= 0) {
            write(Telnet_Sock, "\r", 1);
        }
    }

};

#endif /* CLI_OUTPUT_TELNET_H */
