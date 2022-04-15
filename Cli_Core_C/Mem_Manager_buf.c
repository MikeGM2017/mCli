/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ctype.h>

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

static void Pointer_Str_To_Upper(char *s) {
    while (*s) {
        *s = (*s == 'x' ? *s : toupper(*s));
        s++;
    }
}

static enum Mem_Manager_Res Mem_Manager_Info(struct Mem_Manager_C *obj, char *s, int s_len) {
    struct Mem_Manager_buf *obj_buf = (struct Mem_Manager_buf *) obj;
    const int s_buf_ptr_size = 32;
    char s_buf_ptr[s_buf_ptr_size];
    snprintf(s_buf_ptr, s_buf_ptr_size, "%p", obj_buf->buf);
    Pointer_Str_To_Upper(s_buf_ptr);
    snprintf(s, s_len, "Mem_Manager_buf: buf=%s buf_size=0x%08X buf_pos=0x%08X",
            s_buf_ptr, obj_buf->buf_size, obj_buf->buf_pos);
    return MEM_MANAGER_OK;
}

struct Mem_Manager_buf Mem_Manager_buf_Init(char *buf, int buf_size) {
    struct Mem_Manager_buf Mem_Manager = {
        .Mem_Manager_Base =
        {
            .Mem_Manager_Alloc = Mem_Manager_Alloc,
            .Mem_Manager_Free = Mem_Manager_Free,
            .Mem_Manager_Info = Mem_Manager_Info,
        },
        .buf = buf,
        .buf_size = buf_size,
        .buf_pos = 0,
    };
    return Mem_Manager;
}
