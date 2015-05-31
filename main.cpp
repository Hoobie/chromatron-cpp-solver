#include <iostream>
#include <vector>
#include "Device.h"

using namespace std;

int main() {

    int width, height, devicesCount = 0;
    vector<Device> devices;

    cin >> width >> height >> devicesCount;

    for (int i = 0; i < devicesCount; i++) {
        string type;
        unsigned int x, y = 0;
        unsigned short direction, color = 0;
        cin >> type >> x >> y >> direction >> color;
        Device device = Device(type, x, y, direction, color);
        devices.push_back(device);
        cout << device;
    }

    return 0;
}