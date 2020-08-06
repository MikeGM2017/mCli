/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_Filter.h
 * Author: mike
 *
 * Created on August 6, 2020, 1:21 PM
 */

#ifndef STR_FILTER_H
#define STR_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct Str_Filter {
        char C_Single; // @Example: '.' or '?'
        char C_Multy; // @Example: '*'
    };

    int Str_Filter_Is_Match(struct Str_Filter *str_filter, char *filter, char *s);

    struct Str_Filter Str_Filter_Init(char c_single, char c_multy);

#ifdef __cplusplus
}
#endif

#endif /* STR_FILTER_H */
