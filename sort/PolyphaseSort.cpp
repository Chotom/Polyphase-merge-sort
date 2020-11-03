#include "PolyphaseSort.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
PolyphaseSort::PolyphaseSort(int blockSize) {
    //init tapes
    this->tapes[0] = new Tape("database/tapes/tape1.txt", blockSize);
    this->tapes[1] = new Tape("database/tapes/tape2.txt", blockSize);
    this->tapes[2] = new Tape("database/tapes/tape3.txt", blockSize);
    this->tapeDistributionId = 2;
    this->tapeOffset = 0;
    this->dummySeries = 0;

    //clear records
    this->records[0] = nullptr;
    this->records[1] = nullptr;
    this->records[2] = nullptr;
}

void PolyphaseSort::sort() {
    init_phase();
    dummy_phase();
    while (records[0] != nullptr or records[1] != nullptr or records[2] != nullptr)
        phase();
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
void PolyphaseSort::init_phase() {
    // Init values
    int fib0 = 0, fib1 = 0, seriesCounter = 0;
    auto tapeSaveId = get_tape_index();

    // Init record
    Record *r, *prevR = tapes[tapeDistributionId]->get_record();
    tapes[tapeSaveId]->save_record(prevR);

    // Read all records from tape
    while ((r = tapes[tapeDistributionId]->get_record()) != nullptr) {
        // Series ended
        if (!r->is_area_bigger(prevR)) ++seriesCounter;

        if (seriesCounter >= fib1) {
            // Save previous record in tape
            records[tapeSaveId] = prevR;

            // Change tape
            change_tape_offset();
            tapeSaveId = get_tape_index();

            // Does series merge with previous record in tape
            seriesCounter = (records[tapeSaveId] != nullptr and r->is_area_bigger(records[tapeSaveId])) ? -1 : 0;

            // Calc Fibonacci
            std::tie(fib0, fib1) = (fib1 == 0) ? std::make_tuple(0, 1) : std::make_tuple(fib1, fib0 + fib1);
        }

        // Save record to tape
        prevR = r;
        tapes[tapeSaveId]->save_record(prevR);
    }
    dummySeries = fib1 - seriesCounter - 1;
    change_tape_offset();

    // Clear
    records[0] = nullptr;
    records[1] = nullptr;
    records[2] = nullptr;
    delete prevR;
    delete r;
}


void PolyphaseSort::dummy_phase() {
    // Init values
    int inputIds[2] = {(tapeDistributionId + 1) % 3, (tapeDistributionId + 2) % 3};

    // Init records
    records[inputIds[0]] = records[inputIds[0]] == nullptr ? tapes[inputIds[0]]->get_record() : records[inputIds[0]];
    records[inputIds[1]] = records[inputIds[1]] == nullptr ? tapes[inputIds[1]]->get_record() : records[inputIds[1]];

    // Read dummy series
    Record *r;
    while (dummySeries) {
        tapes[tapeDistributionId]->save_record(records[inputIds[tapeOffset]]);

        r = tapes[inputIds[tapeOffset]]->get_record();
        if (!r->is_area_bigger(records[inputIds[tapeOffset]]))
            --dummySeries;
        records[inputIds[tapeOffset]] = r;
    }
}

void PolyphaseSort::phase() {
    // Init values
    bool endOfSeries[2] = {false, false}, endOfTape = false;
    int inputIds[2] = {(tapeDistributionId + 1) % 3, (tapeDistributionId + 2) % 3};

    // Init records
    records[inputIds[0]] = records[inputIds[0]] == nullptr ? tapes[inputIds[0]]->get_record() : records[inputIds[0]];
    records[inputIds[1]] = records[inputIds[1]] == nullptr ? tapes[inputIds[1]]->get_record() : records[inputIds[1]];
    tapeOffset = (records[inputIds[0]]->is_area_bigger(records[inputIds[1]])) ? 1 : 0;

    // Read series and one tape up to end
    Record *r;
    while (!endOfTape or !(endOfSeries[0] and endOfSeries[1])) {
        // Init new series
        if (!endOfTape and endOfSeries[0] and endOfSeries[1]) {
            std::tie(endOfSeries[0], endOfSeries[1]) = std::make_tuple(false, false);
            tapeOffset = (records[inputIds[0]]->is_area_bigger(records[inputIds[1]])) ? 1 : 0;
        }

        tapes[tapeDistributionId]->save_record(records[inputIds[tapeOffset]]);

        if (r = tapes[inputIds[tapeOffset]]->get_record(); r == nullptr) {
            // End of tape
            endOfTape = true;
            endOfSeries[tapeOffset] = true;
            records[inputIds[tapeOffset]] = nullptr;
            if (!(endOfSeries[0] and endOfSeries[1]))
                change_tape_offset();
        } else {
            // Handle record
            if (!r->is_area_bigger(records[inputIds[tapeOffset]])) {
                // End of series in current tape
                records[inputIds[tapeOffset]] = r;
                endOfSeries[tapeOffset] = true;
                change_tape_offset();
            } else if (auto t2 = (tapeOffset + 1) % 2; !endOfSeries[t2] and r->is_area_bigger(records[inputIds[t2]])) {
                // Swap second tape if available
                records[inputIds[tapeOffset]] = r;
                change_tape_offset();
            } else {
                // Stay on current tape
                records[inputIds[tapeOffset]] = r;
            }
        }
    }
    // Switch distribution tape
    tapeDistributionId = inputIds[tapeOffset];
    records[tapeDistributionId] = nullptr;
}

void PolyphaseSort::change_tape_offset() {
    tapeOffset = (tapeOffset + 1) % 2;
}

int PolyphaseSort::get_tape_index() {
    return (tapeDistributionId + tapeOffset + 1) % 3;
}

PolyphaseSort::~PolyphaseSort() {
    tapes[0]->close_tape();
    tapes[1]->close_tape();
    tapes[2]->close_tape();
    delete tapes[0];
    delete tapes[1];
    delete tapes[2];
    delete records[0];
    delete records[1];
    delete records[2];
}