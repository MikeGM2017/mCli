/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_C_file.h
 * Author: mike
 *
 * Created on December 14, 2021, 2:44 PM
 */

#ifndef CLI_OUTPUT_C_FILE_H
#define CLI_OUTPUT_C_FILE_H

#include <stdio.h>

#include "Cli_Output_C.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLI_OUTPUT_C_FILENAME_SIZE 4096

    struct Cli_Output_C Cli_Output_C_file(char *filename);

#ifdef __cplusplus
}
#endif

#endif /* CLI_OUTPUT_C_FILE_H */
