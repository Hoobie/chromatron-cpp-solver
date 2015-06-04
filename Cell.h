#ifndef CHROMATRON_CPP_SOLVER_CELL_H
#define CHROMATRON_CPP_SOLVER_CELL_H


#include "color_type.h"

class Cell {
protected:
    unsigned int x;
    unsigned int y;
    color_type color;
    unsigned short direction;
public:
    Cell(unsigned int x, unsigned int y, unsigned short direction, string color);
    Cell();
};


#endif //CHROMATRON_CPP_SOLVER_CELL_H
