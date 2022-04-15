/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_termios.h"

static struct Cli_Input_C *Cli_Input_Object = NULL;

static void SIGINT_Handler(int sig) { // Ctrl+C
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear(Cli_Input_Object);
    }
    struct Cli_Output_C *cli_output_obj = Cli_Input_Object->Cli_Output;
    if (cli_output_obj) {
        cli_output_obj->Output_NewLine(cli_output_obj);
        cli_output_obj->Output_Str(cli_output_obj, Cli_Input_Object->Invitation_Full_Get(Cli_Input_Object));
    }
}

static void SIGTSTP_Handler(int sig) { // Ctrl+Z
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear(Cli_Input_Object);
    }
    struct Cli_Output_C *cli_output_obj = Cli_Input_Object->Cli_Output;
    if (cli_output_obj) {
        cli_output_obj->Output_NewLine(cli_output_obj);
        cli_output_obj->Output_Str(cli_output_obj, Cli_Input_Object->Invitation_Full_Get(Cli_Input_Object));
    }
}

static int Input_Init(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Termios *obj_termios = (struct Cli_Input_C_Termios *) obj;

    Cli_Input_Object = obj;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    signal(SIGTSTP, SIGTSTP_Handler); // Ctrl+Z

    int res_tcgetattr = tcgetattr(STDIN_FILENO, &obj_termios->terminal_state_prev);
    obj_termios->terminal_state_new = obj_termios->terminal_state_prev;
    obj_termios->terminal_state_new.c_lflag &= ~(ICANON | ECHO);
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &obj_termios->terminal_state_new);

    struct Cli_Output_C *cli_output_obj = obj->Cli_Output;
    int res_cli_output_init = cli_output_obj->Output_Init(cli_output_obj);

    if (res_tcgetattr == 0 && res_tcsetattr == 0 && res_cli_output_init) {
        return 1; // Ok
    }

    return 0; // Failed
}

static int Input_Restore(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Termios *obj_termios = (struct Cli_Input_C_Termios *) obj;

    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &obj_termios->terminal_state_prev);

    struct Cli_Output_C *cli_output_obj = obj->Cli_Output;
    int res_cli_output_close = cli_output_obj->Output_Close(cli_output_obj);

    if (res_tcsetattr == 0 && res_cli_output_close) {
        return 1; // Ok
    }

    return 0; // Failed
}

static int Input_Clear(struct Cli_Input_C *obj) {
    struct Cli_Output_C *cli_output_obj = obj->Cli_Output;
    if (!cli_output_obj->Output_Clear(cli_output_obj))
        cli_output_obj->Output_Str(cli_output_obj, "\033[H\033[J");
    return 1; // Ok
}

static struct Cli_Input_C_Item Input_Item_Get(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Termios *obj_termios = (struct Cli_Input_C_Termios *) obj;

    int stop = 0;

    struct Cli_Input_C_Item Input_Item;
    memset(&Input_Item, 0, sizeof (struct Cli_Input_C_Item));

    do {
        int c = getchar();
        switch (obj_termios->Input_State) {

            case 0:
                switch (c) {
                    case 8: // Back
                    case 127:
                    case 247: // Back: Telnet + Special Commands
                        obj->Input_Back(obj);
                        break;
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
                    case 27: // Начало последовательности
                        obj_termios->Input_State = 1;
                        break;
                    default:
                        obj->Input_Add(obj, c);
                }
                break;

            case 1:
                switch (c) {
                    case '[':
                        obj_termios->Input_State = 2;
                        break;
                    case 'O':
                        obj_termios->Input_State = 22;
                        break;
                    default:
                        obj_termios->Input_State = 0;
                }
                break;

            case 2:
            {
                int state_new = 0;
                switch (c) {
                    case 'A': // Стрелка Вверх
                        //Cli_History_Up();
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_UP);
                        stop = 1;
                        break;
                    case 'B': // Стрелка Вниз
                        //Cli_History_Down();
                    {
                        Cli_Input_C_Item_Text_Set(&Input_Item, obj->Input_Str);
                        Cli_Input_C_Item_Type_Set(&Input_Item, CLI_INPUT_ITEM_TYPE_DOWN);
                        stop = 1;
                    }
                        break;
                    case 'C': // Стрелка Вправо
                        obj->Input_Right(obj);
                        break;
                    case 'D': // Стрелка Влево
                        obj->Input_Left(obj);
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
                        obj->Input_Home(obj);
                        break;
                    case 'F':
                        obj->Input_End(obj);
                        break;
                }
                obj_termios->Input_State = state_new;
            }
                break;

            case 22:
                switch (c) {
                    case 'H':
                        obj->Input_Home(obj);
                        break;
                    case 'F':
                        obj->Input_End(obj);
                        break;
                }
                obj_termios->Input_State = 0;
                break;

            case 3:
                switch (c) {
                    case '~':
                        obj->Input_Delete(obj);
                        obj_termios->Input_State = 0;
                        break;
                    case ';':
                        obj_termios->Input_State = 4;
                        break;
                    default:
                        obj_termios->Input_State = 0;
                }
                break;

            case 31:
                switch (c) {
                    case '~':
                        obj->Input_Home(obj);
                        obj_termios->Input_State = 0;
                        break;
                    case ';':
                        obj_termios->Input_State = 4;
                        break;
                    default:
                        obj_termios->Input_State = 0;
                }
                break;

            case 32:
                switch (c) {
                    case '~':
                        obj->Input_End(obj);
                        break;
                }
                obj_termios->Input_State = 0;
                break;

            case 33:
                switch (c) {
                    case ';':
                        obj_termios->Input_State = 4;
                        break;
                    default:
                        obj_termios->Input_State = 0;
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
                        obj_termios->Input_State = 5;
                        break;
                    default:
                        obj_termios->Input_State = 0;
                }
                break;

            case 5:
                obj_termios->Input_State = 0;
                break;

            default:
                obj_termios->Input_State = 0;

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
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    int c = getchar();
    fcntl(STDIN_FILENO, F_SETFL, flags);
    if (c > 0)
        return 1;
    return 0;
}

static int Char_Get_Blocked(struct Cli_Input_C *obj) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    int c = getchar();
    fcntl(STDIN_FILENO, F_SETFL, flags);
    return c;
}

struct Cli_Input_C_Termios Cli_Input_C_termios(struct Cli_Output_C *cli_output) {
    struct Cli_Input_C Cli_Input_Base = Cli_Input_C_base(cli_output);

    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Input_Clear = Input_Clear;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;
    Cli_Input_Base.Input_sleep = Input_sleep;
    Cli_Input_Base.Input_kbhit = Input_kbhit;

    Cli_Input_Base.Is_Echo_On(&Cli_Input_Base);

    Cli_Input_Base.Char_Get_Blocked = Char_Get_Blocked;

    struct Cli_Input_C_Termios Cli_Input_Termios;
    memset(&Cli_Input_Termios, 0, sizeof (struct Cli_Input_C_Termios));

    Cli_Input_Termios.Cli_Input_Base = Cli_Input_Base;

    return Cli_Input_Termios;
}
