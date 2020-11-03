#include "Record.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Record::Record(int height, int base) {
    this->height = height;
    this->base = base;
}

int Record::get_height() const {
    return height;
}

int Record::get_base() const {
    return base;
}

auto Record::get_area() const {
    return (double)(height * base) / 2;
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
bool Record::is_area_bigger(Record *r) {
    if (r->get_area() <= this->get_area())
        return true;
    return false;
}

// LOGS ----------------------------------------------------------------------------------------------------------------
void Record::print_record() {
    std::cout << "Triangle values: " << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "base: " << base << std::endl;
    std::cout << "area: " << this->get_area() << std::endl << std::endl;
}

Record::~Record() = default;