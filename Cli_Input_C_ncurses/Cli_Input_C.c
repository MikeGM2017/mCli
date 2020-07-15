/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_C.h"

static char *Title_Get(struct Cli_Input_C *obj) {
    return obj->Title;
}

static void Title_Set(struct Cli_Input_C *obj, char *title) {
    strncpy(obj->Title, title, CLI_INPUT_C_TITLE_SIZE);
}

static char *User_Get(struct Cli_Input_C *obj) {
    return obj->User;
}

static void User_Set(struct Cli_Input_C *obj, char *user) {
    strncpy(obj->User, user, CLI_INPUT_C_USER_SIZE);
}

static char *Level_Get(struct Cli_Input_C *obj) {
    return obj->Level;
}

static void Level_Set(struct Cli_Input_C *obj, char *level) {
    strncpy(obj->Level, level, CLI_INPUT_C_LEVEL_SIZE);
}

static char *Invitation_Get(struct Cli_Input_C *obj) {
    return obj->Invitation;
}

static void Invitation_Set(struct Cli_Input_C *obj, char *invitation) {
    strncpy(obj->Invitation, invitation, CLI_INPUT_C_INVITATION_SIZE);
}

static char *Divider_L_Get(struct Cli_Input_C *obj) {
    return obj->Divider_L;
}

static void Divider_L_Set(struct Cli_Input_C *obj, char *divider_l) {
    strncpy(obj->Divider_L, divider_l, CLI_INPUT_C_DIVIDER_SIZE);
}

static char *Divider_R_Get(struct Cli_Input_C *obj) {
    return obj->Divider_R;
}

static void Divider_R_Set(struct Cli_Input_C *obj, char *divider_r) {
    strncpy(obj->Divider_R, divider_r, CLI_INPUT_C_DIVIDER_SIZE);
}

static char *Invitation_Full_Get(struct Cli_Input_C *obj) { // Attention: Should be used for print cli invitation
    static char s[CLI_INPUT_C_INVITATION_SIZE] = "";
    char *p = s;
    s[0] = '\0'; // clear;
    if (obj->Title[0]) {
        p = strncat(p, obj->Divider_L, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->Title, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->Divider_R, CLI_INPUT_C_INVITATION_SIZE - (p - s));
    }
    if (obj->User[0]) {
        p = strncat(p, obj->Divider_L, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->User, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->Divider_R, CLI_INPUT_C_INVITATION_SIZE - (p - s));
    }
    if (obj->Level[0]) {
        p = strncat(p, obj->Divider_L, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->Level, CLI_INPUT_C_INVITATION_SIZE - (p - s));
        p = strncat(p, obj->Divider_R, CLI_INPUT_C_INVITATION_SIZE - (p - s));
    }
    if (obj->Invitation[0]) {
        p = strncat(p, obj->Invitation, CLI_INPUT_C_INVITATION_SIZE - (p - s));
    }
    return s;
}

static char *Input_Str_Get(struct Cli_Input_C *obj) {
    return obj->Input_Str;
};

static void Input_Str_Set(struct Cli_Input_C *obj, char *s) {
    strncpy(obj->Input_Str, s, CLI_INPUT_C_INPUT_STR_SIZE);
};

static void Input_Str_Clear(struct Cli_Input_C *obj) {
    obj->Input_Str_Pos = 0;
    obj->Input_Str[0] = '\0'; // clear
    obj->Input_Str_Size = 0;
};

static int Input_Init(struct Cli_Input_C *obj) {
    return obj->Cli_Output->Output_Init();
}

static int Input_Restore(struct Cli_Input_C *obj) {
    return obj->Cli_Output->Output_Close();
}

static int Is_Echo_Get(struct Cli_Input_C *obj) {
    return obj->Is_Echo;
}

static void Is_Echo_On(struct Cli_Input_C *obj) {
    obj->Is_Echo = 1;
}

static void Is_Echo_Off(struct Cli_Input_C *obj) {
    obj->Is_Echo = 0;
}

static void Input_Str_To_Output(struct Cli_Input_C *obj) {
    if (obj->Is_Echo_Get(obj)) {
        obj->Cli_Output->Output_Return();
        obj->Cli_Output->Output_Str(Invitation_Full_Get(obj));
        if (obj->Input_Str_Pos > 0) {
            char input_substr[CLI_INPUT_C_INPUT_STR_SIZE];
            strncpy(input_substr, obj->Input_Str, obj->Input_Str_Pos);
            input_substr[obj->Input_Str_Pos] = '\0';
            obj->Cli_Output->Output_Str(input_substr);
        }
    }
}

