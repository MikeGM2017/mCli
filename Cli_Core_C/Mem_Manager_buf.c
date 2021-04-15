/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mem_Manager_buf.h"

static enum Mem_Manager_Res Mem_Manager_Alloc(struct Mem_Manager_C *obj, int size, char **p) {
    struct Mem_Manager_buf *obj_buf = (struct Mem_Manager_buf *) obj;

    if (obj_buf->buf_pos + size <= obj_buf->buf_size) {
        (*p) = obj_buf->buf + obj_buf->buf_pos;
        obj_buf->buf_pos += size;
        return MEM_MANAGER_OK;
    } else {
        (*p) = 0;
        return MEM_MANAGER_NO_MEM;
    }
}

static enum Mem_Manager_Res Mem_Manager_Free(struct Mem_Manager_C *obj, char *p) {
    // nothing
    return MEM_MANAGER_OK;
}

struct Mem_Manager_buf Mem_Manager_buf_Init(char *buf, int buf_size) {
    struct Mem_Manager_buf Mem_Manager = {
        .Mem_Manager_Base = {
            .Mem_Manager_Alloc = Mem_Manager_Alloc,
            .Mem_Manager_Free = Mem_Manager_Free,
        },
        .buf = buf,
        .buf_size = buf_size,
        .buf_pos = 0,
    };
    return Mem_Manager;
}
