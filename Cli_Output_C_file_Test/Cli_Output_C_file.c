/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <string.h>

#include "Cli_Output_C_file.h"

static int Cli_Output_Init(struct Cli_Output_C *obj) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (!obj_file->File_Out) {
        obj_file->File_Out = fopen(obj_file->File_Name, "wt");
        if (obj_file->File_Out) {
            return 1; // Ok
        }
    }
    return 0; // Failed
}

static int Cli_Output_Close(struct Cli_Output_C *obj) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (obj_file->File_Out) {
        fclose(obj_file->File_Out);
        obj_file->File_Out = NULL;
        return 1; // Ok
    }
    return 0; // Failed
}

static int Cli_Output_Clear(struct Cli_Output_C *obj) {
    return 0; // Failed: can not clear
}

static void Cli_Output_NewLine(struct Cli_Output_C *obj) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (obj_file->File_Out) {
        fprintf(obj_file->File_Out, "\n");
    }
}

static void Cli_Output_Char(struct Cli_Output_C *obj, char c) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (obj_file->File_Out) {
        fprintf(obj_file->File_Out, "%c", c);
        fflush(obj_file->File_Out);
    }
}

static void Cli_Output_Str(struct Cli_Output_C *obj, char *s) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (obj_file->File_Out) {
        fprintf(obj_file->File_Out, "%s", s);
        fflush(obj_file->File_Out);
    }
}

static void Cli_Output_Return(struct Cli_Output_C *obj) {
    struct Cli_Output_C_file *obj_file = (struct Cli_Output_C_file *)obj;
    if (obj_file->File_Out) {
        fprintf(obj_file->File_Out, "\r");
        fflush(obj_file->File_Out);
    }
}

struct Cli_Output_C_file Cli_Output_C_file(char *filename) {
    struct Cli_Output_C Cli_Output_Base;
    struct Cli_Output_C_file Cli_Output_file;

    memset(&Cli_Output_Base, 0, sizeof (struct Cli_Output_C));

    Cli_Output_Base.Output_Init = Cli_Output_Init;
    Cli_Output_Base.Output_Close = Cli_Output_Close;
    Cli_Output_Base.Output_Clear = Cli_Output_Clear;
    Cli_Output_Base.Output_NewLine = Cli_Output_NewLine;
    Cli_Output_Base.Output_Char = Cli_Output_Char;
    Cli_Output_Base.Output_Str = Cli_Output_Str;
    Cli_Output_Base.Output_Return = Cli_Output_Return;
    
    Cli_Output_file.Cli_Output_Base = Cli_Output_Base;

    strncpy(Cli_Output_file.File_Name, filename, CLI_OUTPUT_C_FILENAME_SIZE - 1);
    Cli_Output_file.File_Name[CLI_OUTPUT_C_FILENAME_SIZE - 1] = '\0';

    Cli_Output_file.File_Out = NULL;

    return Cli_Output_file;
}
