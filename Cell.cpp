#include <iostream>
#include "Cell.h"

Cell::Cell() {
    this->type = NONE;
}

Cell::Cell(cell_type type, unsigned int x, unsigned int y, unsigned short direction, color_type color) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = color;
}

Cell::Cell(string type, unsigned int x, unsigned int y, unsigned short direction, string color) : Cell(toCellType(type), x, y, direction, toColor(color))
{ };


cell_type Cell::getCellType() {
    return type;
}

unsigned int Cell::getX() {
    return x;
}

unsigned int Cell::getY() {
    return y;
}

color_type Cell::getColor() {
    return color;
}

unsigned short Cell::getDirection() {
    return direction;
}

void Cell::setType(cell_type type) {
    this->type = type;
}

void Cell::setX(unsigned int x) {
    this->x = x;
}

void Cell::setY(unsigned int x) {
    this->y = y;
}

void Cell::setColor(color_type color) {
    this->color = color;
}

void Cell::setDirection(unsigned short direction) {
    this->direction = direction;
}

ostream& operator<<(ostream& os, const Cell& c) {
    os << cellTypeToString(c.type) << ": (" << c.x << ", " << c.y << "), d: " << c.direction <<
            ", c: " << colorToString(c.color) << endl;
    return os;
}

void Cell::addRay(ray_type ray) {
    rays.push_back(ray);
}
