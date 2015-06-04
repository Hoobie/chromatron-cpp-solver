#include <iostream>
#include "Device.h"

Device::Device(string type, unsigned int x, unsigned int y, unsigned short direction, string color)
        : Cell(x, y, direction, color) {
    this->type = toDeviceType(type);
}

Device::~Device() {
}

device_type Device::getDeviceType() {
    return type;
}

ostream& operator<<(ostream& os, const Device& d) {
    os << deviceTypeToString(d.type) << ": (" << d.x << ", " << d.y << "), d: " << d.direction << ", c: " << colorToString(d.color);
    return os;
}
