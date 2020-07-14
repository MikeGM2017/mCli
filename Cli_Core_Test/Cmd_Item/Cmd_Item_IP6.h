/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cmd_Item_IP6.h
 * Author: mike
 *
 * Created on July 13, 2020, 1:27 PM
 */

#ifndef CMD_ITEM_IP6_H
#define CMD_ITEM_IP6_H

#include <string.h>

#include "Cmd_Item_Base.h"

class Cmd_Item_IP6 : public Cmd_Item_Base {
protected:

    virtual bool Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9')
            return true;
        if (c >= 'a' && c <= 'f')
            return true;
        if (c >= 'A' && c <= 'F')
            return true;
        if (c == ':' || c == '.' || c == '/')
            return true;
        return false;
    }

#define u8 unsigned char

#define IN6PTON_XDIGIT  0x00010000
#define IN6PTON_DIGIT  0x00020000
#define IN6PTON_COLON_MASK 0x00700000
#define IN6PTON_COLON_1  0x00100000 /* single : requested */
#define IN6PTON_COLON_2  0x00200000 /* second : requested */
#define IN6PTON_COLON_1_2 0x00400000 /* :: requested */
#define IN6PTON_DOT  0x00800000 /* . */
#define IN6PTON_DELIM  0x10000000
#define IN6PTON_NULL  0x20000000 /* first/tail */
#define IN6PTON_UNKNOWN  0x40000000

    int hex_to_bin(char ch) {
        if ((ch >= '0') && (ch <= '9'))
            return ch - '0';
        //ch = tolower(ch);
        if ((ch >= 'a') && (ch <= 'f'))
            return ch - 'a' + 10;
        if ((ch >= 'A') && (ch <= 'F'))
            return ch - 'A' + 10;
        return -1;
    }

    inline int xdigit2bin(char c, int delim) {
        int val;

        if (c == delim || c == '\0')
            return IN6PTON_DELIM;
        if (c == ':')
            return IN6PTON_COLON_MASK;
        if (c == '.')
            return IN6PTON_DOT;

        val = hex_to_bin(c);
        if (val >= 0)
            return val | IN6PTON_XDIGIT | (val < 10 ? IN6PTON_DIGIT : 0);

        if (delim == -1)
            return IN6PTON_DELIM;
        return IN6PTON_UNKNOWN;
    }

    int in4_pton(const char *src, int srclen,
            u8 *dst,
            int delim, const char **end) {
        const char *s;
        u8 *d;
        u8 dbuf[4];
        int ret = 0;
        int i;
        int w = 0;

        if (srclen < 0)
            srclen = strlen(src);
        s = src;
        d = dbuf;
        i = 0;
        while (1) {
            int c;
            c = xdigit2bin(srclen > 0 ? *s : '\0', delim);
            if (!(c & (IN6PTON_DIGIT | IN6PTON_DOT | IN6PTON_DELIM | IN6PTON_COLON_MASK))) {
                goto out;
            }
            if (c & (IN6PTON_DOT | IN6PTON_DELIM | IN6PTON_COLON_MASK)) {
                if (w == 0)
                    goto out;
                *d++ = w & 0xff;
                w = 0;
                i++;
                if (c & (IN6PTON_DELIM | IN6PTON_COLON_MASK)) {
                    if (i != 4)
                        goto out;
                    break;
                }
                goto cont;
            }
            w = (w * 10) + c;
            if ((w & 0xffff) > 255) {
                goto out;
            }
cont:
            if (i >= 4)
                goto out;
            s++;
            srclen--;
        }
        ret = 1;
        memcpy(dst, dbuf, sizeof (dbuf));
out:
        if (end)
            *end = s;
        return ret;
    }

    int in6_pton(const char *src, int srclen,
            u8 *dst,
            int delim, const char **end) {
        const char *s, *tok = NULL;
        u8 *d, *dc = NULL;
        u8 dbuf[16];
        int ret = 0;
        int i;
        int state = IN6PTON_COLON_1_2 | IN6PTON_XDIGIT | IN6PTON_NULL;
        int w = 0;

        memset(dbuf, 0, sizeof (dbuf));

        s = src;
        d = dbuf;
        if (srclen < 0)
            srclen = strlen(src);

        while (1) {
            int c;

            c = xdigit2bin(srclen > 0 ? *s : '\0', delim);
            if (!(c & state))
                goto out;
            if (c & (IN6PTON_DELIM | IN6PTON_COLON_MASK)) {
                /* process one 16-bit word */
                if (!(state & IN6PTON_NULL)) {
                    *d++ = (w >> 8) & 0xff;
                    *d++ = w & 0xff;
                }
                w = 0;
                if (c & IN6PTON_DELIM) {
                    /* We've processed last word */
                    break;
                }
                /*
                 * COLON_1 => XDIGIT
                 * COLON_2 => XDIGIT|DELIM
                 * COLON_1_2 => COLON_2
                 */
                switch (state & IN6PTON_COLON_MASK) {
                    case IN6PTON_COLON_2:
                        dc = d;
                        state = IN6PTON_XDIGIT | IN6PTON_DELIM;
                        if (dc - dbuf >= sizeof (dbuf))
                            state |= IN6PTON_NULL;
                        break;
                    case IN6PTON_COLON_1 | IN6PTON_COLON_1_2:
                        state = IN6PTON_XDIGIT | IN6PTON_COLON_2;
                        break;
                    case IN6PTON_COLON_1:
                        state = IN6PTON_XDIGIT;
                        break;
                    case IN6PTON_COLON_1_2:
                        state = IN6PTON_COLON_2;
                        break;
                    default:
                        state = 0;
                }
                tok = s + 1;
                goto cont;
            }

            if (c & IN6PTON_DOT) {
                ret = in4_pton(tok ? tok : s, srclen + (int) (s - tok), d, delim, &s);
                if (ret > 0) {
                    d += 4;
                    break;
                }
                goto out;
            }

            w = (w << 4) | (0xff & c);
            state = IN6PTON_COLON_1 | IN6PTON_DELIM;
            if (!(w & 0xf000)) {
                state |= IN6PTON_XDIGIT;
            }
            if (!dc && d + 2 < dbuf + sizeof (dbuf)) {
                state |= IN6PTON_COLON_1_2;
                state &= ~IN6PTON_DELIM;
            }
            if (d + 2 >= dbuf + sizeof (dbuf)) {
                state &= ~(IN6PTON_COLON_1 | IN6PTON_COLON_1_2);
            }
cont:
            if ((dc && d + 4 < dbuf + sizeof (dbuf)) ||
                    d + 4 == dbuf + sizeof (dbuf)) {
                state |= IN6PTON_DOT;
            }
            if (d >= dbuf + sizeof (dbuf)) {
                state &= ~(IN6PTON_XDIGIT | IN6PTON_COLON_MASK);
            }
            s++;
            srclen--;
        }

        i = 15;
        d--;

        if (dc) {
            while (d >= dc)
                dst[i--] = *d--;
            while (i >= dc - dbuf)
                dst[i--] = 0;
            while (i >= 0)
                dst[i--] = *d--;
        } else
            memcpy(dst, dbuf, sizeof (dbuf));

        ret = 1;
out:
        if (end)
            *end = s;
        return ret;
    }

public:

    Cmd_Item_IP6(string text, string help) : Cmd_Item_Base(text, help) {
        Type = "IP6";
    }

    virtual string Debug_Value_Get() {
        return "::ffff:1.2.3.4";
    }

    virtual Cmd_Item_Valid_Result Parse(string s) {
        Value_Str = s;

        if (s.size() == 0) return CMD_ITEM_EMPTY;

        for (int pos = 0; pos < s.size(); pos++) {
            if (!Is_Char_Valid(s[pos], pos, s.size())) return CMD_ITEM_ERROR;
        }

        u8 dest[32];
        int res_ipv6 = in6_pton(s.c_str(), s.size(), dest, -1, NULL);
        if (res_ipv6 <= 0) return CMD_ITEM_ERROR;

        return CMD_ITEM_OK;
    }

    virtual bool Is_Space_After_Add(string s) {
        if (s.size() >= 7) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == CMD_ITEM_OK)
                return true;
        }
        return false;
    }

};

#endif /* CMD_ITEM_IP6_H */