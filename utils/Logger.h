/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Logger class to log all required information for this project
 **********************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <cmath>

class Logger {
private:
    const char* logger_name;
    int logger_lever;
    int phase_number = 0;
    int inout_number = 0;

public:
    /**
     *
     * @param logger_name
     * @param logger_lever
     */
    Logger(const char* logger_name, int logger_lever);

    ~Logger();

    void inc_inout_number();
    void inc_phase_number();
    void print_line();

    void print_args_error();
    void print_save_output_error(const char *filepath);

    /**
     * @param dummy_series_number
     */
    void print_dummy_series_info(int dummy_series_number);

    /**
     * @param fib0
     * @param fib1
     */
    void print_series_info(int fib0, int fib1);

    /**
     * Write in output given number of phases
     * @param phase_number
     */
    void print_phase_number();

    /**
     * Write in output given number of read/write operations
     * @param inout_number
     */
    void print_inout_number();

    /**
     * Write in output calculated, expected number of series
     * @param series_number number of series saved in file
     */
    void print_theoretic_phase_number(long long records_number);

    /**
     * Write in output calculated, expected number of write/read operation to files
     * @param record_number number of records in file
     * @param block_size size of reading/write block
     */
    void print_theoretic_inout_number(long long records_number, long long file_size, int block_size);

    /**
     * Print content of file
     * @param filepath
     * @return
     */
    void print_file_debug(const char* filepath);

    /**
     * @param number of tape
     */
    void print_distribution_tape_number_debug(int d);
};
