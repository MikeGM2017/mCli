/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Mem_Manager_malloc_free.h"

static enum Mem_Manager_Res Mem_Manager_Alloc(struct Mem_Manager_C *obj, int size, char **p) {
    (*p) = malloc(size);
    return ( (*p) ? MEM_MANAGER_OK : MEM_MANAGER_NO_MEM);
}

static enum Mem_Manager_Res Mem_Manager_Free(struct Mem_Manager_C *obj, char *p) {
    free(p);
    return MEM_MANAGER_OK;
}

static enum Mem_Manager_Res Mem_Manager_Info(struct Mem_Manager_C *obj, char *s, int s_len) {
    snprintf(s, s_len, "Mem_Manager_malloc_free: <no info>");
    return MEM_MANAGER_OK;
}

struct Mem_Manager_C Mem_Manager_malloc_free_Init(void) {
    struct Mem_Manager_C Mem_Manager = {
        .Mem_Manager_Alloc = Mem_Manager_Alloc,
        .Mem_Manager_Free = Mem_Manager_Free,
        .Mem_Manager_Info = Mem_Manager_Info,
    };
    return Mem_Manager;
}
