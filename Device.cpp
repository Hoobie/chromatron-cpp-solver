#include <iostream>
#include "Device.h"

Device::Device(string type, unsigned int x, unsigned int y, unsigned short direction, string color) {
    this->type = toDeviceType(type);
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = toColor(color);
}

Device::~Device() {
}

unsigned short Device::getDirectionsCount() {
    return 0;
}

ostream& operator<<(ostream& os, const Device& d) {
    os << deviceTypeToString(d.type) << ": (" << d.x << ", " << d.y << "), d: " << d.direction << " c: " << colorToString(d.color);
    return os;
}
