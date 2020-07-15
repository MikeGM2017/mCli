/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Time.cpp
 * Author: mike
 *
 * Created on July 14, 2020, 11:11 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Time.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("\"12-01-33\"", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("\"12-01\"", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("\"15-03", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("\"15-03-", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("\"15-03-4", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("\"15-03-44", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("\"1\"", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("\"15\"", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("\"15-\"", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("\"15-0\"", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("\"15-03\"", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("\"15-03-\"", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("\"15-03-4\"", CMD_ITEM_ERROR),

    Cmd_Item_Test_Pair("\"00-00-00\"", CMD_ITEM_OK), // TIME MIN
    Cmd_Item_Test_Pair("\"24-00-00\"", CMD_ITEM_OUT_OF_RANGE),
    Cmd_Item_Test_Pair("\"00-60-00\"", CMD_ITEM_OUT_OF_RANGE),
    Cmd_Item_Test_Pair("\"00-00-60\"", CMD_ITEM_OUT_OF_RANGE),

    Cmd_Item_Test_Pair("\"23-59-59\"", CMD_ITEM_OK), // TIME MAX
    Cmd_Item_Test_Pair("\"24-59-59\"", CMD_ITEM_OUT_OF_RANGE),
    Cmd_Item_Test_Pair("\"23-60-59\"", CMD_ITEM_OUT_OF_RANGE),
    Cmd_Item_Test_Pair("\"23-59-60\"", CMD_ITEM_OUT_OF_RANGE),

};

void test1() {
    std::cout << "Test_Cmd_Item_Time test 1" << std::endl;

    Cmd_Item_Time v("", "");

    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].first);
        if (res != TestVector[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Time) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Time" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Time)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Time)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
