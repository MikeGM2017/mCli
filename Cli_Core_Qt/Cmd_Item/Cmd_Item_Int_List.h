/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_Int_List.h
 * Author: mike
 *
 * Created on July 15, 2020, 9:59 AM
 */

#ifndef CMD_ITEM_INT_LIST_H
#define CMD_ITEM_INT_LIST_H

#include "Cmd_Item_Int_Range.h"

#include "Cmd_Item_Int_List_Item.h"

class Cmd_Item_Int_List : public Cmd_Item_Int_Range {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9')
            return true;
        if (pos > 0) {
            if (c == ',')
                return true;
            if (c == '-')
                return true;
        }
        return false;
    }

public:

    vector<Cmd_Item_Int_List_Item> Values_Int_List_Items;

    Cmd_Item_Int_List(int min, int max, string text, string help) : Cmd_Item_Int_Range(min, max, text, help) {
        Type = "Int_List";
    }

    virtual string Debug_Value_Get() {
        stringstream s_str;
        s_str << Min << "-" << Max;
        return s_str.str();
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;
        Values_Int_List_Items.clear();

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        int n = 0;
        int n_beg = 0;
        bool n_beg_Valid = false;
        bool prev_is_digit = false;
        bool prev_is_minus = false;
        for (int pos = 0; pos < s.size(); pos++) {
            char c = s[pos];
            if (c >= '0' && c <= '9') {
                n = n * 10 + Char_To_N(c);
                prev_is_digit = true;
                prev_is_minus = false;
                //n_beg_Valid = false;
            } else if (c == '-') {
                if (prev_is_digit) {
                    if (n < Min || n > Max) {
                        return CMD_ITEM_OUT_OF_RANGE;
                    }
                    n_beg = n;
                    n = 0;
                    prev_is_digit = false;
                    prev_is_minus = true;
                    n_beg_Valid = true;
                } else {
                    return CMD_ITEM_ERROR;
                }
            } else if (c == ',') {
                if (prev_is_minus) {
                    return CMD_ITEM_ERROR;
                }
                if (!prev_is_digit) {
                    return CMD_ITEM_ERROR;
                }
                // Повтор для последнего значения - Beg
                if (n_beg_Valid && prev_is_digit) {
                    if (n < Min || n > Max) {
                        return CMD_ITEM_OUT_OF_RANGE;
                    }
                    //if (n_beg <= n) { @Attention
                    if (n_beg < n) {
                        Values_Int_List_Items.push_back(Cmd_Item_Int_List_Item(n_beg, n));
                        n = 0;
                        prev_is_digit = false;
                        prev_is_minus = false;
                        n_beg_Valid = false;
                    } else {
                        return CMD_ITEM_OUT_OF_ORDER;
                    }
                } else if (prev_is_digit) {
                    if (n < Min || n > Max) {
                        return CMD_ITEM_OUT_OF_RANGE;
                    }
                    Values_Int_List_Items.push_back(Cmd_Item_Int_List_Item(n, n));
                    n = 0;
                    prev_is_digit = false;
                    prev_is_minus = false;
                    n_beg_Valid = false;
                }
                // Повтор для последнего значения - End

            }
        }
        // Последнее значение
        if (prev_is_minus) {
            return CMD_ITEM_INCOMPLETE_STR;
        }
        if (!prev_is_digit) {
            return CMD_ITEM_INCOMPLETE_STR;
        }
        // Повтор для последнего значения - Beg
        if (n_beg_Valid && prev_is_digit) {
            if (n < Min || n > Max) {
                return CMD_ITEM_OUT_OF_RANGE;
            }
            //if (n_beg <= n) { @Attention
            if (n_beg < n) {
                Values_Int_List_Items.push_back(Cmd_Item_Int_List_Item(n_beg, n));
                n = 0;
                prev_is_digit = false;
                prev_is_minus = false;
                n_beg_Valid = false;
            } else {
                return CMD_ITEM_OUT_OF_ORDER;
            }
        } else if (prev_is_digit) {
            if (n < Min || n > Max) {
                return CMD_ITEM_OUT_OF_RANGE;
            }
            Values_Int_List_Items.push_back(Cmd_Item_Int_List_Item(n, n));
            n = 0;
            prev_is_digit = false;
            prev_is_minus = false;
            n_beg_Valid = false;
        }
        // Повтор для последнего значения - End

        if (s[s.size() - 1] == ',') {
            return CMD_ITEM_INCOMPLETE_STR;
        }
        if (s[s.size() - 1] == '-') {
            return CMD_ITEM_INCOMPLETE_STR;
        }

        return CMD_ITEM_OK_CAN_CONTINUE;

        return CMD_ITEM_OK; // Список значений, попадающие в Min...Max
    }

    virtual string To_String() {
        stringstream s_str;
        s_str << "Int_List: " << Min << "..." << Max << ": " << Cmd_Item_Base::To_String() << " ";
        for (int i = 0; i < Values_Int_List_Items.size(); i++) {
            Cmd_Item_Int_List_Item &item = Values_Int_List_Items[i];
            if (i > 0) {
                s_str << ",";
            }
            if (item.Min == item.Max) {
                s_str << item.Min;
            } else {
                s_str << item.Min << "-" << item.Max;
            }
        }
        return s_str.str();
    }

};

#endif /* CMD_ITEM_INT_LIST_H */
