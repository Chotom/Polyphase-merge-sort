/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Main program
 **********************************************************************************************************************/

#include <iostream>
#include "database/Tape.h"

int main(){
    auto char_array = "/home/tomasz/Documents/repo/sbd_projekt/Polyphase-merge-sort/database/input.txt";
    Tape *tape1 = new Tape(char_array, 8);

    //some read file test
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();
    if (auto r = tape1->get_record(); r != nullptr) r->print_record();

    return 0;
}