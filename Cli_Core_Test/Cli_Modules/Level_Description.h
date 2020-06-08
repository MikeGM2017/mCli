/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Level_Description.h
 * Author: mike
 *
 * Created on August 10, 2018, 11:59 AM
 */

#ifndef LEVEL_DESCRIPTION_H
#define LEVEL_DESCRIPTION_H

#include <string>

using namespace std;

class Level_Description {
public:
    string Level;
    string Parameter;

    Level_Description() {
    }

    Level_Description(string level) : Level(level) {
    }

    Level_Description(string level, string parameter) : Level(level), Parameter(parameter) {
    }

};

#endif /* LEVEL_DESCRIPTION_H */
