/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_Item.h
 * Author: mike
 *
 * Created on June 2, 2020, 9:40 AM
 */

#ifndef CLI_INPUT_C_ITEM_H
#define CLI_INPUT_C_ITEM_H

#include <string.h>

#include "Cli_Input_Item_Type.h"

#define CLI_INPUT_C_ITEM_TEXT_SIZE 1024

struct Cli_Input_C_Item;

typedef void ftCli_Input_C_Item_Init(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type, char *text);
typedef enum Cli_Input_Item_Type ftCli_Input_C_Item_Type_Get(struct Cli_Input_C_Item *obj);
typedef void ftCli_Input_C_Item_Type_Set(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type);
typedef char *ftCli_Input_C_Item_Text_Get(struct Cli_Input_C_Item *obj);
typedef void ftCli_Input_C_Item_Text_Set(struct Cli_Input_C_Item *obj, char *text);

struct Cli_Input_C_Item {
    enum Cli_Input_Item_Type Type;
    char Text[CLI_INPUT_C_ITEM_TEXT_SIZE];
    
    ftCli_Input_C_Item_Init *Init;
    ftCli_Input_C_Item_Type_Get *Type_Get;
    ftCli_Input_C_Item_Type_Set *Type_Set;
    ftCli_Input_C_Item_Text_Get *Text_Get;
    ftCli_Input_C_Item_Text_Set *Text_Set;
};

void Cli_Input_C_Item_Init(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type, char *text);

enum Cli_Input_Item_Type Cli_Input_C_Item_Type_Get(struct Cli_Input_C_Item *obj);

void Cli_Input_C_Item_Type_Set(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type);

char *Cli_Input_C_Item_Text_Get(struct Cli_Input_C_Item *obj);

void Cli_Input_C_Item_Text_Set(struct Cli_Input_C_Item *obj, char *text);

#endif /* CLI_INPUT_C_ITEM_H */
