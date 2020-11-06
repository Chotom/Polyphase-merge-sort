/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Input/Output handler class - simulate tape in polyphase merge sort
 **********************************************************************************************************************/
#include "../database/Tape.h"
#include <tuple>

/**
 * Sort given file by polyphase merge method
 */
class PolyphaseSort {
private:
    /// Number of tape to Distribute
    int tape_distribution_id;

    /// Offset to read current tape
    int tape_offset;

    /// Number of empty series from init phase
    int dummy_series;

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
    int get_tape_index();

public:
    explicit PolyphaseSort(int block_size);

    /**
     * Sort values
     */
    void sort();

    /**
     * Destructor
     */
    ~PolyphaseSort();
};