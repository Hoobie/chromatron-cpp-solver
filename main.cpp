#include <iostream>
#include <vector>
#include "cell_type.h"
#include "Cell.h"

void addRays(Cell **board, int width, int height, Cell &laser);

pair<short, short> getRaySteps(unsigned short laserDirection);

unsigned short laserToPipeDirection(unsigned short laserDirection);

using namespace std;

int main() {

    int width, height, devicesCount = 0;
    vector<Cell> devices;

    cin >> width >> height >> devicesCount;
    // extend board
    width++;
    height++;

    Cell** board = new Cell*[width];
    for (int i = 0; i < width; i++) {
        board[i] = new Cell[height];
    }

    for (int i = 0; i < devicesCount; i++) {
        string type, color;
        unsigned int x, y = 0;
        unsigned short direction = 0;

        cin >> type >> x >> y >> direction >> color;

        Cell cell = Cell(type, x, y, direction, color);
        devices.push_back(board[x][y]);
        board[x][y] = cell;
        cout << board[x][y];
    }

    // add lasers and rays
    for (auto &dev : devices) {
        if (isLaser(dev.getCellType())) {
            addRays(board, width, height, dev);
        }
    }

    // TODO: move mirrors

    // cleanup
    for (int i = 0; i < width; ++i) {
        delete [] board[i];
    }
    delete [] board;

    return 0;
}

void addRays(Cell **board, int width, int height, Cell &laser) {
    pair<short, short> steps = getRaySteps(laser.getDirection());
    for (pair<unsigned int, unsigned int> i(laser.getX() + steps.first, laser.getY() + steps.second);
         i.first > 0, i.first < width, i.second > 0, i.second < height; i.first + steps.first, i.second + steps.second) {
        Cell &cell = board[i.first][i.second];
        if (isBlock(cell.getCellType())) {
            break;
        }
        ray_type ray = { laser.getDirection(), laser.getColor() };
        if (isPipe(cell.getCellType())) {
            if (cell.getDirection() != laserToPipeDirection(laser.getDirection())) {
                break;
            }
        }
        cell.addRay(ray);
    }
}

pair<short, short> getRaySteps(unsigned short laserDirection) {
    switch (laserDirection) {
        case 0:
            return make_pair(-1, 0);
        case 1:
            return make_pair(-1, 1);
        case 2:
            return make_pair(0, 1);
        case 3:
            return make_pair(1, 1);
        case 4:
            return make_pair(1, 0);
        case 5:
            return make_pair(1, -1);
        case 6:
            return make_pair(0, -1);
        case 7:
            return make_pair(-1, -1);
        default:
            return make_pair(0, 0);
    }
}

unsigned short laserToPipeDirection(unsigned short laserDirection) {
    switch (laserDirection) {
        case 0:
        case 4:
            return 0;
        case 1:
        case 5:
            return 1;
        case 2:
        case 6:
            return 2;
        case 3:
        case 7:
            return 3;
        default:
            return 0;
    }
}