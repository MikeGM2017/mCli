/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Level_Description_Array.h"

static int Level_Description_Array_Add(struct Level_Description_Array *levels, struct Level_Description *level) {
    if (levels->Size < LEVEL_DESCRIPTION_ARRAY_SIZE_DEF) {
        levels->Items[levels->Size++] = (*level);
        return 1; // Ok
    }
    return 0; // Failed
}

static struct Level_Description* Level_Description_Array_Get(struct Level_Description_Array *levels) {
    return &levels->Items[levels->Size];
}

static int Level_Description_Array_Pop(struct Level_Description_Array *levels) {
    if (levels->Size > 0) {
        levels->Size--;
        return 1; // Ok
    }
    return 0; // Failed
}

struct Level_Description_Array Level_Description_Array_Init(void) {
    struct Level_Description_Array levels;
    memset(&levels, 0, sizeof (levels));
    levels.Add = Level_Description_Array_Add;
    levels.Get = Level_Description_Array_Get;
    levels.Pop = Level_Description_Array_Pop;
    return levels;
}
