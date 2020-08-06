/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Core.h
 * Author: mike
 *
 * Created on June 5, 2020, 11:03 AM
 */

#ifndef CLI_CORE_H
#define CLI_CORE_H

#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Cmd_Token_Parser.h"

#include "Level_Description.h"

#include "Cmd_Item_Valid_Result_Func.h"

#include "TAB_Cmd.h"

class Cli_Core {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;

    vector<Level_Description> &Levels;
    Cmd_Token_Parser &Token_Parser;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    string Str_Rem;

public:

    Cli_Core(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            vector<Level_Description> &levels, Cmd_Token_Parser &parser,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            string str_rem) :
    User_Privilege(user_privilege), Modules(modules),
    Levels(levels), Token_Parser(parser),
    Cli_Input(cli_input), Cli_Output(cli_output),
    Str_Rem(str_rem) {
    }

    virtual ~Cli_Core() {
    }

    virtual string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() ? (s.size() - 1) : 0;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

};

#endif /* CLI_CORE_H */
