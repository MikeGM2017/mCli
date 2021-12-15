/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C.h"
#include "Cli_Input_C_file.h"

static int Input_Init(struct Cli_Input_C *obj) {
    struct Cli_Input_C_File *obj_file = (struct Cli_Input_C_File *) obj;
    if (!obj_file->File_In) {
        obj_file->File_In = fopen(obj_file->File_Name, "rt");
        if (obj_file->File_In) {
            return 1; // Ok
        }
    }
    return 0; // Failed
}

static int Input_Restore(struct Cli_Input_C *obj) {
    struct Cli_Input_C_File *obj_file = (struct Cli_Input_C_File *) obj;
    if (obj_file->File_In) {
        fclose(obj_file->File_In);
        obj_file->File_In = NULL;
        return 1; // Ok
    }
    return 0; // Failed
}

static int Input_Clear(struct Cli_Input_C *obj) {
    return 0; // Failed
}

static struct Cli_Input_C_Item Input_Item_Get(struct Cli_Input_C *obj) {
    struct Cli_Input_C_File *obj_file = (struct Cli_Input_C_File *) obj;

    int stop = 0;

    struct Cli_Input_C_Item Input_Item;
    memset(&Input_Item, 0, sizeof (struct Cli_Input_C_Item));

    if (obj_file->File_In) {

        int stop = 0;

        do {
            char c = fgetc(obj_file->File_In);
            if (!feof(obj_file->File_In)) {
                switch (c) {
                    case 9: // Tab
                        obj->Input_Str_Pos = obj->Input_Str_Size;
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_TAB);
                        stop = 1;
                        break;
                    case '\n':
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_STR);
                        obj->Input_Str_Clear(obj);
                        stop = 1;
                        break;
                    default:
                        obj->Input_Add(obj, c);
                }
            } else {
                if (obj->Input_Str[0]) {
                    Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                    Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_STR);
                    obj->Input_Str_Clear(obj);
                } else {
                    Cli_Input_C_Item_Text_Set(&Input_Item, "");
                    Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_QUIT);
                    obj->Input_Str_Clear(obj);
                }
                stop = 1;
            }
        } while (!stop);

    } else {
        Cli_Input_C_Item_Text_Set(&Input_Item, "");
        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_QUIT);
        obj->Input_Str_Clear(obj);
    }

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
    return 0;
}

struct Cli_Input_C_File Cli_Input_C_file(char *filename) {
    struct Cli_Input_C Cli_Input_Base = Cli_Input_C_base();

    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Input_Clear = Input_Clear;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;
    Cli_Input_Base.Input_sleep = Input_sleep;
    Cli_Input_Base.Input_kbhit = Input_kbhit;

    struct Cli_Input_C_File Cli_Input;

    memset(&Cli_Input, 0, sizeof (struct Cli_Input_C_File));

    Cli_Input.Cli_Input_Base = Cli_Input_Base;

    strncpy(Cli_Input.File_Name, filename, CLI_INTPUT_C_FILENAME_SIZE - 1);
    Cli_Input.File_Name[CLI_INTPUT_C_FILENAME_SIZE - 1] = '\0';

    Cli_Input.File_In = NULL;

    return Cli_Input;
}
