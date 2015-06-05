#include <iostream>
#include <vector>
#include <algorithm>
#include "cell_type.h"
#include "Cell.h"

void changeRays(vector<vector<Cell>> &board, int width, int height, Cell &device, bool remove);
pair<short, short> getRaySteps(unsigned short direction);
unsigned short laserToPipeDirection(unsigned short laserDirection);
bool solve(vector<vector<Cell>> &board, int width, int height, vector<Cell> &mirrors);
void printBoard(vector<vector<Cell>> board, int width, int height);
void prepareBoardCopy(vector<vector<Cell>> &boardCopy, int width, int height, vector<Cell> &mirrorsCopy, unsigned int x,
                      unsigned int y, unsigned short mirrorDirection);
unsigned short getReflectionDirection(cell_type mirror_type, unsigned short mirrorDirection,
                                      unsigned short rayDirection);
bool isBoardCompleted(vector<vector<Cell>> board, int width, int height);

using namespace std;

int main() {

    unsigned int width, height, devicesCount = 0;
    vector<Cell> devices;
    vector<Cell> mirrors;

    cin >> width >> height >> devicesCount;
    // extend board
    width++;
    height++;

    vector<vector<Cell>> board(width, vector<Cell>(height));

    for (int i = 0; i < devicesCount; i++) {
        string type, color;
        unsigned int x, y = 0;
        unsigned short direction = 0;

        cin >> type >> x >> y >> direction >> color;

        Cell cell = Cell(type, x, y, direction, color);
        devices.push_back(cell);
        board[x][y] = cell;
    }

    // add lasers and rays, gather mirrors
    for (auto &dev : devices) {
        if (isLaser(dev.getCellType())) {
            changeRays(board, width, height, dev, false);
        }
        if (isMirror(dev.getCellType())) {
            mirrors.push_back(dev);
        }
    }

    printBoard(board, width, height);

    // solve
    if (!solve(board, width, height, mirrors)) {
        cout << "No solution" << endl;
    }

    return 0;
}

void printBoard(vector<vector<Cell>> board, int width, int height) {
    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}

