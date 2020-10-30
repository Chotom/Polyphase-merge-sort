/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Input/Output handler class - simulate tape in polyphase merge sort
 **********************************************************************************************************************/
#include <fstream>
#include <vector>
#include "Record.h"

class Record;

class Tape {
    const char VALUE_SEP=',';
    const char RECORD_SEP=';';
private:
    ///Handler to given file
    std::ifstream* fileStream;

    ///Does end of file appeared
    bool isFileEnded;

    ///Size of read block
    int blockSize;

    ///Point at char in block/buffer
    int blockIndex;

    ///Buffer for read data
    std::vector<char>* block;

    /**
     * Increment blockIndex and check if next block/page needs to be loaded
     */
    void inc_block();

    /**
     * Read next block of data up to given size
     */
    void get_block();

    /**
     * Print string saved in vector
     */
    void print_vector(std::vector<char>&);

public:
    /**
     * Simulate tape in polyphase merge sort:
     *  open file stream
     *  set blockSize
     *  create empty block
     * @param filepath
     * @param blockSize in bytes
     */
    Tape(const char *filepath, int blockSize);

    /**
     * Destructor
     */
    ~Tape();

    /**
     * Save values from block into tmp vector<char>
     *  cast vector<char> to double and create Record object
     * @return next record from file
     */
    Record* get_record();

    void save_record(Record *r);
};
