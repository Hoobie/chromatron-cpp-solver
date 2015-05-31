#ifndef CHROMATRON_CPP_SOLVER_DEVICE_H
#define CHROMATRON_CPP_SOLVER_DEVICE_H

#include <iostream>
#include "device_type.h"

using namespace std;

class Device {
    device_type type;
    unsigned int x;
    unsigned int y;
    unsigned short direction;
    unsigned short color;
public:
    Device(string type, unsigned int x, unsigned int y, unsigned short direction, unsigned short color);
    ~Device();
    unsigned short getDirectionsCount();
    friend ostream& operator<<(ostream& os, const Device& d);
};

#endif //CHROMATRON_CPP_SOLVER_DEVICE_H
