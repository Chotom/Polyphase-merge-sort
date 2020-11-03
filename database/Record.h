/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Record in file - representation of triangle (height and base of triangle)
 **********************************************************************************************************************/
#include <iostream>

class Record {
private:
    ///height of triangle
    int height;

    ///base of triangle
    int base;

    /**
     * @return calculated area of triangle: (a*h)/2
     */
    auto get_area() const;

public:
    /**
     * Constructor of record (triangle representation)
     * @param height of triangle
     * @param base of triangle
     */
    Record(int height, int base);

    /**
     * @return height
     */
    int get_height() const;

    /**
     * @return base
     */
    int get_base() const;

    /**
     * @param other record to compare
     * @return true if current record (triangle) has bigger area
     */
    bool is_area_bigger(Record *r);

    /**
     * Print values of record
     */
    void print_record();

    /**
     * Destructor
     */
    ~Record();
};
