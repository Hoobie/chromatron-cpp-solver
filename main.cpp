#include <iostream>
#include <vector>
#include "Device.h"

using namespace std;

int main() {

    int width, height, devicesCount = 0;
    vector<Device> devices;

    cin >> width >> height >> devicesCount;

    Cell** board = new Cell*[width];

    for (int i = 0; i < devicesCount; i++) {
        string type, color;
        unsigned int x, y = 0;
        unsigned short direction = 0;
        cin >> type >> x >> y >> direction >> color;
        Device device = Device(type, x, y, direction, color);
        devices.push_back(device);
        cout << device;

        // add blocks, pipes and targets
        if (!isLaser(device.getDeviceType()) && !isMirror(device.getDeviceType())) {
            Cell c = Cell(x, y, direction, color);
            board[x][y] = c;
        }
    }

    // TODO: add lasers and rays to the board

    for (int i = 0; i < width; ++i) {
        if (board[i] != NULL) {
            delete board[i];
        }
        delete[] board[i];
    }
    delete [] board;

    return 0;
}