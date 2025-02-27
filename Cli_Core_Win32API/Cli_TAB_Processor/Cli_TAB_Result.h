/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Tab_Result.h
 * Author: mike
 *
 * Created on July 16, 2020, 4:48 PM
 */

#ifndef CLI_TAB_RESULT_H
#define CLI_TAB_RESULT_H

#include <string>
#include <vector>

using namespace std;

#include "Cli_Cmd.h"

class Cli_TAB_Result {
public:

    Cli_Cmd *cmd_ptr;
    string s_log;
    vector<string> s_add_list;
    vector<string> s_full_list;
    bool Is_Enter;
    bool is_space_after_add;

    Cli_TAB_Result() : cmd_ptr(NULL), Is_Enter(false), is_space_after_add(false) {
    }

};

#endif /* CLI_TAB_RESULT_H */
