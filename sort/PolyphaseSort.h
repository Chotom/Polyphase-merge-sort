/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 **********************************************************************************************************************/
#include "../database/Tape.h"
#include <filesystem>
#include <tuple>

/**
 * Sort given file by polyphase merge method and save it to given output
 */
class PolyphaseSort {
private:
    /// Logger passed in constructor
    Logger* log;

    /// Path to sorted output file
    const char *out_filepath;

    /// Number of tape to Distribute
    int tape_distribution_id;

    /// Offset to read current tape
    int tape_offset;

    /// Number of empty series from init phase
    int dummy_series;

    /// Input tape from file
    std::unique_ptr<Tape> input_tape;

    /// Three tapes to distribute sorted records
    std::unique_ptr<Tape> tapes[3];

    /// Current read records from files
    std::shared_ptr<Record> records[3];

    /**
     * Init distribution from input into two tapes
     */
    void init_phase();

    /**
     * Remove dummy series from tape
     */
    void dummy_phase();

    /**
     * Distribute and merge values from two tapes
     */
    void phase();

    /**
     * tape_offset = (tape_offset + 1) % 2;
     */
    void change_tape_offset();

    /**
     * (tape_distribution_id + tape_offset + 1) % 3;
     */
    auto get_tape_index() -> int;

public:
    /**
     * Constructor of sort class
     * @param in_filepath path to file to sort
     * @param out_filepath path to save sorted file
     * @param block_size
     */
    PolyphaseSort(const char *in_filepath, const char *out_filepath, int block_size, Logger &log);

    /**
     * Sort values
     */
    void sort();

    /**
     * Destructor
     */
    ~PolyphaseSort();
};