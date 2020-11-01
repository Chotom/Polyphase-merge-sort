/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Main program
 **********************************************************************************************************************/

#include <iostream>
#include "database/Tape.h"

int main(){
    auto char_array = "./database/input.txt";
    auto char_array_out = "./database/output.txt";
    Tape *tape1 = new Tape(char_array, 8);
    Tape *tape2= new Tape(char_array_out, 16);

    //some read and save file test
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);
    if (auto r = tape1->get_record(); r != nullptr) tape2->save_record(r);

    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);
    if (auto r = tape2->get_record(); r != nullptr) tape1->save_record(r);


    // Closing
    std::cout << "Closing..." << std::endl;
    tape2->close_tape();
    tape1->close_tape();
    delete tape2;
    delete tape1;

    return 0;
}