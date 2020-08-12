/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Str_List_Item.h"

struct Str_List_Item Str_List_Item_Init(struct Str_List_Item *str_item) {
    memset(str_item, 0, sizeof (struct Str_List_Item));
}

void Str_List_Item_Text_Set(struct Str_List_Item *str_item, char *s) {
    int len = STR_LIST_ITEM_TEXT_SIZE_DEF - 1;
    strncpy(str_item->Text, s, len);
    str_item->Text[len] = '\0';
}