static void Input_Str_Modified_To_Output(struct Cli_Input_C *obj, char *s_prev) {
    if (obj->Is_Echo_Get(obj)) {
        char s_prev_space[CLI_INPUT_C_INPUT_STR_SIZE];
        int s_prev_len = strnlen(s_prev, CLI_INPUT_C_INPUT_STR_SIZE);
        memset(s_prev_space, ' ', s_prev_len);
        s_prev_space[s_prev_len] = '\0';

        obj->Cli_Output->Output_Return();
        obj->Cli_Output->Output_Str(obj->Invitation_Full_Get(obj));
        obj->Cli_Output->Output_Str(s_prev_space);

        obj->Cli_Output->Output_Return();
        obj->Cli_Output->Output_Str(obj->Invitation_Full_Get(obj));
        obj->Cli_Output->Output_Str(obj->Input_Str);

        // @Attetion: May optimize: if(obj->Input_Str_Pos < obj->Input_Str_Size)
        obj->Cli_Output->Output_Return();
        obj->Cli_Output->Output_Str(obj->Invitation_Full_Get(obj));
        if (obj->Input_Str_Pos > 0) {
            char input_substr[CLI_INPUT_C_INPUT_STR_SIZE];
            strncpy(input_substr, obj->Input_Str, obj->Input_Str_Pos);
            input_substr[obj->Input_Str_Pos] = '\0';
            obj->Cli_Output->Output_Str(input_substr);
        }
    }
}

static void Input_Add(struct Cli_Input_C *obj, char c) {
    if (obj->Input_Str_Size < CLI_INPUT_C_INPUT_STR_SIZE) {
        if (obj->Input_Str_Pos == obj->Input_Str_Size) {
            if (obj->Is_Echo_Get(obj)) {
                obj->Cli_Output->Output_Char(c);
            }
            obj->Input_Str[obj->Input_Str_Size] = c;
            obj->Input_Str_Size++;
            obj->Input_Str[obj->Input_Str_Size] = '\0';
            obj->Input_Str_Pos++;
        } else {

            char s_prev[CLI_INPUT_C_INPUT_STR_SIZE];
            strncpy(s_prev, obj->Input_Str, CLI_INPUT_C_INPUT_STR_SIZE);

            obj->Input_Str[obj->Input_Str_Pos] = c;
            strncpy(obj->Input_Str + obj->Input_Str_Pos + 1,
                    s_prev + obj->Input_Str_Pos,
                    obj->Input_Str_Size - obj->Input_Str_Pos);

            obj->Input_Str_Size++;
            obj->Input_Str[obj->Input_Str_Size] = '\0';
            obj->Input_Str_Pos++;

            obj->Input_Str_Modified_To_Output(obj, s_prev);
        }
    }
}

static void Input_Back(struct Cli_Input_C *obj) {
    if (obj->Input_Str[0] && obj->Input_Str_Pos > 0) {
        char s_prev[CLI_INPUT_C_INPUT_STR_SIZE];
        strncpy(s_prev, obj->Input_Str, CLI_INPUT_C_INPUT_STR_SIZE);
        if (obj->Input_Str_Pos == obj->Input_Str_Size) {
            obj->Input_Str[obj->Input_Str_Size] = '\0';
            obj->Input_Str_Size--;
            obj->Input_Str[obj->Input_Str_Size] = '\0';
            obj->Input_Str_Pos--;
        } else {
            if (obj->Input_Str_Pos < obj->Input_Str_Size) {
                strncpy(obj->Input_Str + obj->Input_Str_Pos - 1,
                        s_prev + obj->Input_Str_Pos,
                        obj->Input_Str_Size - obj->Input_Str_Pos);
            }
            obj->Input_Str_Size--;
            obj->Input_Str[obj->Input_Str_Size] = '\0';
            obj->Input_Str_Pos--;
        }
        obj->Input_Str_Modified_To_Output(obj, s_prev);
    }
}

