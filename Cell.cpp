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

void Cell::setType(cell_type type) {
    this->type = type;
}

unsigned int Cell::getX() {
    return x;
}

void Cell::setX(unsigned int x) {
    this->x = x;
}

unsigned int Cell::getY() {
    return y;
}

void Cell::setY(unsigned int y) {
    this->y = y;
}

color_type Cell::getColor() {
    return color;
}

void Cell::setColor(color_type color) {
    this->color = color;
}

unsigned short Cell::getDirection() {
    return direction;
}

void Cell::setDirection(unsigned short direction) {
    this->direction = direction;
}

ostream& operator<<(ostream& os, const Cell& c) {
    if (isBlock(c.type)) {
        os << "X";
        return os;
    }
    if (isLaser(c.type)) {
        os << "*";
        return os;
    }
    if (isMirror(c.type)) {
        os << ")";
        return os;
    }
    if (isPipe(c.type)) {
        os << "=";
        return os;
    }
    if (isTarget(c.type)) {
        os << "o";
        return os;
    }
    if (!c.rays.empty()) {
        switch(c.rays[0].direction) {
            case 0:
            case 4:
                os << "-";
                break;
            case 1:
            case 5:
                os << "/";
                break;
            case 2:
            case 6:
                os << "|";
                break;
            case 3:
            case 7:
                os << "\\";
                break;
            default:
                os << "R";
        }
        return os;
    } else if (c.type == NONE) {
        os << ".";
        return os;
    }
    return os;
}

void Cell::addRay(ray_type ray) {
    rays.push_back(ray);
}

vector<ray_type> Cell::getRays() {
    return rays;
}