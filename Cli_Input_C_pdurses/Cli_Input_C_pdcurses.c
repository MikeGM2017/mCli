/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_pdcurses.h"

static int Input_Init(struct Cli_Input_C *obj) {
    return obj->Cli_Output->Output_Init();
}

static int Input_Restore(struct Cli_Input_C *obj) {
    return obj->Cli_Output->Output_Close();
}

static int Input_Clear(struct Cli_Input_C *obj) {
    if(!obj->Cli_Output->Output_Clear())
        clear();
    return 1;
}

static struct Cli_Input_C_Item Input_Item_Get(struct Cli_Input_C *obj) {
    int stop = 0;

    struct Cli_Input_C_Item Input_Item;
    memset(&Input_Item, 0, sizeof (struct Cli_Input_C_Item));

    do {
        unsigned int c = getch();
        switch (c) {
            case '\n': // Enter - NCurses
            case '\r': // Enter - PDCurses
            case KEY_ENTER:
                Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_STR);
                obj->Input_Str_Clear(obj);
                stop = 1;
                break;
            case 0x03: // Ctrl+C
                obj->Input_Str_Clear(obj);
                obj->Cli_Output->Output_NewLine();
                obj->Cli_Output->Output_Str(obj->Invitation_Full_Get(obj));
                break;
            case 0x1C: // Ctrl+"\"
                Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_QUIT);
                obj->Input_Str_Clear(obj);
                obj->Cli_Output->Output_NewLine();
                obj->Cli_Output->Output_Str("Ctrl+\\");
                obj->Cli_Output->Output_NewLine();
                stop = 1;
                break;
            case 8: // BACK
            case KEY_BACKSPACE:
                obj->Input_Back(obj);
                break;
            case 9: // Tab
                obj->Input_Str_Pos = obj->Input_Str_Size;
                Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_TAB);
                stop = 1;
                break;
            case KEY_DC:
                obj->Input_Delete(obj);
                break;
            case KEY_HOME:
                obj->Input_Home(obj);
                break;
            case KEY_END:
                obj->Input_End(obj);
                break;
            case KEY_LEFT:
                obj->Input_Left(obj);
                break;
            case KEY_RIGHT:
                obj->Input_Right(obj);
                break;
            case KEY_UP:
                Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_UP);
                stop = 1;
                break;
            case KEY_DOWN:
                Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_DOWN);
                stop = 1;
                break;
            default:
                obj->Input_Add(obj, c);
        }
    } while (!stop);

    return Input_Item;
}

static int Input_sleep(struct Cli_Input_C *obj, int sleep_sec) {
#ifdef _WIN32
    Sleep(sleep_sec * 1000);
#else
    sleep(sleep_sec);
#endif
    return 1;
}

static int Input_kbhit(struct Cli_Input_C *obj) {
    nodelay(stdscr, TRUE);
    int c = getch();
    nodelay(stdscr, FALSE);
    if (c > 0) {
        return true;
    }
    return false;
}

struct Cli_Input_C_PDCurses Cli_Input_C_pdcurses(void) {
    struct Cli_Input_C Cli_Input_Base = Cli_Input_C_base();

    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Input_Clear = Input_Clear;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;
    Cli_Input_Base.Input_sleep = Input_sleep;
    Cli_Input_Base.Input_kbhit = Input_kbhit;

    Cli_Input_Base.Is_Echo_On(&Cli_Input_Base);

    struct Cli_Input_C_PDCurses Cli_Input_PDCurses;
    memset(&Cli_Input_PDCurses, 0, sizeof (struct Cli_Input_C_PDCurses));

    Cli_Input_PDCurses.Cli_Input_Base = Cli_Input_Base;

    return Cli_Input_PDCurses;
}
