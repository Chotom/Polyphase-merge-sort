/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 **********************************************************************************************************************/
#include <iostream>
#include <memory>

/**
 * Storage for single record from file that represents values of triangle (height and base)
 */
class Record {
private:
    ///height of triangle
    int height;

    ///base of triangle
    int base;

public:
    /**
     * Constructor of record
     * @param height of triangle
     * @param base of triangle
     */
    Record(int height, int base);

    /**
     * @return height
     */
    auto get_height() const -> int;

    /**
     * @return base
     */
    auto get_base() const -> int;

    /**
     * @param r other record to compare
     * @return true if current record (triangle) has bigger or equal area
     */
    auto is_area_bigger(std::shared_ptr<Record> &r) const -> bool;

    /**
     * Destructor
     */
    ~Record();
};
