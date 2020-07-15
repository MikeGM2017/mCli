/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Word.cpp
 * Author: mike
 *
 * Created on July 14, 2020, 2:03 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Word.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector_01[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("a", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("aZ", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("_a", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a0_", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a_0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("0a", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a z", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair(" az", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("az ", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("+1", CMD_ITEM_ERROR),
};

static const Cmd_Item_Test_Pair TestVector_02[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("abcd", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("a", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("ab", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("abc", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("aZ", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("_a", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a0_", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a_0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("0a", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("a z", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair(" az", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("az ", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("+1", CMD_ITEM_ERROR),
};

void test1() {
    std::cout << "Test_Cmd_Item_Word test 1" << std::endl;

    {
        Cmd_Item_Word v("a", "");

        int test_vector_size = sizeof (TestVector_01) / sizeof (Cmd_Item_Test_Pair);

        for (int i = 0; i < test_vector_size; i++) {
            Cmd_Item_Valid_Result res = v.Parse(TestVector_01[i].first);
            if (res != TestVector_01[i].second)
                std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Word_01) message="
                    << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
                << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector_01[i].second) << ")" << std::endl;
            else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
        }
    }

    {
        Cmd_Item_Word v("abcd", "");

        int test_vector_size = sizeof (TestVector_02) / sizeof (Cmd_Item_Test_Pair);

        for (int i = 0; i < test_vector_size; i++) {
            Cmd_Item_Valid_Result res = v.Parse(TestVector_02[i].first);
            if (res != TestVector_02[i].second)
                std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Word_02) message="
                    << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
                << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector_02[i].second) << ")" << std::endl;
            else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
        }
    }

}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Word" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Word)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Word)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
