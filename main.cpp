#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

#define DEBUG false

using namespace std;

// =============================================== CELL TYPE ===========================================================

enum cell_type {ES = 0, LU = 1, LP = 2, LK = 3, RU = 4, TG = 5, BL = 6, NONE = 7};

inline cell_type toCellType(string s);
inline string cellTypeToString(cell_type dt);
inline bool isLaser(cell_type dt);
inline bool isMirror(cell_type dt);
inline bool isBlock(cell_type dt);
inline bool isPipe(cell_type dt);
inline bool isTarget(cell_type dt);

inline cell_type toCellType(string s) {
    // Laser
    if (s == "ES") return ES;
    // Mirror
    if (s == "LU") return LU;
    // Splitter mirror
    if (s == "LP") return LP;
    // Shifted mirror
    if (s == "LK") return LK;
    // Pipe
    if (s == "RU") return RU;
    // Target
    if (s == "TG") return TG;
    // Block
    if (s == "BL") return BL;
    // None - default type for rays or empty cells
    if (s == "NONE") return NONE;
    return NONE;
}

inline string cellTypeToString(cell_type dt) {
    switch (dt) {
        case ES: return "ES";
        case LU: return "LU";
        case LP: return "LP";
        case LK: return "LK";
        case RU: return "RU";
        case TG: return "TG";
        case BL: return "BL";
        case NONE: return "NONE";
    }
    return "NONE";
}

inline bool isLaser(cell_type dt) {
    return dt == ES;
}

inline bool isMirror(cell_type dt) {
    return dt == LU || dt == LP || dt == LK;
}

inline bool isBlock(cell_type dt) {
    return dt == BL;
}

inline bool isPipe(cell_type dt) {
    return dt == RU;
}

inline bool isTarget(cell_type dt) {
    return dt == TG;
}

// =============================================== COLOR TYPE ==========================================================

enum color_type {BLANK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, YELLOW = 6, WHITE = 7};

inline color_type toColor(string s);
inline string colorToString(color_type c);

inline color_type toColor(string s) {
    if (s == "000") return BLANK;
    if (s == "001") return BLUE;
    if (s == "010") return GREEN;
    if (s == "011") return CYAN;
    if (s == "100") return RED;
    if (s == "101") return MAGENTA;
    if (s == "110") return YELLOW;
    if (s == "111") return WHITE;
    return BLANK;
}

inline string colorToString(color_type c) {
    switch (c) {
        case BLANK: return "000";
        case BLUE: return "001";
        case GREEN: return "010";
        case CYAN: return "011";
        case RED: return "100";
        case MAGENTA: return "101";
        case YELLOW: return "110";
        case WHITE: return "111";
    }
    return "000";
}

inline color_type operator+=(color_type& c1, color_type c2) {
    if ((color_type)c1 == BLANK) return c1 = c2;
    if (c2 == BLANK) return c1;
    if ((color_type)c1 == RED && c2 == GREEN) return c1 = YELLOW;
    if ((color_type)c1 == GREEN && c2 == BLUE) return c1 = CYAN;
    if ((color_type)c1 == RED && c2 == BLUE) return c1 = MAGENTA;
    if (c2 == RED && (color_type)c1 == GREEN) return c1 = YELLOW;
    if (c2 == GREEN && (color_type)c1 == BLUE) return c1 = CYAN;
    if (c2 == RED && (color_type)c1 == BLUE) return c1 = MAGENTA;
    return c1;
}

// ================================================ RAY TYPE ===========================================================

struct ray_type {
    unsigned short direction;
    color_type color;

    bool operator==(ray_type r) {
        return (direction == r.direction && color == r.color);
    }
};

// ================================================== CELL =============================================================

class Cell {
    int id;
    cell_type type;
    unsigned int x;
    unsigned int y;
    color_type color;
    /*
     * directions (from laser definition):
     * _________
     * |7  6  5|
     * |0  x  4|
     * |1  2  3|
     * ---------
     */
    unsigned short direction;
    vector<ray_type> rays;
public:
    Cell();
    Cell(cell_type type, unsigned int x, unsigned int y, unsigned short direction, color_type color);
    Cell(string type, unsigned int x, unsigned int y, unsigned short direction, string color);
    cell_type getCellType();
    unsigned int getX();
    void setX(unsigned int x);
    unsigned int getY();
    void setY(unsigned int y);
    color_type getColor();
    unsigned short getDirection()const;
    void setDirection(unsigned short direction);
    friend ostream& operator<<(ostream& os, const Cell& c);
    friend bool operator==(Cell c1, Cell c2);
    void addRay(ray_type ray);
    vector<ray_type>& getRays();
    void clearRays();

