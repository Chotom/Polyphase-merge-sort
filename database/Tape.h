/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Input/Output handler class - simulate tape in polyphase merge sort
 **********************************************************************************************************************/
#include <fstream>
#include <vector>
#include "Record.h"

class Tape {
private:
    const char VALUE_SEP = ',';
    const char RECORD_SEP = ';';

    ///Tape path
    const char *filepath;

    ///Size of read block
    int blockSize;

    ///Input handler to given file
    std::ifstream *fileInStream;

    ///Output handler to given file
    std::ofstream *fileOutStream;

    ///Does end of file appeared
    bool isInFileEnded;

    ///Point at char in block/buffer
    int blockIndex;

    ///Buffer for read/save data
    std::vector<char> *block;

    /**
     * Initiate tape to read from file
     */
    void init_read();

    /**
     * Initiate tape to save to file
     */
    void init_save();

    /**
     * Increment blockIndex and check if next block/page needs to be saved
     */
    void inc_block();

    /**
     * Read next block of data up to given size
     */
    void get_block();

    /**
     * Save next block of data up to given size
     */
    void save_block();

    /**
     * Print string saved in vector
     */
    void print_vector(std::vector<char> &);

public:
    /**
     * Simulate tape in polyphase merge sort:
     *  open file stream
     *  set blockSize
     *  create empty block
     *  starts with read mode
     * @param filepath to tape
     * @param blockSize in bytes
     */
    Tape(const char *filepath, int blockSize);

    /**
     * Destructor
     */
    ~Tape();

    /**
     * Return Record object:
     *  save values from block into tmp vector<char>
     *  cast vector<char> to double and return created object
     * @return next record from file or null if file ended
     */
    Record *get_record();

    /**
     * Save record to file:
     *  cast value from double to str
     *  save it to block
     * @param r record to save in file
     */
    void save_record(Record *r);

    /**
     * Close all connection in tape
     */
    void close_tape();
};
