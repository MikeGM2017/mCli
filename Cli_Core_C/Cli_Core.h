/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Core.h
 * Author: mike
 *
 * Created on August 4, 2020, 3:45 PM
 */

#ifndef CLI_CORE_H
#define CLI_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct Cli_Core;

    typedef char *ftStr_Trim(char *s, char *s_trim, int s_trim_size);

    struct Cli_Core {
        ftStr_Trim *Str_Trim;
    };

    struct Cli_Core Cli_Core_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_CORE_H */
