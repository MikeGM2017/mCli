/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Str_Filter_Abstract.h
 * Author: mike
 *
 * Created on August 31, 2018, 2:45 PM
 */

#ifndef STR_FILTER_ABSTRACT_H
#define STR_FILTER_ABSTRACT_H

#include <string>

using namespace std;

class Str_Filter_Abstract {
protected:

    string Type;
    string Version;

public:

    Str_Filter_Abstract() {
        Type = "Str_Filter_Abstract";
        Version = "0.01";
    }

    virtual bool Is_Match(string filter, string s) = 0;

    string Type_Get() {
        return Type;
    }

    string Version_Get() {
        return Version;
    }

};

#endif /* STR_FILTER_ABSTRACT_H */
