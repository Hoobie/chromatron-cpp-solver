#include <iostream>
#include "Device.h"

Device::Device(string type, unsigned int x, unsigned int y, unsigned short direction, unsigned short color) {
    this->type = toDeviceType(type);
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = color;
}

Device::~Device() {
}

unsigned short Device::getDirectionsCount() {
    return 0;
}

ostream& operator<<(ostream& os, const Device& d) {
    os << deviceTypeToString(d.type) << ": (" << d.x << ", " << d.y << "), d:" << d.direction << " c:" << d.color;
    return os;
}
