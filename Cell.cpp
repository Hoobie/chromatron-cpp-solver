#include "Cell.h"

Cell::Cell(unsigned int x, unsigned int y, unsigned short direction, string color) {
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = toColor(color);
}

Cell::Cell() {
}
