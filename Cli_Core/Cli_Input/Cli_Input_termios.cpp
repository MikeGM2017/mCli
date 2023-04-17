/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_termios.h"

Cli_Input_Abstract *Cli_Input_termios::Cli_Input_Object = NULL;
Cli_Output_Abstract *Cli_Input_termios::Cli_Output_Object = NULL;

void Cli_Input_termios::SIGINT_Handler(int sig) { // Ctrl+C
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear();
        Cli_Input_Object->Is_Ctrl_C_Pressed_Set();
    }
    if (Cli_Output_Object) {
        Cli_Output_Object->Output_NewLine();
        Cli_Output_Object->Output_Str(Cli_Input_Object->Invitation_Full_Get());
    }
}

void Cli_Input_termios::SIGTSTP_Handler(int sig) { // Ctrl+Z
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear();
    }
    if (Cli_Output_Object) {
        Cli_Output_Object->Output_NewLine();
        Cli_Output_Object->Output_Str(Cli_Input_Object->Invitation_Full_Get());
    }
}

bool Cli_Input_termios::Input_Init() {
    Cli_Input_Object = this;
    Cli_Output_Object = &Cli_Output;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    signal(SIGTSTP, SIGTSTP_Handler); // Ctrl+Z

    int res_tcgetattr = tcgetattr(STDIN_FILENO, &terminal_state_prev);
    terminal_state_new = terminal_state_prev;
    terminal_state_new.c_lflag &= ~(ICANON | ECHO);
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_new);

    bool res_cli_output_init = Cli_Output.Output_Init();

    if (res_tcgetattr == 0 && res_tcsetattr == 0 && res_cli_output_init) {
        return true; // Ok
    }

    return false; // Failed
}

bool Cli_Input_termios::Input_Restore() {
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_prev);

    bool res_cli_output_close = Cli_Output.Output_Close();

    if (res_tcsetattr == 0 && res_cli_output_close) {
        return true; // Ok
    }

    return false; // Failed
}

bool Cli_Input_termios::Input_Clear() {
    if (!Cli_Output.Output_Clear())
        Cli_Output.Output_Str("\033[H\033[J");
    return true;
}

Cli_Input_Item Cli_Input_termios::Input_Item_Get() {
    bool stop = false;

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    do {
        int c = getchar();
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
    } while (!stop);

    return Input_Item;
}

bool Cli_Input_termios::Input_sleep(int sleep_sec) {
#ifdef _WIN32
    Sleep(sleep_sec*1000);
#else
    sleep(sleep_sec);
#endif
    return true;
}

bool Cli_Input_termios::Input_kbhit() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    int c = getchar();
    fcntl(STDIN_FILENO, F_SETFL, flags);
    if (c > 0)
        return true;
    return false;
}
