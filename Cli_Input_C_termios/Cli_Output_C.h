/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_C.h
 * Author: mike
 *
 * Created on July 2, 2020, 11:31 AM
 */

#ifndef CLI_OUTPUT_C_H
#define CLI_OUTPUT_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int ftOutput_Init(void);
typedef int ftOutput_Close(void);
typedef int ftOutput_Clear(void);
typedef void ftOutput_NewLine(void);
typedef void ftOutput_Char(char c);
typedef void ftOutput_Str(char *s);
typedef void ftOutput_Return(void);

struct Cli_Output_C {
    ftOutput_Init *Output_Init;
    ftOutput_Close *Output_Close;
    ftOutput_Clear *Output_Clear;
    ftOutput_NewLine *Output_NewLine;
    ftOutput_Char *Output_Char;
    ftOutput_Str *Output_Str;
    ftOutput_Return *Output_Return;
};

#ifdef __cplusplus
}
#endif

#endif /* CLI_OUTPUT_C_H */