    void setId(int id);
};

Cell::Cell() {
    this->x = 0;
    this->y = 0;
    this->type = NONE;
    this->color = BLANK;
    this->id = 0;
}

Cell::Cell(cell_type type, unsigned int x, unsigned int y, unsigned short direction, color_type color) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = color;
    this->id = 0;
}

Cell::Cell(string type, unsigned int x, unsigned int y, unsigned short direction, string color) {
    this->type = toCellType(type);
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = toColor(color);
    this->id = 0;
}

cell_type Cell::getCellType() {
    return type;
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

unsigned short Cell::getDirection()const {
    return direction;
}

void Cell::setDirection(unsigned short direction) {
    this->direction = direction;
}

ostream& operator<<(ostream& os, const Cell& c) {
    if (isBlock(c.type)) {
        os << "B";
        return os;
    }
    if (isLaser(c.type)) {
        os << "*";
        return os;
    }
    if (isMirror(c.type)) {
        if (c.type == LP) {
            os << "P";
            return os;
        }
        if (c.rays.empty()) {
            switch (c.type) {
                case LU:
                    os << "L";
                    break;
                case LK:
                    os << "K";
                    break;
                default:
                    os << ".";
            }
            return os;
        }
        os << c.direction;
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
                os << ".";
        }
        return os;
    } else if (c.type == NONE) {
        os << ".";
        return os;
    }
    if (isPipe(c.type)) {
        os << "R";
        return os;
    }
    return os;
}

bool operator==(Cell c1, Cell c2) {
    return (c1.type == c2.type && c1.x == c2.x && c1.y == c2.y && c1.direction == c2.direction
            && c1.color == c2.color && c1.id == c2.id);
}

void Cell::setId(int id) {
    this->id = id;
}

void Cell::addRay(ray_type ray) {
    rays.push_back(ray);
}

vector<ray_type> & Cell::getRays() {
    return rays;
}

void Cell::clearRays() {
    rays.clear();
}

// ============================================== DECLARATIONS =========================================================

void emitRay(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, shared_ptr<Cell> &laser, bool clear);
pair<short, short> getRaySteps(unsigned short direction);
unsigned short laserToPipeDirection(unsigned short laserDirection);
bool solve(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height,
           vector<shared_ptr<Cell>> allMirrors, vector<shared_ptr<Cell>> &mirrorsToUse,
           map<long, bool> &mirrorsSnapshots, vector<shared_ptr<Cell>> lasers);
void printBoard(vector<vector<shared_ptr<Cell>>> board, unsigned int width, unsigned int height);
void putMirror(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, unsigned int x, unsigned int y,
               shared_ptr<Cell> &mirror, unsigned short mirrorDirection);
unsigned short getReflectionDirection(cell_type mirror_type, unsigned short mirrorDirection, unsigned short rayDirection);
bool isBoardCompleted(vector<vector<shared_ptr<Cell>>> board, unsigned int width, unsigned int height);
void reflectRays(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, shared_ptr<Cell> &mirror, bool clear);

unsigned int width, height, devicesCount = 0;

int main() {

    vector<shared_ptr<Cell>> devices;
    vector<shared_ptr<Cell>> mirrors;
    vector<shared_ptr<Cell>> lasers;

    cin >> width >> height >> devicesCount;
    // extend board
    width++;
    height++;

    vector<vector<shared_ptr<Cell>>> board(width, vector<shared_ptr<Cell>>(height));

    for (unsigned int i = 0; i < devicesCount; i++) {
        string type, color;
        unsigned int x, y = 0;
        unsigned short direction = 0;

        cin >> type >> x >> y >> direction >> color;

        shared_ptr<Cell> cell = make_shared<Cell>(type, x, y, direction, color);

        devices.push_back(cell);
        board[x][y] = cell;
    }

    // add lasers and rays, gather mirrors
    int i = 0;
    for (auto &dev : devices) {
        if (isLaser(dev->getCellType())) {
            lasers.push_back(dev);
            emitRay(board, width, height, dev, false);
        }
        if (isMirror(dev->getCellType())) {
            dev->setId(i++);
            mirrors.push_back(dev);
        }
    }

    // solve
    map<long, bool> snapshots = map<long, bool>();
    if (solve(board, width, height, mirrors, mirrors, snapshots, lasers)) {
        if (DEBUG) {
            cout << "Solution found! :)" << endl;
        }
        printBoard(board, width, height);
    } else {
        cout << "Solution not found :(" << endl;
    }

    return 0;
};

