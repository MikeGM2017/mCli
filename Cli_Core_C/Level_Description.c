/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Level_Description.h"

struct Level_Description Level_Description_Init(void) {
    struct Level_Description level;
    memset(&level, 0, sizeof (level));
    return level;
}

char *Level_Description_Level_Get(struct Level_Description *level_description) {
    return level_description->Level;
}

void Level_Description_Level_Set(struct Level_Description *level_description, char *s) {
    if (!s) {
        level_description->Level[0] = '\0';
    } else {
        int len = LEVEL_DESCRIPTION_LEVEL_SIZE_DEF - 1;
        strncpy(level_description->Level, s, len);
        level_description->Level[len] = '\0';
    }
}

char *Level_Description_Parameter_Get(struct Level_Description *level_description) {
    return level_description->Parameter;
}

void Level_Description_Parameter_Set(struct Level_Description *level_description, char *s) {
    if (!s) {
        level_description->Parameter[0] = '\0';
    } else {
        int len = LEVEL_DESCRIPTION_PARAMETER_SIZE_DEF - 1;
        strncpy(level_description->Parameter, s, len);
        level_description->Parameter[len] = '\0';
    }
}
