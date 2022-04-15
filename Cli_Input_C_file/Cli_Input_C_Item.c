/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_Item.h"

void Cli_Input_C_Item_Init(struct Cli_Input_C_Item *obj, enum Cli_Input_Item_Type type, char *text) {
    obj->Type = type;
    strncpy(obj->Text, text, CLI_INPUT_C_ITEM_TEXT_SIZE - 1);
    obj->Text[CLI_INPUT_C_ITEM_TEXT_SIZE - 1] = '\0';
}

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
    strncpy(obj->Text, text, CLI_INPUT_C_ITEM_TEXT_SIZE - 1);
    obj->Text[CLI_INPUT_C_ITEM_TEXT_SIZE - 1] = '\0';
}
