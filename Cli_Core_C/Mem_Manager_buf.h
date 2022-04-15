/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mem_Manager_buf.h
 * Author: mike
 *
 * Created on December 24, 2020, 11:02 AM
 */

#ifndef MEM_MANAGER_BUF_H
#define MEM_MANAGER_BUF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Mem_Manager_C.h"

#include <stdio.h>

    struct Mem_Manager_buf {
        struct Mem_Manager_C Mem_Manager_Base;
        char *buf;
        int buf_size;
        int buf_pos;
    };

    struct Mem_Manager_buf Mem_Manager_buf_Init(char *buf, int buf_size);

#ifdef __cplusplus
}
#endif

#endif /* MEM_MANAGER_BUF_H */
