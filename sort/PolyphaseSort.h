/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Input/Output handler class - simulate tape in polyphase merge sort
 **********************************************************************************************************************/
#include "../database/Tape.h"
#include <tuple>

class PolyphaseSort {
private:
    /// Number of tape to Distribute
    int tapeDistributionId;

    /// Offset to read current tape
    int tapeOffset;

    /// Number of empty series from init phase
    int dummySeries;

    /// Three tapes
    Tape *tapes[3];

    /// Current read records from files
    Record *records[3];

    /**
     * Init distribution from input into two tapes
     */
    void init_phase();

    /**
     * Distribute normal series from one to tape
     */
    void dummy_phase();

    /**
     * Distribute and merge values from two tapes
     */
    void phase();

    /**
     * tapeOffset = (tapeOffset + 1) % 2;
     */
    void change_tape_offset();

    /**
     * (tapeDistributionId + tapeOffset + 1) % 3;
     */
    int get_tape_index();

public:
    PolyphaseSort(int blockSize);

    /**
     * Sort values
     */
    void sort();


    /**
     * Destructor
     */
    ~PolyphaseSort();
};