static void Input_Delete(struct Cli_Input_C *obj) {
    if (obj->Input_Str[0] && obj->Input_Str_Pos < obj->Input_Str_Size) {
        char s_prev[CLI_INPUT_C_INPUT_STR_SIZE];
        strncpy(s_prev, obj->Input_Str, CLI_INPUT_C_INPUT_STR_SIZE);
        if (obj->Input_Str_Pos < obj->Input_Str_Size - 1) {
            strncpy(obj->Input_Str + obj->Input_Str_Pos,
                    s_prev + obj->Input_Str_Pos + 1,
                    obj->Input_Str_Size - obj->Input_Str_Pos - 1);
        }
        obj->Input_Str_Size--;
        obj->Input_Str[obj->Input_Str_Size] = '\0';
        obj->Input_Str_Modified_To_Output(obj, s_prev);
    }
}

static void Input_Home(struct Cli_Input_C *obj) {
    obj->Input_Str_Pos = 0;
    obj->Input_Str_To_Output(obj);
}

static void Input_End(struct Cli_Input_C *obj) {
    obj->Input_Str_Pos = obj->Input_Str_Size;
    obj->Input_Str_To_Output(obj);
}

static void Input_Left(struct Cli_Input_C *obj) {
    if (obj->Input_Str_Pos > 0) {
        obj->Input_Str_Pos--;
        obj->Input_Str_To_Output(obj);
    }
}

static void Input_Right(struct Cli_Input_C *obj) {
    if (obj->Input_Str_Pos < obj->Input_Str_Size) {
        obj->Input_Str_Pos++;
        obj->Input_Str_To_Output(obj);
    }
}

static struct Cli_Input_C_Item Input_Item_Get(struct Cli_Input_C *obj) { // Attention: Main Cli Input Method - Blocked
    struct Cli_Input_C_Item item;
    memset(&item, 0, sizeof (struct Cli_Input_C_Item));
    return item;
}

struct Cli_Input_C Cli_Input_C_base(void) {
    struct Cli_Input_C Cli_Input_Base;
    memset(&Cli_Input_Base, 0, sizeof (struct Cli_Input_C));
    strncpy(Cli_Input_Base.Divider_L, CLI_INPUT_C_DIVIDER_L_DEF, CLI_INPUT_C_DIVIDER_SIZE);
    strncpy(Cli_Input_Base.Divider_R, CLI_INPUT_C_DIVIDER_R_DEF, CLI_INPUT_C_DIVIDER_SIZE);

    Cli_Input_Base.Title_Get = Title_Get;
    Cli_Input_Base.Title_Set = Title_Set;
    Cli_Input_Base.User_Get = User_Get;
    Cli_Input_Base.User_Set = User_Set;
    Cli_Input_Base.Level_Get = Level_Get;
    Cli_Input_Base.Level_Set = Level_Set;
    Cli_Input_Base.Invitation_Get = Invitation_Get;
    Cli_Input_Base.Invitation_Set = Invitation_Set;
    Cli_Input_Base.Divider_L_Get = Divider_L_Get;
    Cli_Input_Base.Divider_L_Set = Divider_L_Set;
    Cli_Input_Base.Divider_R_Get = Divider_R_Get;
    Cli_Input_Base.Divider_R_Set = Divider_R_Set;
    Cli_Input_Base.Invitation_Full_Get = Invitation_Full_Get;
    Cli_Input_Base.Input_Str_Get = Input_Str_Get;
    Cli_Input_Base.Input_Str_Set = Input_Str_Set;
    Cli_Input_Base.Input_Str_Clear = Input_Str_Clear;
    Cli_Input_Base.Input_Init = Input_Init;
    Cli_Input_Base.Input_Restore = Input_Restore;
    Cli_Input_Base.Is_Echo_Get = Is_Echo_Get;
    Cli_Input_Base.Is_Echo_On = Is_Echo_On;
    Cli_Input_Base.Is_Echo_Off = Is_Echo_Off;
    Cli_Input_Base.Input_Str_To_Output = Input_Str_To_Output;
    Cli_Input_Base.Input_Str_Modified_To_Output = Input_Str_Modified_To_Output;
    Cli_Input_Base.Input_Add = Input_Add;
    Cli_Input_Base.Input_Back = Input_Back;
    Cli_Input_Base.Input_Delete = Input_Delete;
    Cli_Input_Base.Input_Home = Input_Home;
    Cli_Input_Base.Input_End = Input_End;
    Cli_Input_Base.Input_Left = Input_Left;
    Cli_Input_Base.Input_Right = Input_Right;
    Cli_Input_Base.Input_Item_Get = Input_Item_Get;

    return Cli_Input_Base;
}