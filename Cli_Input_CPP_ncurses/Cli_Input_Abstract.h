/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Abstract.h
 * Author: mike
 *
 * Created on June 2, 2020, 9:35 AM
 */

#ifndef CLI_INPUT_ABSTRACT_H
#define CLI_INPUT_ABSTRACT_H

#include <string>

using namespace std;

#include "Cli_Input_Item.h"

#include "Cli_Output_Abstract.h"

class Cli_Input_Abstract {
protected:
    string Title;
    string User;
    string Level;
    string Invitation;
    string Divider_L;
    string Divider_R;
    string Input_Str;

    Cli_Output_Abstract &Cli_Output;

public:

    Cli_Input_Abstract(Cli_Output_Abstract &cli_output) : Divider_L("["), Divider_R("]"), Cli_Output(cli_output) {
    }

    virtual ~Cli_Input_Abstract() {
    }

    virtual string Title_Get() {
        return Title;
    }

    virtual void Title_Set(string title) {
        Title = title;
    }

    virtual string User_Get() {
        return User;
    }

    virtual void User_Set(string user) {
        User = user;
    }

    virtual string Level_Get() {
        return Level;
    }

    virtual void Level_Set(string level) {
        Level = level;
    }

    virtual string Invitation_Get() {
        return Invitation;
    }

    virtual void Invitation_Set(string invitation) {
        Invitation = invitation;
    }

    virtual string Divider_L_Get() {
        return Divider_L;
    }

    virtual void Divider_L_Set(string divider_l) {
        Divider_L = divider_l;
    }

    virtual string Divider_R_Get() {
        return Divider_R;
    }

    virtual void Divider_R_Set(string divider_r) {
        Divider_R = divider_r;
    }

    virtual string Invitation_Full_Get() { // Attention: Should be used for print cli invitation
        string s;
        if (!Title.empty()) {
            s += Divider_L + Title + Divider_R;
        }
        if (!User.empty()) {
            s += Divider_L + User + Divider_R;
        }
        if (!Level.empty()) {
            s += Divider_L + Level + Divider_R;
        }
        if (!Invitation.empty()) {
            s += Invitation;
        }
        return s;
    }

    virtual string Input_Str_Get() {
        return Input_Str;
    };

    virtual void Input_Str_Set(string s) {
        Input_Str = s;
    };

    virtual void Input_Str_Clear() {
        Input_Str.clear();
    };

    virtual bool Input_Init() {
        Cli_Output.Output_Init();
    }
    virtual bool Input_Restore() {
        Cli_Output.Output_Close();
    }

    virtual Cli_Input_Item Input_Item_Get() = 0; // Attention: Main Cli Input Method - Blocked

};

#endif /* CLI_INPUT_ABSTRACT_H */
