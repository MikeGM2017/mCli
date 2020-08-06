/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_Item.h"

enum Cli_Input_Item_Type Cli_Input_C_Item_Type_Get(struct Cli_Input_C_Item *obj) {
    return obj->Type;
}

void Cli_Input_C_Item_Type_Set(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type) {
    obj->Type = type;
}

char *Cli_Input_C_Item_Text_Get(struct Cli_Input_C_Item *obj) {
    return obj->Text;
}

void Cli_Input_C_Item_Text_Set(struct Cli_Input_C_Item *obj, char *text) {
    int len = CLI_INPUT_C_ITEM_TEXT_SIZE - 1;
    strncpy(obj->Text, text, len);
    obj->Text[len] = '\0';
}

void Cli_Input_C_Item_Init(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type, char *text) {
    obj->Type = type;
    int len = CLI_INPUT_C_ITEM_TEXT_SIZE - 1;
    strncpy(obj->Text, text, len);
    obj->Text[len] = '\0';

    obj->Init = Cli_Input_C_Item_Init;
    obj->Type_Get = Cli_Input_C_Item_Type_Get;
    obj->Type_Set = Cli_Input_C_Item_Type_Set;
    obj->Text_Get = Cli_Input_C_Item_Text_Get;
    obj->Text_Set = Cli_Input_C_Item_Text_Set;
}
