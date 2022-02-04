/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>

#include "Cli_Input_file_as_termios.h"

bool Cli_Input_file_as_termios::Input_Init() {
    if (!File_In) {
        File_In = fopen(File_Name.c_str(), "rt");
        if (File_In) {
            return true; // Ok
        }
    }
    return false; // Failed
}

bool Cli_Input_file_as_termios::Input_Restore() {
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

bool Cli_Input_file_as_termios::Input_Clear() {
    return true;
}

void Cli_Input_file_as_termios::Input_Add(char c) {
    Input_Str += c;
    Input_Str_Pos = Input_Str.size();
    if (Is_Echo_Get()) {
        Cli_Output.Output_Char(c);
    }
}

Cli_Input_Item Cli_Input_file_as_termios::Input_Item_Get() {

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    if (File_In) {

        bool stop = false;

        do {
            int c = fgetc(File_In);
            if (!feof(File_In)) {

                switch (Input_State) {

                    case 0:
                        switch (c) {
                            case 8: // Back
                            case 127:
                            case 247: // Back: Telnet + Special Commands
                                Input_Back();
                                break;
                            case 9: // Tab
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
                            case 27: // Начало последовательности
                                Input_State = 1;
                                break;
                            default:
                                Input_Add(c);
                        }
                        break;

                    case 1:
                        switch (c) {
                            case '[':
                                Input_State = 2;
                                break;
                            case 'O':
                                Input_State = 22;
                                break;
                            default:
                                Input_State = 0;
                        }
                        break;

                    case 2:
                    {
                        int state_new = 0;
                        switch (c) {
                            case 'A': // Стрелка Вверх
                                //Cli_History_Up();
                                Input_Item.Text_Set(Input_Str);
                                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_UP);
                                stop = true;
                                break;
                            case 'B': // Стрелка Вниз
                                //Cli_History_Down();
                            {
                                Input_Item.Text_Set(Input_Str);
                                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_DOWN);
                                stop = true;
                            }
                                break;
                            case 'C': // Стрелка Вправо
                                Input_Right();
                                break;
                            case 'D': // Стрелка Влево
                                Input_Left();
                                break;
                            case '3': // Delete
                                state_new = 3;
                                break;
                            case '1': // Home - Telnet
                                state_new = 31;
                                break;
                            case '4': // End - Telnet
                                state_new = 32;
                                break;
                            case '5': // Ubuntu: Ctrl+PgUp
                            case '6': // Ubuntu: Ctrl+PgDown
                                state_new = 33;
                            case 'H':
                                Input_Home();
                                break;
                            case 'F':
                                Input_End();
                                break;
                        }
                        Input_State = state_new;
                    }
                        break;

                    case 22:
                        switch (c) {
                            case 'H':
                                Input_Home();
                                break;
                            case 'F':
                                Input_End();
                                break;
                        }
                        Input_State = 0;
                        break;

                    case 3:
                        switch (c) {
                            case '~':
                                Input_Delete();
                                Input_State = 0;
                                break;
                            case ';':
                                Input_State = 4;
                                break;
                            default:
                                Input_State = 0;
                        }
                        break;

                    case 31:
                        switch (c) {
                            case '~':
                                Input_Home();
                                Input_State = 0;
                                break;
                            case ';':
                                Input_State = 4;
                                break;
                            default:
                                Input_State = 0;
                        }
                        break;

                    case 32:
                        switch (c) {
                            case '~':
                                Input_End();
                                break;
                        }
                        Input_State = 0;
                        break;

                    case 33:
                        switch (c) {
                            case ';':
                                Input_State = 4;
                                break;
                            default:
                                Input_State = 0;
                        }
                        break;

                    case 4:
                        switch (c) {
                            case '3':
                            case '5':
                            case 'A':
                            case 'B':
                            case 'C':
                            case 'D':
                                Input_State = 5;
                                break;
                            default:
                                Input_State = 0;
                        }
                        break;

                    case 5:
                        Input_State = 0;
                        break;

                    default:
                        Input_State = 0;

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

bool Cli_Input_file_as_termios::Input_sleep(int sleep_sec) {
#ifdef _WIN32
    Sleep(sleep_sec * 1000);
#else
    sleep(sleep_sec);
#endif
    return true;
}

bool Cli_Input_file_as_termios::Input_kbhit() {
    return false;
}
