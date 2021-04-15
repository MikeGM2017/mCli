/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

struct Mem_Manager_C Mem_Manager_malloc_free_Init(void) {
    struct Mem_Manager_C Mem_Manager = {
        .Mem_Manager_Alloc = Mem_Manager_Alloc,
        .Mem_Manager_Free = Mem_Manager_Free,
    };
    return Mem_Manager;
}
