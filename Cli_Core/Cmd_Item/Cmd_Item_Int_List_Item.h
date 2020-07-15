/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Int_List_Item.h
 * Author: mike
 *
 * Created on July 15, 2020, 10:03 AM
 */

#ifndef CMD_ITEM_INT_LIST_ITEM_H
#define CMD_ITEM_INT_LIST_ITEM_H

class Cmd_Item_Int_List_Item {
public:
    int Min;
    int Max;

    Cmd_Item_Int_List_Item() : Min(0), Max(0) {
    }

    Cmd_Item_Int_List_Item(int min, int max) : Min(min), Max(max) {
    }

};

#endif /* CMD_ITEM_INT_LIST_ITEM_H */
