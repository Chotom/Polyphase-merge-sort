/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Main program
 **********************************************************************************************************************/

#include <iostream>
#include <filesystem>
#include "sort/PolyphaseSort.h"

const int LOGGER_LEVEL = 1;

/**
 * @param argc number of arguments
 * @param argv:
 * - input= path to input file,
 * - output= path to sorted result,
 * - records= number of records in given file,
 * - block= block size in bytes
 */
int main(int argc, char **argv) {
    // Init
    Logger log("polyphase-sort", LOGGER_LEVEL);
    const char *in_filepath, *out_filepath;
    int number_of_records, block_size;

    // Handle args
    if (argc == 5) {
        in_filepath = argv[1];
        out_filepath = argv[2];
        number_of_records = std::stoi(argv[3]);
        block_size = std::stoi(argv[4]);
    } else {
        log.print_args_error();
        return 1;
    }

    // Print content of file
    log.print_line();
    log.print_file_debug(in_filepath);

    // Sort file
    auto ps = new PolyphaseSort(in_filepath, out_filepath, block_size, log);
    ps->sort();
    delete ps;

    // Print information after sort
    log.print_file_debug(out_filepath);
    log.print_line();
    log.print_phase_number();
    log.print_theoretic_phase_number(number_of_records);
    log.print_inout_number();
    log.print_theoretic_inout_number(number_of_records, std::filesystem::file_size(in_filepath), block_size);

    return 0;
}