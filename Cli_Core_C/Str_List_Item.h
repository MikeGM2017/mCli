/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_List_Item.h
 * Author: mike
 *
 * Created on August 12, 2020, 9:06 AM
 */

#ifndef STR_LIST_ITEM_H
#define STR_LIST_ITEM_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <string.h>

#define STR_LIST_ITEM_TEXT_SIZE_DEF 32

    struct Str_List_Item {
        char Text[STR_LIST_ITEM_TEXT_SIZE_DEF];
    };
    
    struct Str_List_Item Str_List_Item_Init(struct Str_List_Item *str_item);
    
    void Str_List_Item_Text_Set(struct Str_List_Item *str_item, char *s);

#ifdef __cplusplus
}
#endif

#endif /* STR_LIST_ITEM_H */
