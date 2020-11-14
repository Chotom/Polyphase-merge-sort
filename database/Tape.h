/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 **********************************************************************************************************************/
#include <fstream>
#include <vector>
#include "Record.h"
#include "../utils/Logger.h"

/**
 * Simulate tape in polyphase merge sort.
 * Stores input and output handlers to files, provide data block read/write mode
 */
class Tape {
private:
    const char VALUE_SEP = ',';
    const char RECORD_SEP = ';';

    /// Logger passed in constructor
    Logger *log;

    ///Tape path
    const char *filepath;

    ///Size of read block
    int block_size;

    ///Point at char in block/buffer
    int block_index;

    ///Buffer for read/save data
    std::vector<char> block;

    ///Input handler to given file
    std::ifstream file_in_stream;

    ///Output handler to given file
    std::ofstream file_out_stream;

    /**
     * Initiate tape to read from file
     */
    void init_read();

    /**
     * Initiate tape to save to file
     */
    void init_save();

    /**
     * Increment block_index and check if next block/page needs to be read/saved
     */
    void inc_block();

    /**
     * Read next block of data up to block size
     */
    void get_block();

    /**
     * Save next block of data up to block size
     */
    void save_block();

    /**
     * Close all connection in tape
     */
    void close_tape();

public:
    /**
     * Constructor of tape:
     *  set filename,
     *  initiate data block
     * @param filepath to tape
     * @param block_size in bytes
     */
    Tape(const char *filepath, int block_size, Logger &log);

    /**
     * Initiate read mode if necessary and read values from file
     * @return next record object as smart ptr or nullptr if file ended
     */
    auto get_record() -> std::shared_ptr<Record>;

    /**
     * Save record to file
     * @param r record to save in file
     */
    void save_record(const std::shared_ptr<Record> &r);

    /**
     * Print content of tape after distribute
     */
    void print_tape();

    /**
     * Destructor
     */
    ~Tape();
};
