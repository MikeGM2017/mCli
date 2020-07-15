/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C_termios.h"

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

static void SIGTSTP_Handler(int sig) { // Ctrl+Z
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear(Cli_Input_Object);
    }
    if (Cli_Output_Object) {
        Cli_Output_Object->Output_NewLine();
        Cli_Output_Object->Output_Str(Cli_Input_Object->Invitation_Full_Get(Cli_Input_Object));
    }
}

static int Input_Init(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Termios *obj_termios = (struct Cli_Input_C_Termios *) obj;

    Cli_Input_Object = obj;
    Cli_Output_Object = obj->Cli_Output;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    signal(SIGTSTP, SIGTSTP_Handler); // Ctrl+Z

    int res_tcgetattr = tcgetattr(STDIN_FILENO, &obj_termios->terminal_state_prev);
    obj_termios->terminal_state_new = obj_termios->terminal_state_prev;
    obj_termios->terminal_state_new.c_lflag &= ~(ICANON | ECHO);
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &obj_termios->terminal_state_new);

    int res_cli_output_init = obj->Cli_Output->Output_Init();

    if (res_tcgetattr == 0 && res_tcsetattr == 0 && res_cli_output_init) {
        return 1; // Ok
    }

    return 0; // Failed
}

static int Input_Restore(struct Cli_Input_C *obj) {
    struct Cli_Input_C_Termios *obj_termios = (struct Cli_Input_C_Termios *) obj;

    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &obj_termios->terminal_state_prev);

    int res_cli_output_close = obj->Cli_Output->Output_Close();

    if (res_tcsetattr == 0 && res_cli_output_close) {
        return 1; // Ok
    }

    return 0; // Failed
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
};

struct Cli_Input_C_Termios Cli_Input_C_termios(void) {
    struct Cli_Input_C Cli_Input_Base = Cli_Input_C_base();

    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;

    Cli_Input_Base.Is_Echo_On(&Cli_Input_Base);

    struct Cli_Input_C_Termios Cli_Input_Termios;
    memset(&Cli_Input_Termios, 0, sizeof (struct Cli_Input_C_Termios));

    Cli_Input_Termios.Cli_Input_Base = Cli_Input_Base;

    return Cli_Input_Termios;
}
