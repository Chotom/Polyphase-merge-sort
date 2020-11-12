/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Main program
 **********************************************************************************************************************/

#include <iostream>
#include "sort/PolyphaseSort.h"

const char *IN_FILEPATH = "database/input_21";
const char *OUT_FILEPATH = "database/output_21";
const int BLOCK_SIZE = 8;

int main() {

    auto ps = new PolyphaseSort(IN_FILEPATH, OUT_FILEPATH, BLOCK_SIZE);
    ps->sort();
    delete ps;

    return 0;
}