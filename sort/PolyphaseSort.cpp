#include "PolyphaseSort.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
PolyphaseSort::PolyphaseSort(int block_size) {
    //init tapes
    this->tapes[0] = new Tape("database/tapes/tape1.txt", block_size);
    this->tapes[1] = new Tape("database/tapes/tape2.txt", block_size);
    this->tapes[2] = new Tape("database/tapes/tape3.txt", block_size);
    this->tape_distribution_id = 2;
    this->tape_offset = 0;
    this->dummy_series = 0;

    //clear records
    this->records[0] = nullptr;
    this->records[1] = nullptr;
    this->records[2] = nullptr;
}

void PolyphaseSort::sort() {
    init_phase();
    dummy_phase();
    while (records[0] != nullptr or records[1] != nullptr or records[2] != nullptr) phase();
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
void PolyphaseSort::init_phase() {
    // Init values
    int fib0 = 0, fib1 = 0, series_counter = 0;
    auto tape_save_id = get_tape_index();

    // Init record
    std::shared_ptr<Record> r, prev_r = tapes[tape_distribution_id]->get_record();
    tapes[tape_save_id]->save_record(prev_r);

    // Read all records from tape
    while ((r = tapes[tape_distribution_id]->get_record()) != nullptr) {
        // Series ended
        if (!r->is_area_bigger(prev_r)) ++series_counter;

        if (series_counter >= fib1) {
            // Save previous record in tape
            records[tape_save_id] = prev_r;

            // Change tape
            change_tape_offset();
            tape_save_id = get_tape_index();

            // Does series merge with previous record in tape
            series_counter = (records[tape_save_id] != nullptr and r->is_area_bigger(records[tape_save_id])) ? -1 : 0;

            // Calc Fibonacci
            std::tie(fib0, fib1) = (fib1 == 0) ? std::make_tuple(0, 1) : std::make_tuple(fib1, fib0 + fib1);
        }

        // Save record to tape
        tapes[tape_save_id]->save_record(r);
        prev_r = r;
    }
    dummy_series = fib1 - series_counter - 1;
    change_tape_offset();

    // Clear
    records[0] = nullptr;
    records[1] = nullptr;
    records[2] = nullptr;
}


void PolyphaseSort::dummy_phase() {
    // Init values
    int input_ids[2] = {(tape_distribution_id + 1) % 3, (tape_distribution_id + 2) % 3};

    // Init records
    records[input_ids[0]] = records[input_ids[0]] == nullptr ? tapes[input_ids[0]]->get_record() : records[input_ids[0]];
    records[input_ids[1]] = records[input_ids[1]] == nullptr ? tapes[input_ids[1]]->get_record() : records[input_ids[1]];

    // Read dummy series
    std::shared_ptr<Record> r;
    while (dummy_series) {
        tapes[tape_distribution_id]->save_record(records[input_ids[tape_offset]]);

        r = tapes[input_ids[tape_offset]]->get_record();
        if (!r->is_area_bigger(records[input_ids[tape_offset]]))
            --dummy_series;
        records[input_ids[tape_offset]] = r;
    }
}

void PolyphaseSort::phase() {
    // Init values
    bool is_series_end[2] = {false, false}, is_tape_end = false;
    int input_ids[2] = {(tape_distribution_id + 1) % 3, (tape_distribution_id + 2) % 3};

    // Init records
    records[input_ids[0]] = records[input_ids[0]] == nullptr ? tapes[input_ids[0]]->get_record() : records[input_ids[0]];
    records[input_ids[1]] = records[input_ids[1]] == nullptr ? tapes[input_ids[1]]->get_record() : records[input_ids[1]];
    tape_offset = (records[input_ids[0]]->is_area_bigger(records[input_ids[1]])) ? 1 : 0;

    // Read series and one tape up to end
    std::shared_ptr<Record> r;
    while (!is_tape_end or !(is_series_end[0] and is_series_end[1])) {
        // Init new series
        if (!is_tape_end and is_series_end[0] and is_series_end[1]) {
            std::tie(is_series_end[0], is_series_end[1]) = std::make_tuple(false, false);
            tape_offset = (records[input_ids[0]]->is_area_bigger(records[input_ids[1]])) ? 1 : 0;
        }

        tapes[tape_distribution_id]->save_record(records[input_ids[tape_offset]]);

        // End of tape
        if (r = tapes[input_ids[tape_offset]]->get_record(); r == nullptr) {
            is_tape_end = true;
            is_series_end[tape_offset] = true;
            records[input_ids[tape_offset]] = nullptr;
            if (!(is_series_end[0] and is_series_end[1]))
                change_tape_offset();
            continue;
        }
        // Handle record
        if (!r->is_area_bigger(records[input_ids[tape_offset]])) {
            // End of series in current tape
            records[input_ids[tape_offset]] = r;
            is_series_end[tape_offset] = true;
            change_tape_offset();
        } else if (auto t2 = (tape_offset + 1) % 2; !is_series_end[t2] and r->is_area_bigger(records[input_ids[t2]])) {
            // Swap second tape if available
            records[input_ids[tape_offset]] = r;
            change_tape_offset();
        } else {
            // Stay on current tape
            records[input_ids[tape_offset]] = r;
        }
    }
    // Switch distribution tape
    tape_distribution_id = input_ids[tape_offset];
    records[tape_distribution_id] = nullptr;
}

void PolyphaseSort::change_tape_offset() {
    tape_offset = (tape_offset + 1) % 2;
}

int PolyphaseSort::get_tape_index() {
    return (tape_distribution_id + tape_offset + 1) % 3;
}

PolyphaseSort::~PolyphaseSort() {
    delete tapes[0];
    delete tapes[1];
    delete tapes[2];
}