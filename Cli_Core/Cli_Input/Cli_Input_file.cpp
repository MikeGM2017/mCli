/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>

#include "Cli_Input_file.h"

bool Cli_Input_file::Input_Init() {
    if (!File_In) {
        File_In = fopen(File_Name.c_str(), "rt");
        if (File_In) {
            return true; // Ok
        }
    }
    return false; // Failed
}

bool Cli_Input_file::Input_Restore() {
    if (File_In) {
        fclose(File_In);
        File_In = NULL;
    }
    bool res_cli_output_close = Cli_Output.Output_Close();
    if (res_cli_output_close) {
        return true; // Ok
    }
    return false; // Failed
}

bool Cli_Input_file::Input_Clear() {
    return true;
}

void Cli_Input_file::Input_Add(char c) {
    Input_Str += c;
    Input_Str_Pos = Input_Str.size();
    if (Is_Echo_Get()) {
        Cli_Output.Output_Char(c);
    }
}

Cli_Input_Item Cli_Input_file::Input_Item_Get() {

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    if (File_In) {

        bool stop = false;

        do {
            char c = fgetc(File_In);
            if (!feof(File_In)) {
                switch (c) {
                    case 9: // Tab
                        Input_Str_Pos = Input_Str.size();
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_TAB);
                        stop = true;
                        break;
                    case '\n':
                    case '\r':
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                        Input_Str_Clear();
                        stop = true;
                        break;
                    default:
                        Input_Add(c);
                }
            } else {
                if (!Input_Str.empty()) {
                    Input_Item.Text_Set(Input_Str);
                    Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                    Input_Str_Clear();
                } else {
                    Input_Item.Text_Set("");
                    Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_QUIT);
                    Input_Str_Clear();
                }
                stop = true;
            }
        } while (!stop);

    } else {
        Input_Item.Text_Set("");
        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_QUIT);
        Input_Str_Clear();
    }

    return Input_Item;
}

bool Cli_Input_file::Input_sleep(int sleep_sec) {
#ifdef _WIN32
    Sleep(sleep_sec * 1000);
#else
    sleep(sleep_sec);
#endif
    return true;
}

bool Cli_Input_file::Input_kbhit() {
    return false;
}
