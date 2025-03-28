/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CmdLine_Parse.h"

vector<wstring> CmdLine_Parse(TCHAR *s) {

    vector<wstring> v;

    const int WBUF_SIZE = 1024;
    TCHAR wbuf[WBUF_SIZE];
    int wbuf_len = wnsprintf(wbuf, WBUF_SIZE - 1, "%s", s);

    int wbuf_beg = 0;
    int wbuf_pos = 0;
    bool stop = false;

    // Case 1: simple string -> tokens - realized
    // Case 2: string with "Abc xyz" / 'Abc xyz' / "Abc \"\' xyz" / 'Abc \"\' xyz' -> tokens - NOT REALIZED
    // Case 3: string with Abc\ xyz -> tokens - NOT REALIZED

    do {
        TCHAR c = wbuf[wbuf_pos];
        if (c != 0) {
            if (c == ' ' || c == '\t') {
                v.push_back(wstring(wbuf + wbuf_beg, wbuf + wbuf_pos));

                // skip spaces - beg
                do {
                    wbuf_pos++;
                    c = wbuf[wbuf_pos];
                } while ((c == ' ' || c == '\t') && wbuf_pos <= WBUF_SIZE);
                // skip spaces - end

                wbuf_beg = wbuf_pos;
            } else {
                wbuf_pos++;
            }
            if (wbuf_pos > WBUF_SIZE) {
                stop = true;
            }
        } else {
            // last
            v.push_back(wstring(wbuf + wbuf_beg, wbuf + wbuf_pos));
            stop = true;
        }
    } while (!stop);

    return v;
}
