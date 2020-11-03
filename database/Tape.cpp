#include "Tape.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Tape::Tape(const char *filepath, int blockSize) {
    this->filepath = filepath;
    this->blockSize = blockSize;
    this->blockIndex = 0;
    this->block = new(std::vector<char>)(this->blockSize, 0);

    this->fileInStream = nullptr;
    this->fileOutStream = nullptr;
}

Record *Tape::get_record() {
    // Create input handler to file
    if (fileInStream == nullptr) init_read();

    // Return dummy record
    if (isInFileEnded) return nullptr;

    std::vector<char> tmp_height, tmp_base;

    // Read first value to tmp vector from buffer/block
    while (block->at(blockIndex) != VALUE_SEP) {
        tmp_height.push_back(block->at(blockIndex));
        this->inc_block();
    }
    this->inc_block();

    // Read second value to tmp vector from buffer/block
    while (block->at(blockIndex) != RECORD_SEP) {
        tmp_base.push_back(block->at(blockIndex));
        this->inc_block();
    }
    this->inc_block();

    // Cast string to double
    auto height = std::stoi(tmp_height.data());
    auto base = std::stoi(tmp_base.data());

    return new Record(height, base);
}

void Tape::save_record(Record *r) {
    // Create output handler to file
    if (fileOutStream == nullptr) init_save();

    auto tmp_height = std::to_string(r->get_height());
    auto tmp_base = std::to_string(r->get_base());

    // Save first value from tmp str to buffer/block
    for (auto i : tmp_height) {
        block->at(blockIndex) = i;
        this->inc_block();
    }
    block->at(blockIndex) = VALUE_SEP;
    this->inc_block();

    // Save first second from tmp str to buffer/block
    for (auto i : tmp_base) {
        block->at(blockIndex) = i;
        this->inc_block();
    }
    block->at(blockIndex) = RECORD_SEP;
    this->inc_block();
}

void Tape::close_tape() {
    if (fileOutStream != nullptr) {
        // Save out stream
        blockSize = blockIndex;
        save_block();

        // Clear out stream
        fileOutStream->close();
        delete fileOutStream;
        this->fileOutStream = nullptr;
    }
    else if (fileInStream != nullptr) {
        // Clear in stream
        fileInStream->close();
        delete fileInStream;
        this->fileInStream = nullptr;
        this->isInFileEnded = false;
    }

    this->blockIndex = 0;
    this->blockSize = block->size();
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
void Tape::init_read() {
    this->close_tape();

    // Open in stream
    this->fileInStream = new std::ifstream(filepath, std::ifstream::binary);
    this->get_block();
}

void Tape::init_save() {
    this->close_tape();

    // Open out stream
    this->fileOutStream = new std::ofstream(filepath, std::ofstream::binary);
}

void Tape::inc_block() {
    if (++blockIndex == blockSize) {
        blockIndex = 0;
        if (fileInStream != nullptr)
            get_block();
        else if (fileOutStream != nullptr)
            save_block();
    }
}

void Tape::get_block() {
    if (fileInStream != nullptr and !isInFileEnded) {
        fileInStream->read(block->data(), block->size());
        blockSize = fileInStream->gcount();
        if (fileInStream->eof()) isInFileEnded = true;
    }
}

void Tape::save_block() {
    if (fileOutStream != nullptr)
        fileOutStream->write(block->data(), blockSize);
}

Tape::~Tape() {
    delete fileInStream;
    delete fileOutStream;
    delete block;
}

// LOGS ----------------------------------------------------------------------------------------------------------------
void Tape::print_vector(std::vector<char> &v) {
    for (auto &val: v)
        std::cout << val;
    std::cout << std::endl;
}