bool solve(vector<vector<Cell>> &board, int width, int height, vector<Cell> &mirrors) {
    if (isBoardCompleted(board, width, height)) {
        cout << endl << "completed!" << endl;
        printBoard(board, width, height);
        return true;
    }
    if (mirrors.empty()) {
        return false;
    }
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            Cell &cell = board[x][y];
            if (!cell.getRays().empty() && cell.getCellType() != VISITED) {
                for (auto &mirror : mirrors) {
                    if (mirror.getCellType() == LP) {
                        vector<vector<Cell>> boardCopy1(board);
                        vector<vector<Cell>> boardCopy2(board);
                        vector<vector<Cell>> boardCopy3(board);
                        vector<vector<Cell>> boardCopy4(board);
                        vector<vector<Cell>> boardCopy5(board);

                        vector<Cell> mirrorsCopy1;
                        vector<Cell> mirrorsCopy2;
                        vector<Cell> mirrorsCopy3;
                        vector<Cell> mirrorsCopy4;
                        vector<Cell> mirrorsCopy5;
                        for (auto &m : mirrors) {
                            mirrorsCopy1.push_back(m.clone());
                            mirrorsCopy2.push_back(m.clone());
                            mirrorsCopy3.push_back(m.clone());
                            mirrorsCopy4.push_back(m.clone());
                            mirrorsCopy5.push_back(m.clone());
                        }

                        prepareBoardCopy(boardCopy1, width, height, mirrorsCopy1, x, y, 0);
                        prepareBoardCopy(boardCopy2, width, height, mirrorsCopy2, x, y, 1);
                        prepareBoardCopy(boardCopy3, width, height, mirrorsCopy3, x, y, 2);
                        prepareBoardCopy(boardCopy4, width, height, mirrorsCopy4, x, y, 3);

                        boardCopy5[x][y].setType(VISITED);

                        return solve(boardCopy1, width, height, mirrorsCopy1) ||
                               solve(boardCopy2, width, height, mirrorsCopy2) ||
                               solve(boardCopy3, width, height, mirrorsCopy3) ||
                               solve(boardCopy4, width, height, mirrorsCopy4) ||
                               solve(boardCopy5, width, height, mirrorsCopy5);
                    } else {
                        vector<vector<Cell>> boardCopy1(board);
                        vector<vector<Cell>> boardCopy2(board);
                        vector<vector<Cell>> boardCopy3(board);
                        vector<vector<Cell>> boardCopy4(board);
                        vector<vector<Cell>> boardCopy5(board);
                        vector<vector<Cell>> boardCopy6(board);
                        vector<vector<Cell>> boardCopy7(board);
                        vector<vector<Cell>> boardCopy8(board);
                        vector<vector<Cell>> boardCopy9(board);

                        vector<Cell> mirrorsCopy1;
                        vector<Cell> mirrorsCopy2;
                        vector<Cell> mirrorsCopy3;
                        vector<Cell> mirrorsCopy4;
                        vector<Cell> mirrorsCopy5;
                        vector<Cell> mirrorsCopy6;
                        vector<Cell> mirrorsCopy7;
                        vector<Cell> mirrorsCopy8;
                        vector<Cell> mirrorsCopy9;
                        for (auto &m : mirrors) {
                            mirrorsCopy1.push_back(m.clone());
                            mirrorsCopy2.push_back(m.clone());
                            mirrorsCopy3.push_back(m.clone());
                            mirrorsCopy4.push_back(m.clone());
                            mirrorsCopy5.push_back(m.clone());
                            mirrorsCopy6.push_back(m.clone());
                            mirrorsCopy7.push_back(m.clone());
                            mirrorsCopy8.push_back(m.clone());
                            mirrorsCopy9.push_back(m.clone());
                        }

                        prepareBoardCopy(boardCopy1, width, height, mirrorsCopy1, x, y, 0);
                        prepareBoardCopy(boardCopy2, width, height, mirrorsCopy2, x, y, 1);
                        prepareBoardCopy(boardCopy3, width, height, mirrorsCopy3, x, y, 2);
                        prepareBoardCopy(boardCopy4, width, height, mirrorsCopy4, x, y, 3);
                        prepareBoardCopy(boardCopy5, width, height, mirrorsCopy5, x, y, 4);
                        prepareBoardCopy(boardCopy6, width, height, mirrorsCopy6, x, y, 5);
                        prepareBoardCopy(boardCopy7, width, height, mirrorsCopy7, x, y, 6);
                        prepareBoardCopy(boardCopy8, width, height, mirrorsCopy8, x, y, 7);

                        boardCopy9[x][y].setType(VISITED);

                        return solve(boardCopy1, width, height, mirrorsCopy1) ||
                               solve(boardCopy2, width, height, mirrorsCopy2) ||
                               solve(boardCopy3, width, height, mirrorsCopy3) ||
                               solve(boardCopy4, width, height, mirrorsCopy4) ||
                               solve(boardCopy5, width, height, mirrorsCopy5) ||
                               solve(boardCopy6, width, height, mirrorsCopy6) ||
                               solve(boardCopy7, width, height, mirrorsCopy7) ||
                               solve(boardCopy8, width, height, mirrorsCopy8) ||
                               solve(boardCopy9, width, height, mirrorsCopy9);
                    }
                }
            }
        }
    }
    return false;
}

void prepareBoardCopy(vector<vector<Cell>> &boardCopy, int width, int height, vector<Cell> &mirrorsCopy, unsigned int x,
                      unsigned int y, unsigned short mirrorDirection) {
    Cell &cell = boardCopy[x][y];

    unsigned short direction = cell.getDirection();
    color_type color = cell.getColor();

    changeRays(boardCopy, width, height, cell, true);

    Cell m = mirrorsCopy.back();
    mirrorsCopy.pop_back();
    m.setDirection(getReflectionDirection(m.getCellType(), mirrorDirection, direction));
    m.setX(x);
    m.setY(y);
    m.setColor(color);
    cell = m;
    changeRays(boardCopy, width, height, cell, false);
}

