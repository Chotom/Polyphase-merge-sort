/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Main program
 **********************************************************************************************************************/

#include <iostream>
#include "sort/PolyphaseSort.h"

int main() {
    auto ps = new PolyphaseSort(8);
    ps->sort();
    delete ps;

    return 0;
}