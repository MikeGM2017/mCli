/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TAB_Cmd.h
 * Author: mike
 *
 * Created on August 13, 2018, 2:46 PM
 */

#ifndef TAB_CMD_H
#define TAB_CMD_H

#include <string>

using namespace std;

#include "TAB_Cmd_ID.h"

class TAB_Cmd {
public:
    TAB_Cmd_ID ID;
    string Text;

    TAB_Cmd(TAB_Cmd_ID id, string text) : ID(id), Text(text) {

    }
};

#endif /* TAB_CMD_H */
