/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_History.h"

static void Clear(struct Cli_History *history) {
    history->History_Size = 0;
    history->History_Pos = 0;
}

static int History_Size_Get(struct Cli_History *history) {
    return history->History_Size;
}

static char *History_Item_Get(struct Cli_History *history, int index) {
    if (index >= 0 && index < history->History_Size)
        return history->History[index].Text;
    return history->Dummy_Str;
}

static void History_Put(struct Cli_History *history, char *s_trim) {
    if (history->History_Size < CLI_HISTORY_ITEMS_SIZE_DEF) {
        if (history->History_Size == 0 || strncmp(history->History[history->History_Size - 1].Text, s_trim, CLI_HISTORY_ITEM_TEXT_SIZE)) {
            int len = CLI_HISTORY_ITEM_TEXT_SIZE - 1;
            strncpy(history->History[history->History_Size].Text, s_trim, len);
            history->History[history->History_Size].Text[len] = '\0';
            history->History_Size++;
        }
        history->History_Pos = history->History_Size;
    }
}

static char *History_Up(struct Cli_History *history) {
    if (history->History_Size == 0) {
        return history->Dummy_Str;
    } else {
        if (history->History_Pos > 0) {
            history->History_Pos--;
        }
        return history->History[history->History_Pos].Text;
    }
}

static char *History_Down(struct Cli_History *history) {
    if (history->History_Size == 0) {
        return history->Dummy_Str;
    } else {
        if (history->History_Pos < history->History_Size - 1) {
            history->History_Pos++;
            return history->History[history->History_Pos].Text;
        } else {
            history->History_Pos = history->History_Size;
            return history->Dummy_Str;
        }
    }
}

struct Cli_History Cli_History_Init(void) {
    struct Cli_History history;
    memset(&history, 0, sizeof (history));
    
    history.Clear = Clear;
    history.History_Size_Get = History_Size_Get;
    history.History_Item_Get = History_Item_Get;
    history.History_Put = History_Put;
    history.History_Up = History_Up;
    history.History_Down = History_Down;
    
    return history;
}
