/* *********************************************************************************************************************
 * author: Tomasz Czochański
 *
 * Record in file - representation of triangle (height and base of triangle)
 **********************************************************************************************************************/
#include <iostream>

class Record {
private:
    ///height of triangle
    double height;

    ///base of triangle
    double base;

    /**
     * @return calculated area of triangle: (a*h)/2
     */
    auto get_area();
public:
    /**
     * Constructor of record (triangle representation)
     * @param height of triangle
     * @param base of triangle
     */
    Record(double height, double base);

    /**
     * @return height
     */
    double get_height();

    /**
     * @return base
     */
    double get_base();

    /**
     * @param other record to compare
     * @return true if current record (triangle) has bigger area
     */
    auto is_area_bigger(Record *r);

    /**
     * Print values of record
     */
    void print_record();

    /**
     * Destructor
     */
    ~Record();
};
