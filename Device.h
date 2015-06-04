#ifndef CHROMATRON_CPP_SOLVER_DEVICE_H
#define CHROMATRON_CPP_SOLVER_DEVICE_H

#include <iostream>
#include "device_type.h"
#include "color_type.h"
#include "Cell.h"

using namespace std;

class Device : public Cell {
    device_type type;
public:
    Device(string type, unsigned int x, unsigned int y, unsigned short direction, string color);
    ~Device();
    device_type getDeviceType();
    friend ostream& operator<<(ostream& os, const Device& d);
};

#endif //CHROMATRON_CPP_SOLVER_DEVICE_H
