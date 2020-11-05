#include "Record.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Record::Record(int height, int base) {
    this->height = height;
    this->base = base;
}

auto Record::get_height() -> int {
    return height;
}

auto Record::get_base() -> int {
    return base;
}

auto Record::is_area_bigger(std::shared_ptr<Record> &r) -> bool {
    return (r->get_base() * r->get_height()) <= (get_base() * get_height());
}

Record::~Record() = default;

// LOGS ----------------------------------------------------------------------------------------------------------------
void Record::print_record() {
    std::cout << "Triangle values: " << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "base: " << base << std::endl;
}

