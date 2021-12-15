/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_file.h
 * Author: mike
 *
 * Created on September 14, 2021, 10:34 AM
 */

#ifndef CLI_INPUT_FILE_H
#define CLI_INPUT_FILE_H

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include <stdio.h>

#include "Cli_Input_Abstract.h"

class Cli_Input_file : public Cli_Input_Abstract {
protected:

    string File_Name;

    FILE *File_In;

public:

    Cli_Input_file(string filename, Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output),
    File_Name(filename), File_In(NULL) {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual bool Input_Clear();

    virtual Cli_Input_Item Input_Item_Get();

    virtual bool Input_sleep(int sleep_sec);

    virtual bool Input_kbhit();

    virtual void Input_Add(char c);

};

#endif /* CLI_INPUT_FILE_H */