void printBoard(vector<vector<shared_ptr<Cell>>> board, unsigned int width, unsigned int height) {
    if (DEBUG) {
        for (unsigned int y = 1; y < height; y++) {
            for (unsigned int x = 1; x < width; x++) {
                shared_ptr<Cell> cell = board[x][y];
                if (cell) {
                    cout << *cell;
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        return;
    }
    cout << width - 1 << " " << height - 1 << endl;
    cout << devicesCount << endl;
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            shared_ptr<Cell> cell = board[x][y];
            if (!cell) continue;
            cell_type type = cell->getCellType();
            if (isMirror(type)) {
                if (cell->getRays().empty()) {
                    cout << cellTypeToString(type) << " 0 0 0 0" << endl;
                    continue;
                }
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell->getDirection() << " 0" << endl;
                continue;
            }
            if (isLaser(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell->getDirection() << " " << colorToString(cell->getColor()) << endl;
                continue;
            }
            if (isTarget(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " 0 " << colorToString(cell->getColor()) << endl;
                continue;
            }
            if (isPipe(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell->getDirection() << " 0" << endl;
                continue;
            }
            if (isBlock(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " 0 0" << endl;
                continue;
            }
        }
    }
}

bool solve(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height,
           vector<shared_ptr<Cell>> allMirrors, vector<shared_ptr<Cell>> &mirrorsToUse,
           map<long, bool> &mirrorsSnapshots, vector<shared_ptr<Cell>> lasers) {
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            shared_ptr<Cell> cell = board[x][y];
            if (cell) {
                cell->clearRays();
            }
        }
    }
    for (auto laser : lasers) {
        emitRay(board, width, height, laser, false);
    }
    if (isBoardCompleted(board, width, height)) {
        return true;
    }
    if (DEBUG) {
        printBoard(board, width, height);
    }
    if (mirrorsToUse.empty()) {
        return false;
    }
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            shared_ptr<Cell> cell = board[x][y];
            if (cell && cell->getCellType() == NONE && !cell->getRays().empty()) {
                for (auto &mirror : mirrorsToUse) {
                    unsigned short mirrorDirections = 8;
                    if (mirror->getCellType() == LP) {
                        mirrorDirections = 4;
                    }
                    bool foundNewSnapshot = false;
                    for (unsigned short mirrorDirection = 0; mirrorDirection < mirrorDirections; mirrorDirection++) {
                        long mirrorsHashcode = 17;
                        for (auto m : allMirrors) {
                            unsigned short direction = mirrorDirection;
                            unsigned int mirrorX = x;
                            unsigned int mirrorY = y;
                            if (m != mirror) {
                                direction = m->getDirection();
                                mirrorX = m->getX();
                                mirrorY = m->getY();
                            }
                            if (mirrorX == 0 && mirrorY == 0) continue;
                            mirrorsHashcode = mirrorsHashcode * 31 + m->getCellType();
                            mirrorsHashcode = mirrorsHashcode * 31 + mirrorX;
                            mirrorsHashcode = mirrorsHashcode * 31 + mirrorY;
                            mirrorsHashcode = mirrorsHashcode * 31 + direction;
                        }
                        if (mirrorsSnapshots.find(mirrorsHashcode) != mirrorsSnapshots.end()) {
                            continue;
                        }
                        mirrorsSnapshots[mirrorsHashcode] = true;
                        foundNewSnapshot = true;

//                        bool put = true;
//                        for (auto ray : cell->getRays()) {
//                            try {
//                                if (getReflectionDirection(mirror->getCellType(), mirrorDirection, ray.direction) < 7) {
//                                    break;
//                                }
//                            } catch (int i) {
//                            }
//                            put = false;
//                        }
//                        if (put) {
//                            continue;
//                        }

                        putMirror(board, width, height, x, y, mirror, mirrorDirection);

                        vector<shared_ptr<Cell>> mirrorsCopy(mirrorsToUse);
                        const vector<shared_ptr<Cell>>::iterator &iterator =
                                find_if(mirrorsCopy.begin(), mirrorsCopy.end(), [&](shared_ptr<Cell> const& p) {
                            return *p == *mirror;
                        });
                        mirrorsCopy.erase(iterator);

                        if (solve(board, width, height, allMirrors, mirrorsCopy, mirrorsSnapshots, lasers)) {
                            return true;
                        }
                        board[x][y] = cell;
//                        reflectRays(board, width, height, mirror, true);
//                        for (auto ray : cell->getRays()) {
//                            shared_ptr<Cell> tmpCell = make_shared<Cell>(NONE, x, y, ray.direction, ray.color);
//                            emitRay(board, width, height, tmpCell, false);
//                        }
                        mirror->clearRays();
                        mirror->setX(0);
                        mirror->setY(0);
                        mirror->setDirection(0);
                    }
                    if (!foundNewSnapshot) continue;
                    if (solve(board, width, height, allMirrors, mirrorsToUse, mirrorsSnapshots, lasers)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void putMirror(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, unsigned int x, unsigned int y,
               shared_ptr<Cell> &mirror, unsigned short mirrorDirection) {

    shared_ptr<Cell> cell = board[x][y];

//    for (auto ray : cell->getRays()) {
//        shared_ptr<Cell> tmpCell = shared_ptr<Cell>(new Cell(NONE, x, y, ray.direction, ray.color));
//        emitRay(board, width, height, tmpCell, true);
//
//        mirror->addRay({ray.direction, ray.color});
//    }

    mirror->setDirection(mirrorDirection);
    mirror->setX(x);
    mirror->setY(y);
    board[x][y] = mirror;

//    reflectRays(board, width, height, mirror, false);
}

void reflectRays(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, shared_ptr<Cell> &mirror, bool clear) {

    cell_type mirrorType = mirror->getCellType();

    for (auto ray : mirror->getRays()) {

        unsigned short reflectionDirection;
        try {
            reflectionDirection = getReflectionDirection(mirrorType, mirror->getDirection(), ray.direction);
        } catch (int ex) {
            continue;
        }

        if (reflectionDirection >= 0 && reflectionDirection <= 7) {
            shared_ptr<Cell> tmpLaser = make_shared<Cell>(NONE, mirror->getX(), mirror->getY(), reflectionDirection, ray.color);
            emitRay(board, width, height, tmpLaser, clear);
        }

        if (mirrorType == LP) {
            shared_ptr<Cell> tmpLaser2 = make_shared<Cell>(NONE, mirror->getX(), mirror->getY(), ray.direction, ray.color);
            emitRay(board, width, height, tmpLaser2, clear);
        }
    }
}

void emitRay(vector<vector<shared_ptr<Cell>>> &board, unsigned int width, unsigned int height, shared_ptr<Cell> &laser, bool clear) {

    pair<short, short> steps = getRaySteps(laser->getDirection());

    if (steps.first == 0 && steps.second == 0) {
        return;
    }

    for (pair<unsigned int, unsigned int> i(laser->getX() + steps.first, laser->getY() + steps.second);
         i.first > 0 && i.first < width && i.second > 0 && i.second < height; i.first += steps.first, i.second += steps.second) {

        shared_ptr<Cell> &cell = board[i.first][i.second];
        if (!cell) {
            board[i.first][i.second] = make_shared<Cell>();
        }
        cell->setX(i.first);
        cell->setY(i.second);
        cell_type cellType = cell->getCellType();

        if (isBlock(cellType) || isLaser(cellType)) {
            return;
        }

        if (isPipe(cellType)) {
            try {
                if (cell->getDirection() != laserToPipeDirection(laser->getDirection())) {
                    return;
                }
            } catch (int ex) {
                return;
            }
        }

        vector<ray_type> &rays = cell->getRays();
        ray_type ray = { laser->getDirection(), laser->getColor() };
        const vector<ray_type>::iterator &iterator = find(rays.begin(), rays.end(), ray);

        if (iterator != rays.end() && clear) {
            //rays.erase(iterator);
        } else if (iterator == rays.end() && !clear) {
            cell->addRay(ray);
        } else {
            return;
        }

        if (isMirror(cellType)) {
            reflectRays(board, width, height, cell, clear);
        }

        if (iterator != rays.end() && clear) {
            rays.erase(iterator);
        }

        if (isMirror(cellType)) {
            return;
        }
    }
}

unsigned short getReflectionDirection(cell_type mirror_type, unsigned short mirrorDirection, unsigned short rayDirection) {
    switch (mirror_type) {
        case LU:
            switch (mirrorDirection) {
                case 0:
                    if (rayDirection == 3) return 1;
                    if (rayDirection == 5) return 7;
                    throw 3;
                case 1:
                    if (rayDirection == 4) return 2;
                    if (rayDirection == 6) return 0;
                    throw 3;
                case 2:
                    if (rayDirection == 5) return 3;
                    if (rayDirection == 7) return 1;
                    throw 3;
                case 3:
                    if (rayDirection == 0) return 2;
                    if (rayDirection == 6) return 4;
                    throw 3;
                case 4:
                    if (rayDirection == 1) return 3;
                    if (rayDirection == 7) return 5;
                    throw 3;
                case 5:
                    if (rayDirection == 0) return 6;
                    if (rayDirection == 2) return 4;
                    throw 3;
                case 6:
                    if (rayDirection == 1) return 7;
                    if (rayDirection == 3) return 5;
                    throw 3;
                case 7:
                    if (rayDirection == 2) return 0;
                    if (rayDirection == 4) return 6;
                    throw 3;
                default:
                    throw 4;
            }
        case LP:
            switch (mirrorDirection) {
                case 0:
                    if (rayDirection == 3) return 1;
                    if (rayDirection == 5) return 7;
                    if (rayDirection == 1) return 3;
                    if (rayDirection == 7) return 5;
                    if (rayDirection == 0) return 8;
                    if (rayDirection == 4) return 8;
                    throw 3;
                case 1:
                    if (rayDirection == 4) return 2;
                    if (rayDirection == 6) return 0;
                    if (rayDirection == 0) return 6;
                    if (rayDirection == 2) return 4;
                    if (rayDirection == 1) return 8;
                    if (rayDirection == 5) return 8;
                    throw 3;
                case 2:
                    if (rayDirection == 5) return 3;
                    if (rayDirection == 7) return 1;
                    if (rayDirection == 1) return 7;
                    if (rayDirection == 3) return 5;
                    if (rayDirection == 2) return 8;
                    if (rayDirection == 6) return 8;
                    throw 3;
                case 3:
                    if (rayDirection == 0) return 2;
                    if (rayDirection == 6) return 4;
                    if (rayDirection == 2) return 0;
                    if (rayDirection == 4) return 6;
                    if (rayDirection == 3) return 8;
                    if (rayDirection == 7) return 8;
                    throw 3;
                default:
                    throw 4;
            }
        case LK:
            switch (mirrorDirection) {
                case 0:
                    if (rayDirection == 2) return 1;
                    if (rayDirection == 3) return 0;
                    if (rayDirection == 4) return 7;
                    if (rayDirection == 5) return 6;
                    throw 3;
                case 1:
                    if (rayDirection == 3) return 2;
                    if (rayDirection == 4) return 1;
                    if (rayDirection == 5) return 0;
                    if (rayDirection == 6) return 7;
                    throw 3;
                case 2:
                    if (rayDirection == 4) return 3;
                    if (rayDirection == 5) return 2;
                    if (rayDirection == 6) return 1;
                    if (rayDirection == 7) return 0;
                    throw 3;
                case 3:
                    if (rayDirection == 0) return 1;
                    if (rayDirection == 5) return 4;
                    if (rayDirection == 6) return 3;
                    if (rayDirection == 7) return 2;
                    throw 3;
                case 4:
                    if (rayDirection == 0) return 3;
                    if (rayDirection == 1) return 2;
                    if (rayDirection == 6) return 5;
                    if (rayDirection == 7) return 4;
                    throw 3;
                case 5:
                    if (rayDirection == 0) return 5;
                    if (rayDirection == 1) return 4;
                    if (rayDirection == 2) return 3;
                    if (rayDirection == 7) return 6;
                    throw 3;
                case 6:
                    if (rayDirection == 0) return 7;
                    if (rayDirection == 1) return 6;
                    if (rayDirection == 2) return 5;
                    if (rayDirection == 3) return 4;
                    throw 3;
                case 7:
                    if (rayDirection == 1) return 0;
                    if (rayDirection == 2) return 7;
                    if (rayDirection == 3) return 6;
                    if (rayDirection == 4) return 5;
                    throw 3;
                default:
                    throw 4;
            }
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
            throw 5;
    }
}

bool isBoardCompleted(vector<vector<shared_ptr<Cell>>> board, unsigned int width, unsigned int height) {
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            shared_ptr<Cell> cell = board[x][y];
            if (cell && isTarget(cell->getCellType())) {
                vector<ray_type> rays = cell->getRays();
                color_type colorSum = BLANK;
                for (auto ray : rays) {
                    colorSum += ray.color;
                }
                if (colorSum != cell->getColor()) {
                    return false;
                }
            }
        }
    }
    return true;
}