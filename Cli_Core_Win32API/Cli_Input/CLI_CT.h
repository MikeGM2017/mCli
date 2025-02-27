/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLI_CT.h
 * Author: mike
 *
 * Created on February 6, 2025, 1:31 PM
 */

#ifndef CLI_CT_H
#define CLI_CT_H

#ifdef __cplusplus
extern "C" {
#endif

    enum CLI_CT {
        CLI_CT_NO,

        CLI_CT_CHAR,

        CLI_CT_CTRL_C,
        CLI_CT_CTRL_Z,
        CLI_CT_CTRL_BACKSLASH,

        CLI_CT_UP,
        CLI_CT_DOWN,
        CLI_CT_LEFT,
        CLI_CT_RIGHT,

        CLI_CT_HOME,
        CLI_CT_END,
        CLI_CT_DELETE,

        CLI_CT_ENTER,
        CLI_CT_TAB,
        CLI_CT_ESC,
        CLI_CT_BACK,

        CLI_CT_LAST,
        CLI_CT_UNDEFINED
    };

#ifdef __cplusplus
}
#endif

#endif /* CLI_CT_H */
