/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Do_Abstract.h
 * Author: mike
 *
 * Created on March 20, 2025, 1:10 PM
 */

#ifndef DO_ABSTRACT_H
#define DO_ABSTRACT_H

#include <string>

using namespace std;

class Do_Abstract {
public:
    virtual void Do() = 0;

    bool Is_Yes(string s) {
        if (s == ("Y") || s == ("y")
                || s == ("YES") || s == ("Yes")
                || s == ("yes")) {
            return true;
        }
        return false;
    }
};

#endif /* DO_ABSTRACT_H */
