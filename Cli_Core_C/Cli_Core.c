/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Core.h"

static char *Str_Trim(char *s, char *s_trim, int s_trim_size) {
    int s_size = strlen(s);
    int pos_beg = 0;
    int pos_end = s_size ? (s_size - 1) : 0;
    while (pos_beg < s_size && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
    while (pos_end > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
    if (pos_end >= pos_beg) {
        int len = s_trim_size - 1;
        strncpy(s_trim, s + pos_beg, len);
        s_trim[len] = '\0';
    } else {
        s_trim[0] = '\0';
    }
    return s_trim;
}

struct Cli_Core Cli_Core_Init(void) {
    struct Cli_Core cli_core;
    cli_core.Str_Trim = Str_Trim;
    return cli_core;
}
