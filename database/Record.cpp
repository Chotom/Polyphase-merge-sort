#include "Record.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Record::Record(double height, double base) {
    this->height = height;
    this->base = base;
}

double Record::get_height() {
    return height;
}

double Record::get_base() {
    return this->base;
}

auto Record::get_area() {
    return height * base / 2;
}

// PRIVATE METHODS -----------------------------------------------------------------------------------------------------
auto Record::is_area_bigger(Record *r) {
    if (r->get_area() < this->get_area())
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

Record::~Record() {}