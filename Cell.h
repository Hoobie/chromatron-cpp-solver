#ifndef CHROMATRON_CPP_SOLVER_CELL_H
#define CHROMATRON_CPP_SOLVER_CELL_H


#include <vector>
#include "color_type.h"
#include "cell_type.h"

struct ray_type {
    unsigned short direction;
    color_type color;

    bool operator==(ray_type r) {
        return (direction == r.direction && color == r.color);
    }
};

class Cell {
    cell_type type;
    unsigned int x;
    unsigned int y;
    color_type color;
    /*
     * directions (from laser definition):
     * _________
     * |7  6  5|
     * |0  x  4|
     * |1  2  3|
     * ---------
     */
    unsigned short direction;
    vector<ray_type> rays;
public:
    Cell();
    Cell(cell_type type, unsigned int x, unsigned int y, unsigned short direction, color_type color);
    Cell(string type, unsigned int x, unsigned int y, unsigned short direction, string color);
    Cell clone() const { return Cell(*this); }
    cell_type getCellType();
    void setType(cell_type type);
    unsigned int getX();
    void setX(unsigned int x);
    unsigned int getY();
    void setY(unsigned int y);
    color_type getColor();
    void setColor(color_type color);
    unsigned short getDirection();
    void setDirection(unsigned short direction);
    friend ostream& operator<<(ostream& os, const Cell& c);
    void addRay(ray_type ray);
    vector<ray_type> getRays();
};


#endif //CHROMATRON_CPP_SOLVER_CELL_H
