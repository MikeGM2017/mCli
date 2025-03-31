/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Do_Command.h
 * Author: mike
 *
 * Created on September 12, 2024, 11:17 AM
 */

#ifndef DO_COMMAND_H
#define DO_COMMAND_H

#include "Do_Abstract.h"

#include "Cli_Module_Base_Script.h"

class Do_Command : public Do_Abstract {
protected:

    Cli_Module_Base_Script &Module_Script;

public:

    Do_Command(Cli_Module_Base_Script &module_script) : Module_Script(module_script) {
    }

    virtual void Do(string s = "") {
        bool is_debug;
        bool debug_res;
        Module_Script.Execute_Script_Command(is_debug = false, debug_res);
    }

};

#endif /* DO_COMMAND_H */
