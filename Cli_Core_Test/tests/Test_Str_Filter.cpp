/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Str_Filter.cpp
 * Author: mike
 *
 * Created on June 9, 2020, 8:40 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Str_Filter.h"

class Str_Filter_Test_Item {
public:
    string Text;
    string Filter;
    bool Is_Match;

    Str_Filter_Test_Item(string text, string filter, bool is_match) :
    Text(text), Filter(filter), Is_Match(is_match) {
    }

};

static const Str_Filter_Test_Item TestVector_Str_Filter[] = {
    // Text Filter Is_Match
    Str_Filter_Test_Item("", "", true),
    Str_Filter_Test_Item("", "*", true),
    Str_Filter_Test_Item("T", "*", true),
    Str_Filter_Test_Item("Test", "*", true),
    Str_Filter_Test_Item("Test", "?est", true),
    Str_Filter_Test_Item("Test", "?e*", true),

    Str_Filter_Test_Item("Test", "?e?t", true),

    Str_Filter_Test_Item("Test", "*est", true),
    Str_Filter_Test_Item("Test", "*st", true),
    Str_Filter_Test_Item("Test", "*t", true),

    Str_Filter_Test_Item("Test", "T*t", true),
    Str_Filter_Test_Item("Test", "T??t", true),

    Str_Filter_Test_Item("Test", "T*tx", false),
    Str_Filter_Test_Item("Test", "T*x", false),
    Str_Filter_Test_Item("Test", "T??tx", false),
    Str_Filter_Test_Item("Test", "T??x", false),

    Str_Filter_Test_Item("Test", "T*?t", true),
    Str_Filter_Test_Item("Test", "T?*t", true),

    Str_Filter_Test_Item("Login", "L?*?n", true),

    Str_Filter_Test_Item("Looooper", "L?*r", true),
    Str_Filter_Test_Item("Looooper", "L*p?r", true),

    Str_Filter_Test_Item("Looooper", "*er", true),
    Str_Filter_Test_Item("er", "*r*", true),
    Str_Filter_Test_Item("Value_Str", "*tr*", true),
    Str_Filter_Test_Item("Value_Str", "*tr", true),
    Str_Filter_Test_Item("Value_Str", "*Val", false),

    Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*tr", true),
    Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*tr*", true),
    Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*Val", false),
    
    Str_Filter_Test_Item("help", "*uit", false),

};

void test1() {
    std::cout << "Test_Str_Filter test 1" << std::endl;

    char c_single = '?';
    char c_multy = '*';
    Str_Filter *filter = new Str_Filter(c_single, c_multy);

    for (int item = 0; item < sizeof (TestVector_Str_Filter) / sizeof (Str_Filter_Test_Item); item++) {
        Str_Filter_Test_Item test_item = TestVector_Str_Filter[item];
        bool res_is_match = filter->Is_Match(test_item.Filter, test_item.Text);

        bool is_good = (res_is_match == test_item.Is_Match);

        cout << "[" << item << "]:" << "\"" << test_item.Text << "\":\"" << test_item.Filter << "\": test_vector:"
                << (test_item.Is_Match ? "Match" : "NotMatch");
        cout << " - " << (is_good ? "Ok" : "Failed");
        cout << endl;

        if (!is_good) {
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Str_Filter) message="
                    << "\"" << test_item.Text << "\":\"" << test_item.Filter << "\": test_vector:" << (test_item.Is_Match ? "Match" : "NotMatch")
                    << " != res:" << (res_is_match ? "Match" : "NotMatch") << std::endl;
        }

    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Str_Filter" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Str_Filter)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Str_Filter)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
