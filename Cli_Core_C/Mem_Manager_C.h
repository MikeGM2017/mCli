/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mem_Manager_C.h
 * Author: mike
 *
 * Created on December 24, 2020, 10:50 AM
 */

#ifndef MEM_MANAGER_C_H
#define MEM_MANAGER_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Mem_Manager_Res.h"
    
    struct Mem_Manager_C;

    typedef enum Mem_Manager_Res ftMem_Manager_Alloc(struct Mem_Manager_C *obj, int size, char **p);
    typedef enum Mem_Manager_Res ftMem_Manager_Free(struct Mem_Manager_C *obj, char *p);

    struct Mem_Manager_C {
        ftMem_Manager_Alloc *Mem_Manager_Alloc;
        ftMem_Manager_Free *Mem_Manager_Free;
    };

#ifdef __cplusplus
}
#endif

#endif /* MEM_MANAGER_C_H */
