/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <string.h>

#include "Cli_Output_C_file.h"

static char File_Name[CLI_OUTPUT_C_FILENAME_SIZE] = "";
static FILE *File_Out = NULL;

static int Cli_Output_Init(void) {
    if (!File_Out) {
        File_Out = fopen(File_Name, "wt");
        if (File_Out) {
            return 1; // Ok
        }
    }
    return 0; // Failed
}

static int Cli_Output_Close(void) {
    if (File_Out) {
        fclose(File_Out);
        File_Out = NULL;
        return 1; // Ok
    }
    return 0; // Failed
}

static int Cli_Output_Clear(void) {
    return 0; // Failed: can not clear
}

static void Cli_Output_NewLine(void) {
    if (File_Out) {
        fprintf(File_Out, "\n");
    }
}

static void Cli_Output_Char(char c) {
    if (File_Out) {
        fprintf(File_Out, "%c", c);
        fflush(File_Out);
    }
}

static void Cli_Output_Str(char *s) {
    if (File_Out) {
        fprintf(File_Out, "%s", s);
        fflush(File_Out);
    }
}

static void Cli_Output_Return(void) {
    if (File_Out) {
        fprintf(File_Out, "\r");
    }
}

struct Cli_Output_C Cli_Output_C_file(char *filename) {
    struct Cli_Output_C Cli_Output;

    memset(&Cli_Output, 0, sizeof (struct Cli_Output_C));

    Cli_Output.Output_Init = Cli_Output_Init;
    Cli_Output.Output_Close = Cli_Output_Close;
    Cli_Output.Output_Clear = Cli_Output_Clear;
    Cli_Output.Output_NewLine = Cli_Output_NewLine;
    Cli_Output.Output_Char = Cli_Output_Char;
    Cli_Output.Output_Str = Cli_Output_Str;
    Cli_Output.Output_Return = Cli_Output_Return;

    strncpy(File_Name, filename, CLI_OUTPUT_C_FILENAME_SIZE - 1);
    File_Name[CLI_OUTPUT_C_FILENAME_SIZE - 1] = '\0';

    File_Out = NULL;

    return Cli_Output;
}
