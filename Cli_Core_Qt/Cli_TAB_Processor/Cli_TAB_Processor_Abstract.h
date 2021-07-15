/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_TAB_Processor_Abstract.h
 * Author: mike
 *
 * Created on July 16, 2020, 4:33 PM
 */

#ifndef CLI_TAB_PROCESSOR_ABSTRACT_H
#define CLI_TAB_PROCESSOR_ABSTRACT_H

#include "Cli_Input_Item.h"

class Cli_TAB_Processor_Abstract {
public:

    Cli_TAB_Processor_Abstract() {
    }

    virtual ~Cli_TAB_Processor_Abstract() {
    }

    virtual void Process_Input_Item(Cli_Input_Item &input_item, bool &is_invitation_print) = 0;

};

#endif /* CLI_TAB_PROCESSOR_ABSTRACT_H */
