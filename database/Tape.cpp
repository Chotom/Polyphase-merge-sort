#include "Tape.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Tape::Tape(const char *filepath, int block_size) {
    this->filepath = filepath;
    this->block_size = block_size;
    this->block_index = 0;
    this->block.resize(this->block_size, 0);

    this->file_in_stream = nullptr;
    this->file_out_stream = nullptr;
}

auto Tape::get_record() -> std::shared_ptr<Record> {
    // Create input handler to file
    if (file_in_stream == nullptr) init_read();

    // Return dummy record
    if (is_input_ended and block_index == block_size) return nullptr;

    std::string tmp_height, tmp_base;
    // Read first value to tmp string from buffer/block
    while (block[block_index] != VALUE_SEP) {
        tmp_height.push_back(block[block_index]);
        inc_block();
    }
    inc_block();

    // Read second value to tmp vector from buffer/block
    while (block[block_index] != RECORD_SEP) {
        tmp_base.push_back(block[block_index]);
        inc_block();
    }
    inc_block();

    // Cast string to int
    auto height = std::stoi(tmp_height);
    auto base = std::stoi(tmp_base);

    return  std::make_shared<Record>(height, base);
}

void Tape::save_record(const std::shared_ptr<Record>& r) {
    // Create output handler to file
    if (file_out_stream == nullptr) init_save();

    auto tmp_height = std::to_string(r->get_height());
    auto tmp_base = std::to_string(r->get_base());

    // Save first value from tmp str to buffer/block
    for (auto i : tmp_height) {
        block[block_index] = i;
        inc_block();
    }
    block[block_index] = VALUE_SEP;
    inc_block();

    // Save second value from tmp str to buffer/block
    for (auto i : tmp_base) {
        block[block_index] = i;
        inc_block();
    }
    block[block_index] = RECORD_SEP;
    inc_block();
}

void Tape::close_tape() {
    if (file_out_stream != nullptr) {
        // Save out stream
        block_size = block_index;
        save_block();

        // Clear out stream
        file_out_stream->close();
        delete file_out_stream;
        file_out_stream = nullptr;
    }
    else if (file_in_stream != nullptr) {
        // Clear in stream
        file_in_stream->close();
        delete file_in_stream;
        file_in_stream = nullptr;
        is_input_ended = false;
    }
    //reset block
    block_index = 0;
    block_size = block.size();
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
void Tape::init_read() {
    this->close_tape();

    // Open in stream
    this->file_in_stream = new std::ifstream(filepath, std::ifstream::binary);
    this->get_block();
}

void Tape::init_save() {
    this->close_tape();

    // Open out stream
    this->file_out_stream = new std::ofstream(filepath, std::ofstream::binary);
}

void Tape::inc_block() {
    if (++block_index == block_size) {
        block_index = 0;
        if (file_in_stream != nullptr)
            get_block();
        else if (file_out_stream != nullptr)
            save_block();
    }
}

void Tape::get_block() {
    if (file_in_stream != nullptr and !is_input_ended) {
        file_in_stream->read(block.data(), block.size());
        if (file_in_stream->eof()) is_input_ended = true;
        block_size = file_in_stream->gcount();
    } else {
        block_size = 0;
    }
}

void Tape::save_block() {
    if (file_out_stream != nullptr)
        file_out_stream->write(block.data(), block_size);
}

Tape::~Tape() {
    close_tape();
}

// LOGS ----------------------------------------------------------------------------------------------------------------
void Tape::print_vector(std::vector<char> &v) {
    for (auto &val: v)
        std::cout << val;
    std::cout << std::endl;
}


