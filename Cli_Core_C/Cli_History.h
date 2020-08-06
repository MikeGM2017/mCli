/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_History.h
 * Author: mike
 *
 * Created on August 4, 2020, 3:56 PM
 */

#ifndef CLI_HISTORY_H
#define CLI_HISTORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define CLI_HISTORY_ITEMS_SIZE_DEF 128

#define CLI_HISTORY_ITEM_TEXT_SIZE 1024

    struct Cli_History_Item {
        char Text[CLI_HISTORY_ITEM_TEXT_SIZE];
    };

    struct Cli_History;

    typedef void ftCli_History_Clear(struct Cli_History *history);
    typedef int ftCli_History_History_Size_Get(struct Cli_History *history);
    typedef char *ftCli_History_History_Item_Get(struct Cli_History *history, int index);
    typedef void ftCli_History_History_Put(struct Cli_History *history, char *s_trim);
    typedef char *ftCli_History_History_Up(struct Cli_History *history);
    typedef char *ftCli_History_History_Down(struct Cli_History *history);

    struct Cli_History {
        struct Cli_History_Item History[CLI_HISTORY_ITEMS_SIZE_DEF];
        int History_Size;
        int History_Pos;
        char Dummy_Str[1];

        ftCli_History_Clear *Clear;
        ftCli_History_History_Size_Get *History_Size_Get;
        ftCli_History_History_Item_Get *History_Item_Get;
        ftCli_History_History_Put *History_Put;
        ftCli_History_History_Up *History_Up;
        ftCli_History_History_Down *History_Down;
    };

    struct Cli_History Cli_History_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_HISTORY_H */

