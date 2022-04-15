/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_file.h
 * Author: mike
 *
 * Created on December 14, 2021, 4:03 PM
 */

#ifndef CLI_INPUT_C_FILE_H
#define CLI_INPUT_C_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include <stdio.h>

#include "Cli_Input_C.h"

#define CLI_INTPUT_C_FILENAME_SIZE 4096

    struct Cli_Input_C_File {
        struct Cli_Input_C Cli_Input_Base;

        char File_Name[CLI_INTPUT_C_FILENAME_SIZE]; // @Attention: Cli_Input_C_File specific
        FILE *File_In; // @Attention: Cli_Input_C_File specific
    };

    struct Cli_Input_C_File Cli_Input_C_file(struct Cli_Output_C *cli_output, char *filename);

#ifdef __cplusplus
}
#endif

#endif /* CLI_INPUT_C_FILE_H */
