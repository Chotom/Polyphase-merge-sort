#include "Logger.h"

Logger::Logger(const char *logger_name, int logger_lever) {
    this->logger_name = logger_name;
    this->logger_lever = logger_lever;

}

void Logger::inc_phase_number() {
    phase_number++;
}

void Logger::inc_inout_number() {
    inout_number++;
}

Logger::~Logger() {}

// ERROR LEVEL ----------------------------------------------------------------------------------------------------------
void Logger::print_args_error() {
    std::cout << "[ERROR] Missing arguments! Required: input=, output=, records=, block=" << std::endl;
}

void Logger::print_save_output_error(const char *filepath) {
    std::cout << "[ERROR] Error while saving tape to given output path: " << filepath << std::endl;
}


// INFO LEVEL ----------------------------------------------------------------------------------------------------------
void Logger::print_dummy_series_info(int dummy_series_number) {
    if (logger_lever >= 1) {
        std::cout << "[INFO] Number of dummy series: " << dummy_series_number << std::endl;
    }
}

void Logger::print_series_info(int fib0, int fib1) {
    if (logger_lever >= 1) {
        std::cout << "[INFO] Number of series on tapes: " << fib0 << " | " << fib1 << std::endl;
    }
}

void Logger::print_phase_number() {
    if (logger_lever >= 1) {
        std::cout << "[INFO] Number of phases in sort: " << phase_number << std::endl;
    }
}

void Logger::print_theoretic_phase_number(long long records_number) {
    if (logger_lever >= 1) {
        std::cout << "[INFO] Theoretical number of phases: " << std::ceil(1.45 * log2(records_number / 2)) << std::endl;
    }
}

void Logger::print_inout_number() {
    if (logger_lever >= 1) {
        std::cout << "[INFO] Number of read/write in sort: " << inout_number << std::endl;
    }
}

void Logger::print_theoretic_inout_number(long long records_number, long long file_size, int block_size) {
    if (logger_lever >= 1) {
        //R = file_size / records_number;
        //b = B / R = block_size * records_number / file_size;
        std::cout << "[INFO] Theoretical number of read/write: ";
        std::cout << (int) std::ceil(2 * file_size * (1.04 * log2(records_number / 2) + 1) / block_size) << std::endl;
    }
}

void Logger::print_line() {
    if (logger_lever >= 1) {
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    }
}


// DEBUG LEVEL ---------------------------------------------------------------------------------------------------------
void Logger::print_file_debug(const char *filepath) {
    std::ifstream f(filepath);

    if (logger_lever >= 2 and f.is_open()) {
        std::cout << "[DEBUG] Content of " << filepath << ":" << std::endl;
        std::cout << f.rdbuf() << std::endl;
        f.close();
    }
}

void Logger::print_distribution_tape_number_debug(int d) {
    if (logger_lever >= 2) {
        std::cout << "[DEBUG] Distribute series to tape" << d << std::endl;
    }
}


