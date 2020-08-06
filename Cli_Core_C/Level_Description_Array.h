/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Level_Description_Array.h
 * Author: mike
 *
 * Created on August 4, 2020, 12:15 PM
 */

#ifndef LEVEL_DESCRIPTION_ARRAY_H
#define LEVEL_DESCRIPTION_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Level_Description.h"

#define LEVEL_DESCRIPTION_ARRAY_SIZE_DEF 32
    
    struct Level_Description_Array;

    typedef int ftLevel_Description_Array_Add(struct Level_Description_Array *levels, struct Level_Description *level);
    typedef struct Level_Description* ftLevel_Description_Array_Get(struct Level_Description_Array *levels);
    typedef int ftLevel_Description_Array_Pop(struct Level_Description_Array *levels);

    struct Level_Description_Array {
        struct Level_Description Items[LEVEL_DESCRIPTION_ARRAY_SIZE_DEF];
        int Size;
        ftLevel_Description_Array_Add *Add;
        ftLevel_Description_Array_Get *Get;
        ftLevel_Description_Array_Pop *Pop;
    };

    struct Level_Description_Array Level_Description_Array_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* LEVEL_DESCRIPTION_ARRAY_H */
