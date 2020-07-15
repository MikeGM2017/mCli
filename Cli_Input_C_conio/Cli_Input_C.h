/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C.h
 * Author: mike
 *
 * Created on July 2, 2020, 12:56 PM
 */

#ifndef CLI_INPUT_C_H
#define CLI_INPUT_C_H

#include <string.h>

#include "Cli_Input_C_Item.h"

#include "Cli_Output_C.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLI_INPUT_C_TITLE_SIZE 32
#define CLI_INPUT_C_USER_SIZE 32
#define CLI_INPUT_C_LEVEL_SIZE 32
#define CLI_INPUT_C_INVITATION_SIZE 128
#define CLI_INPUT_C_DIVIDER_SIZE 8
#define CLI_INPUT_C_DIVIDER_L_DEF "["
#define CLI_INPUT_C_DIVIDER_R_DEF "]"
#define CLI_INPUT_C_INPUT_STR_SIZE 1024

    struct Cli_Input_C;

    typedef char *ftCli_Input_C_Title_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Title_Set(struct Cli_Input_C *obj, char *title);
    typedef char *ftCli_Input_C_User_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_User_Set(struct Cli_Input_C *obj, char *user);
    typedef char *ftCli_Input_C_Level_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Level_Set(struct Cli_Input_C *obj, char *level);
    typedef char *ftCli_Input_C_Invitation_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Invitation_Set(struct Cli_Input_C *obj, char *invitation);
    typedef char *ftCli_Input_C_Divider_L_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Divider_L_Set(struct Cli_Input_C *obj, char *divider_l);
    typedef char *ftCli_Input_C_Divider_R_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Divider_R_Set(struct Cli_Input_C *obj, char *divider_r);
    typedef char *ftCli_Input_C_Invitation_Full_Get(struct Cli_Input_C *obj);
    typedef char *ftCli_Input_C_Input_Str_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Str_Set(struct Cli_Input_C *obj, char *s);
    typedef void ftCli_Input_C_Input_Str_Clear(struct Cli_Input_C *obj);
    typedef int ftCli_Input_C_Input_Init(struct Cli_Input_C *obj);
    typedef int ftCli_Input_C_Input_Restore(struct Cli_Input_C *obj);
    typedef int ftCli_Input_C_Is_Echo_Get(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Is_Echo_On(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Is_Echo_Off(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Str_To_Output(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Str_Modified_To_Output(struct Cli_Input_C *obj, char *s_prev);
    typedef void ftCli_Input_C_Input_Add(struct Cli_Input_C *obj, char c);
    typedef void ftCli_Input_C_Input_Back(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Delete(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Home(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_End(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Left(struct Cli_Input_C *obj);
    typedef void ftCli_Input_C_Input_Right(struct Cli_Input_C *obj);
    typedef struct Cli_Input_C_Item ftCli_Input_C_Input_Item_Get(struct Cli_Input_C *obj);

    struct Cli_Input_C {
        char Title[CLI_INPUT_C_TITLE_SIZE];
        char User[CLI_INPUT_C_USER_SIZE];
        char Level[CLI_INPUT_C_LEVEL_SIZE];
        char Invitation[CLI_INPUT_C_INVITATION_SIZE];
        char Divider_L[CLI_INPUT_C_DIVIDER_SIZE];
        char Divider_R[CLI_INPUT_C_DIVIDER_SIZE];
        char Input_Str[CLI_INPUT_C_INPUT_STR_SIZE];

        struct Cli_Output_C *Cli_Output;

        int Is_Echo;
        int Input_Str_Size;
        int Input_Str_Pos;

        ftCli_Input_C_Title_Get *Title_Get;
        ftCli_Input_C_Title_Set *Title_Set;
        ftCli_Input_C_User_Get *User_Get;
        ftCli_Input_C_User_Set *User_Set;
        ftCli_Input_C_Level_Get *Level_Get;
        ftCli_Input_C_Level_Set *Level_Set;
        ftCli_Input_C_Invitation_Get *Invitation_Get;
        ftCli_Input_C_Invitation_Set *Invitation_Set;
        ftCli_Input_C_Divider_L_Get *Divider_L_Get;
        ftCli_Input_C_Divider_L_Set *Divider_L_Set;
        ftCli_Input_C_Divider_R_Get *Divider_R_Get;
        ftCli_Input_C_Divider_R_Set *Divider_R_Set;
        ftCli_Input_C_Invitation_Full_Get *Invitation_Full_Get;
        ftCli_Input_C_Input_Str_Get *Input_Str_Get;
        ftCli_Input_C_Input_Str_Set *Input_Str_Set;
        ftCli_Input_C_Input_Str_Clear *Input_Str_Clear;
        ftCli_Input_C_Input_Init *Input_Init;
        ftCli_Input_C_Input_Restore *Input_Restore;
        ftCli_Input_C_Is_Echo_Get *Is_Echo_Get;
        ftCli_Input_C_Is_Echo_On *Is_Echo_On;
        ftCli_Input_C_Is_Echo_Off *Is_Echo_Off;
        ftCli_Input_C_Input_Str_To_Output *Input_Str_To_Output;
        ftCli_Input_C_Input_Str_Modified_To_Output *Input_Str_Modified_To_Output;
        ftCli_Input_C_Input_Add *Input_Add;
        ftCli_Input_C_Input_Back *Input_Back;
        ftCli_Input_C_Input_Delete *Input_Delete;
        ftCli_Input_C_Input_Home *Input_Home;
        ftCli_Input_C_Input_End *Input_End;
        ftCli_Input_C_Input_Left *Input_Left;
        ftCli_Input_C_Input_Right *Input_Right;
        ftCli_Input_C_Input_Item_Get *Input_Item_Get;

    };

    struct Cli_Input_C Cli_Input_C_base(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_INPUT_C_H */
