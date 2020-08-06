/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Level_Description.h
 * Author: mike
 *
 * Created on August 4, 2020, 12:08 PM
 */

#ifndef LEVEL_DESCRIPTION_H
#define LEVEL_DESCRIPTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define LEVEL_DESCRIPTION_LEVEL_SIZE_DEF 32
#define LEVEL_DESCRIPTION_PARAMETER_SIZE_DEF 128

    struct Level_Description {
        char Level[LEVEL_DESCRIPTION_LEVEL_SIZE_DEF];
        char Parameter[LEVEL_DESCRIPTION_PARAMETER_SIZE_DEF];
    };

    struct Level_Description Level_Description_Init(void);

    char *Level_Description_Level_Get(struct Level_Description *level_description);

    void Level_Description_Level_Set(struct Level_Description *level_description, char *s);

    char *Level_Description_Parameter_Get(struct Level_Description *level_description);

    void Level_Description_Parameter_Set(struct Level_Description *level_description, char *s);

#ifdef __cplusplus
}
#endif

#endif /* LEVEL_DESCRIPTION_H */
