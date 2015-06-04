#ifndef CHROMATRON_CPP_SOLVER_RAY_H
#define CHROMATRON_CPP_SOLVER_RAY_H


#include "Cell.h"

class Ray : public Cell {

public:
    Ray(unsigned int x, unsigned int y, unsigned short direction, const string &color)
            : Cell(x, y, direction, color) { }
};


#endif //CHROMATRON_CPP_SOLVER_RAY_H
