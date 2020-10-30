#include "Record.h"


Record::Record(double height, double base) {
    this->height = height;
    this->base = base;
}

auto Record::get_area() {
    return height * base / 2;
}

auto Record::is_area_bigger(Record *r) {
    if (r->get_area() < this->get_area())
        return true;
    return false;
}

void Record::print_record() {
    std::cout << "Triangle values: " << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "base: " << base << std::endl;
    std::cout << "area: " << this->get_area() << std::endl << std::endl;
}

Record::~Record() {}