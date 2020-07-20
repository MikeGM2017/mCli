/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_conio.h"

static struct Cli_Input_C *Cli_Input_Object = NULL;
static struct Cli_Output_C *Cli_Output_Object = NULL;

static void SIGINT_Handler(int sig) { // Ctrl+C
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear(Cli_Input_Object);
    }
    if (Cli_Output_Object) {
        Cli_Output_Object->Output_NewLine();
        Cli_Output_Object->Output_Str(Cli_Input_Object->Invitation_Full_Get(Cli_Input_Object));
    }
}

static int Input_Init(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Conio *obj_conio = (struct Cli_Input_C_Conio *) obj;

    Cli_Input_Object = obj;
    Cli_Output_Object = obj->Cli_Output;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C

    return obj->Cli_Output->Output_Init();
}

static int Input_Restore(struct Cli_Input_C *obj) {
    return obj->Cli_Output->Output_Close();
}

static int Input_Clear(struct Cli_Input_C *obj) {
    if (!obj->Cli_Output->Output_Clear())
        system("cls");
    return 1;
}

static struct Cli_Input_C_Item Input_Item_Get(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Conio *obj_conio = (struct Cli_Input_C_Conio *) obj;

    int stop = 0;

    struct Cli_Input_C_Item Input_Item;
    memset(&Input_Item, 0, sizeof (struct Cli_Input_C_Item));

    do {
        int c = getch();
        switch (obj_conio->Input_State) {

            case 0:
                switch (c) {
                    case '\n':
                    case '\r':
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_STR);
                        obj->Input_Str_Clear(obj);
                        stop = 1;
                        break;
                    case 8: // BACK
                        obj->Input_Back(obj);
                        break;
                    case 9: // TAB
                        obj->Input_Str_Pos = obj->Input_Str_Size;
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_TAB);
                        stop = 1;
                        break;
                    case 0xE0: // Начало последовательности
                        obj_conio->Input_State = 1;
                        break;
                    default:
                        obj->Input_Add(obj, c);
                }
                break;

            case 1:
                switch (c) {
                    case 0x47: // Home
                        obj->Input_Home(obj);
                        obj_conio->Input_State = 0;
                        break;
                    case 0x4F: // End
                        obj->Input_End(obj);
                        obj_conio->Input_State = 0;
                        break;
                    case 0x4B: // Left
                        obj->Input_Left(obj);
                        obj_conio->Input_State = 0;
                        break;
                    case 0x4D: // Right
                        obj->Input_Right(obj);
                        obj_conio->Input_State = 0;
                        break;
                    case 0x53: // Delete
                        obj->Input_Delete(obj);
                        obj_conio->Input_State = 0;
                        break;
                    case 0x48: // Up
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_UP);
                        stop = 1;
                        obj_conio->Input_State = 0;
                        break;
                    case 0x50: // Down
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_DOWN);
                        stop = 1;
                        obj_conio->Input_State = 0;
                        break;
                    default:
                        obj_conio->Input_State = 0;
                }
                break;

            default:
                obj_conio->Input_State = 0;

        }
    } while (!stop);

    return Input_Item;
}

int Input_sleep(struct Cli_Input_C *obj, int sleep_sec) {
#ifdef _WIN32
    Sleep(sleep_sec * 1000);
#else
    sleep(sleep_sec);
#endif
    return 1;
}

int Input_kbhit(struct Cli_Input_C *obj) {
    int res = kbhit();
    if (res > 0) {
        int c = getch();
        return 1;
    }
    return 0;
}

struct Cli_Input_C_Conio Cli_Input_C_conio(void) {
    struct Cli_Input_C Cli_Input_Base = Cli_Input_C_base();

    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Input_Clear = Input_Clear;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;
    Cli_Input_Base.Input_sleep = Input_sleep;
    Cli_Input_Base.Input_kbhit = Input_kbhit;

    Cli_Input_Base.Is_Echo_On(&Cli_Input_Base);

    struct Cli_Input_C_Conio Cli_Input_Conio;
    memset(&Cli_Input_Conio, 0, sizeof (struct Cli_Input_C_Conio));

    Cli_Input_Conio.Cli_Input_Base = Cli_Input_Base;

    return Cli_Input_Conio;
}
