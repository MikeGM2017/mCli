/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd.h
 * Author: mike
 *
 * Created on July 16, 2018, 2:09 PM
 */

#ifndef CLI_CMD_H
#define CLI_CMD_H

#include <vector>

using namespace std;

#include "Cli_Cmd_ID.h"
#include "Cli_Cmd_Privilege_ID.h"
#include "Cmd_Token.h"
#include "Cmd_Item_Base.h"

class Cli_Cmd {
protected:
    Cli_Cmd_ID ID;
    int Privilege;
    string Text;
    string Level;
    string Help;
    bool Is_Global;
    bool Is_Set;
    int Min;
    int Max;

public:

    vector<Cmd_Item_Base *> Items;

    Cli_Cmd(Cli_Cmd_ID id) : ID(id), Privilege(CMD_PRIVILEGE_ROOT_DEF), Is_Set(false), Is_Global(false) {

    }

    Cli_Cmd(Cli_Cmd_ID id, Cli_Cmd_Privilege_ID privilege) : ID(id), Privilege(privilege), Is_Set(false), Is_Global(false) {

    }

    virtual ~Cli_Cmd() {
        for (int i = 0; i < Items.size(); i++)
            delete Items[i];
    }

    Cli_Cmd_ID ID_Get() const {
        return ID;
    }

    void Privilege_Set(int v) {
        Privilege = v;
    }

    int Privilege_Get() {
        return Privilege;
    }

    string Help_Get() const {
        return Help;
    }

    void Help_Set(string Help) {
        this->Help = Help;
    }

    bool Is_Set_Get() const {
        return Is_Set;
    }

    void Is_Set_Set(bool Is_Set) {
        this->Is_Set = Is_Set;
    }

    string Text_Get() const {
        return Text;
    }

    void Text_Set(string text) {
        Text = text;
    }

    void Item_Add(Cmd_Item_Base *item) {
        Items.push_back(item);
    }

    int Max_Get() const {
        return Max;
    }

    void Max_Set(int max) {
        Max = max;
    }

    int Min_Get() const {
        return Min;
    }

    void Min_Set(int min) {
        Min = min;
    }

    bool Is_Global_Get() const {
        return Is_Global;
    }

    void Is_Global_Set(bool is_global) {
        Is_Global = is_global;
    }

    string Level_Get() const {
        return Level;
    }

    void Level_Set(string Level) {
        this->Level = Level;
    }

    virtual Cmd_Item_Valid_Result Is_Valid(vector<Cmd_Token *> tokens) {
        if (tokens.size() > Items.size()) return CMD_ITEM_ERROR;

        if (tokens.size() <= Items.size()) {
            for (int i = 0; i < tokens.size(); i++) {
                Cmd_Item_Valid_Result res_valid = Items[i]->Parse(tokens[i]->Text_Get());
                if (i == Items.size() - 1) {
                    // Последний токен может быть введен не до конца или с ошибкой
                    return res_valid;
                } else if (res_valid != CMD_ITEM_OK) {
                    return res_valid;
                }
            }
        }
        if (tokens.size() == Items.size()) return CMD_ITEM_OK;

        return CMD_ITEM_INCOMPLETE;
    }

};

#endif /* CLI_CMD_H */
