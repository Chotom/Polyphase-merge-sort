#include "Tape.h"


// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Tape::Tape(const char *filepath, int blockSize) {
    this->fileStream = new std::ifstream(filepath, std::fstream::binary);
    this->isFileEnded = false;
    this->blockSize = blockSize;
    this->block = new(std::vector<char>)(this->blockSize, 0);
    this->get_block();
}

Record* Tape::get_record() {
    if (isFileEnded) return nullptr;

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
    auto height = std::stod(tmp_height.data());
    auto base = std::stod(tmp_base.data());

    return new Record(height, base);
}

Tape::~Tape() {
    delete fileStream;
    delete block;
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
void Tape::inc_block() {
    if (++blockIndex == blockSize)
        get_block();
}

void Tape::get_block() {
    if (!fileStream->eof() or isFileEnded) {
        fileStream->read(block->data(), block->size());
        blockSize = fileStream->gcount();
        blockIndex = 0;
    } else {
        isFileEnded = true;
    }
}

void Tape::print_vector(std::vector<char> &v) {
    for (auto &val: v)
        std::cout << val;
    std::cout << std::endl;
}