void changeRays(vector<vector<Cell>> &board, int width, int height, Cell &device, bool remove) {
    pair<short, short> steps = getRaySteps(device.getDirection());

    if (steps.first == 0 && steps.second == 0) {
        return;
    }

    for (pair<unsigned int, unsigned int> i(device.getX() + steps.first, device.getY() + steps.second);
         i.first > 0 && i.first < width && i.second > 0 && i.second < height; i.first += steps.first, i.second += steps.second) {

        Cell &cell = board[i.first][i.second];

        if (isBlock(cell.getCellType())) {
            break;
        }

        const ray_type &ray = { device.getDirection(), device.getColor() };

        vector<ray_type> &rays = cell.getRays();
        const vector<::ray_type>::iterator &iterator = find(rays.begin(), rays.end(), ray);
        if (iterator != rays.end()) {
            if (remove) {
                rays.erase(iterator);
            }
            continue;
        }

        if (isPipe(cell.getCellType())) {
            if (cell.getDirection() != laserToPipeDirection(device.getDirection())) {
                break;
            }
        }

        if (isMirror(cell.getCellType())) {
            // create pseudo-laser with proper reflection direction
            unsigned short direction = getReflectionDirection(cell.getCellType(), cell.getDirection(), device.getDirection());
            Cell pseudoLaser = Cell(NONE, i.first, i.second, direction, device.getColor());
            changeRays(board, width, height, pseudoLaser, remove);
            // if not splitter then only one ray
            if (cell.getCellType() != LP) {
                break;
            }
        }

        cell.setX(i.first);
        cell.setY(i.second);
        cell.addRay(ray);
        cell.setDirection(device.getDirection());

        rays = cell.getRays();
        color_type colorSum = BLANK;
        for (auto r : rays) {
            colorSum += r.color;
        }
        cell.setColor(colorSum);

        if (isTarget(cell.getCellType())) {
            break;
        }
    }
}

unsigned short getReflectionDirection(cell_type mirror_type, unsigned short mirrorDirection,
                                      unsigned short rayDirection) {
    switch (mirror_type) {
        case LU:
        case LP:
            switch (mirrorDirection) {
                case 0:
                    if (rayDirection == 3) return 1;
                    if (rayDirection == 5) return 7;
                    return 8;
                case 1:
                    if (rayDirection == 4) return 2;
                    if (rayDirection == 6) return 0;
                    return 8;
                case 2:
                    if (rayDirection == 5) return 3;
                    if (rayDirection == 7) return 1;
                    return 8;
                case 3:
                    if (rayDirection == 0) return 2;
                    if (rayDirection == 6) return 4;
                    return 8;
                case 4:
                    if (rayDirection == 1) return 3;
                    if (rayDirection == 7) return 5;
                    return 8;
                case 5:
                    if (rayDirection == 0) return 6;
                    if (rayDirection == 2) return 5;
                    return 8;
                case 6:
                    if (rayDirection == 1) return 7;
                    if (rayDirection == 3) return 5;
                    return 8;
                case 7:
                    if (rayDirection == 2) return 0;
                    if (rayDirection == 4) return 6;
                    return 8;
                default:
                    throw 3;
            }
        case LK:
            throw "Not implemented yet!!!";
        default:
            throw 2;
    }
}

pair<short, short> getRaySteps(unsigned short direction) {
    switch (direction) {
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

bool isBoardCompleted(vector<vector<Cell>> board, int width, int height) {
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            Cell cell = board[x][y];
            if (isTarget(cell.getCellType())) {
                vector<ray_type> rays = cell.getRays();
                color_type colorSum = BLANK;
                for (auto ray : rays) {
                    colorSum += ray.color;
                }
                if (colorSum != cell.getColor()) {
                    return false;
                }
            }
        }
    }
    return true;
}