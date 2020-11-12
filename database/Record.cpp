#include "Record.h"

// PUBLIC METHODS ------------------------------------------------------------------------------------------------------
Record::Record(int height, int base) {
    this->height = height;
    this->base = base;
}

auto Record::get_height() const -> int {
    return height;
}

auto Record::get_base() const -> int {
    return base;
}

auto Record::is_area_bigger(std::shared_ptr<Record> &r) const -> bool {
    return (r->get_base() * r->get_height()) <= (get_base() * get_height());
}

Record::~Record() = default;
