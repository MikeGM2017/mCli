/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Str_Esc.cpp
 * Author: mike
 *
 * Created on January 12, 2024, 1:33 PM
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Str_Esc.h"

class Test_Item {
public:
    string Src_Str;
    string Res_Str;
    enum Cmd_Item_Valid_Result Res;

    Test_Item(string src_str, string res_str, enum Cmd_Item_Valid_Result res) : Src_Str(src_str), Res_Str(res_str), Res(res) {
    }

};

static const Test_Item TestVector[] = {

    Test_Item("\\\"Str\\\"", "\"Str\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("\"", "\"", CMD_ITEM_INCOMPLETE_STR),

    // From Test_Cmd_Item_Str - Beg

    Test_Item("", "", CMD_ITEM_EMPTY),
    Test_Item("\"<str>\"", "<str>", CMD_ITEM_OK),
    Test_Item("\"  <str1>   <str2>    \"", "  <str1>   <str2>    ", CMD_ITEM_OK),
    Test_Item("\"\"", "", CMD_ITEM_OK),
    Test_Item("\"", "\"", CMD_ITEM_INCOMPLETE_STR),
    Test_Item("\"<str>", "\"<str>", CMD_ITEM_INCOMPLETE_STR),
    Test_Item("<str>\"", "<str>\"", CMD_ITEM_ERROR),
    Test_Item("FF:FF:FF:FF:FF:FF", "FF:FF:FF:FF:FF:FF", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Test_Item("<str>'", "<str>'", CMD_ITEM_ERROR),

    // Escaped:
    Test_Item("\\\"Str\\\"", "\"Str\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    // From Test_Cmd_Item_Str - End

    // '\"'
    // Not Escaped:
    Test_Item("", "", CMD_ITEM_EMPTY),
    Test_Item("\"\"", "", CMD_ITEM_OK),
    Test_Item("\'\'", "", CMD_ITEM_OK),
    Test_Item("Str", "Str", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("Str\"Str", "Str\"Str", CMD_ITEM_ERROR),
    Test_Item("\" Str Str \"", " Str Str ", CMD_ITEM_OK),
    Test_Item("\" ", "\" ", CMD_ITEM_INCOMPLETE_STR),

    // Escaped:
    Test_Item("a\\\"", "a\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\"b", "a\"b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\'b", "a\'b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\\b", "a\\b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\ b", "a b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\ab", "a\ab", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\bb", "a\bb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\fb", "a\fb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\nb", "a\nb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\rb", "a\rb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\tb", "a\tb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\vb", "a\vb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\zb", "azb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Test_Item("\\\"a\\\"", "\"a\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("\\\"a", "\"a", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Test_Item("\\\"", "\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("\\", "\\", CMD_ITEM_INCOMPLETE_STR),

    Test_Item("a\\\"\\\'\\\\\\ \\a\\b\\f\\n\\r\\t\\v\\z ", "a\"\'\\ \a\b\f\n\r\t\vz ", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    // '\''
    // Not Escaped:
    Test_Item("", "", CMD_ITEM_EMPTY),
    Test_Item("\'\'", "", CMD_ITEM_OK),
    Test_Item("Str", "Str", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("Str\'Str", "Str\'Str", CMD_ITEM_ERROR),
    Test_Item("\' Str Str \'", " Str Str ", CMD_ITEM_OK),
    Test_Item("\' ", "\' ", CMD_ITEM_INCOMPLETE_STR),

    // Escaped:
    Test_Item("a\\\'", "a\'", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\'b", "a\'b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\'b", "a\'b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\\\b", "a\\b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\ b", "a b", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\ab", "a\ab", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\bb", "a\bb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\fb", "a\fb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\nb", "a\nb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\rb", "a\rb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\tb", "a\tb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\vb", "a\vb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("a\\zb", "azb", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Test_Item("\\\'a\\\'", "\'a\'", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("\\\'a", "\'a", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Test_Item("\\\'", "\'", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    Test_Item("\\", "\\", CMD_ITEM_INCOMPLETE_STR),

    Test_Item("a\\\'\\\'\\\\\\ \\a\\b\\f\\n\\r\\t\\v\\z ", "a\'\'\\ \a\b\f\n\r\t\vz ", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    // '\'' + '\"'
    // Not Escaped
    Test_Item("\'\"\"\'", "\"\"", CMD_ITEM_OK),
    // Escaped
    Test_Item("\'\\\"\\\"\'", "\"\"", CMD_ITEM_OK),
};

static const Test_Item TestVector_02[] = {
    Test_Item("\"", "\"", CMD_ITEM_INCOMPLETE_STR),
    Test_Item("\'", "\'", CMD_ITEM_INCOMPLETE_STR),
    Test_Item("\\", "\\", CMD_ITEM_INCOMPLETE_STR),
    Test_Item("a", "a", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
};

static const Test_Item TestVector_03[] = {
    //    Test_Item("", "", CMD_ITEM_EMPTY),
    //    Test_Item("\"<str>\"", "<str>", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    //    Test_Item("\"  <str1>   <str2>    \"", "  <str1>   <str2>    ", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    //    Test_Item("\"\"", "", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    //    Test_Item("\"", "\"", CMD_ITEM_INCOMPLETE_STR),
    //    Test_Item("\"<str>", "\"<str>", CMD_ITEM_INCOMPLETE_STR),
    //    Test_Item("<str>\"", "<str>\"", CMD_ITEM_ERROR),
    Test_Item("FF:FF:FF:FF:FF:FF", "FF:FF:FF:FF:FF:FF", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
    //
    //    Test_Item("<str>'", "<str>'", CMD_ITEM_ERROR),
    //
    //    // Escaped:
    //    Test_Item("\\\"Str\\\"", "\\\"Str\\\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
};

void test1() {
    std::cout << "Test_Cmd_Item_Str_Esc test 1" << std::endl;

    Cmd_Item_Str_Esc v("", "");

    int test_vector_size = sizeof (TestVector) / sizeof (Test_Item);

    int test_count_total = 0;
    int test_count_passed = 0;
    int test_count_failed = 0;

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].Src_Str);
        if (res != TestVector[i].Res || v.Value_Str != TestVector[i].Res_Str) {
            stringstream s_str1;
            stringstream s_str2;

            if (res == TestVector[i].Res) {
                s_str1 << " res=" << Cmd_Item_Valid_Result_Func::To_String(res) << " - Ok";
            } else {
                s_str1 << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
                        << " must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].Res);
            }

            if (v.Value_Str == TestVector[i].Res_Str) {
                s_str2 << " res_str=\'" << v.Value_Str << "\' - Ok";
            } else {
                s_str2 << " res_str=\'" << v.Value_Str << "\'"
                        << " must be \'" << TestVector[i].Res_Str << "\'";
            }

            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Str_Esc) message=test item failed:"
                    << s_str1.str()
                    << s_str2.str()
                    << std::endl;

            test_count_failed++;
        } else {
            std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
            test_count_passed++;
        }
        test_count_total++;
    }

    std::cout << "Result: Total: " << test_count_total << " Passed: " << test_count_passed << " Failed: " << test_count_failed << endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Str_Esc" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Str_Esc)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Str_Esc)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
