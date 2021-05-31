/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Key_Processor_Abstract.h
 * Author: mike
 *
 * Created on May 18, 2021, 8:49 AM
 */

#ifndef CLI_KEY_PROCESSOR_ABSTRACT_H
#define CLI_KEY_PROCESSOR_ABSTRACT_H

#include "Cli_Output_Abstract.h"

class Cli_Key_Processor_Abstract {
protected:

    Cli_Output_Abstract &Cli_Output;

public:

    Cli_Key_Processor_Abstract(Cli_Output_Abstract &cli_output) : Cli_Output(cli_output) {
    }

    virtual ~Cli_Key_Processor_Abstract() {
    }

    virtual void On_Key_Pressed(int key_code, bool is_ctrl) = 0;

};

#endif /* CLI_KEY_PROCESSOR_ABSTRACT_H */
