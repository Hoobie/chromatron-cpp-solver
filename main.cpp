#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG false

using namespace std;

// =============================================== CELL TYPE ===========================================================

enum cell_type {ES = 0, LU = 1, LP = 2, LK = 3, RU = 4, TG = 5, BL = 6, NONE = 7, VISITED = 8};

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
    // VISITED - for marking visited cells
    if (s == "VISITED") return VISITED;
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
        case VISITED: return "VISITED";
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
    return "BLANK";
}

inline void operator+=(color_type &c1, color_type &c2) {
    if (c1 == BLANK) c1 = c2;
    if (c1 == RED && c2 == GREEN) c1 = YELLOW;
    if (c1 == GREEN && c2 == BLUE) c1 = CYAN;
    if (c1 == RED && c2 == BLUE) c1 = MAGENTA;
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
    Cell clone() const { return Cell(*this); }
    cell_type getCellType();
    void setType(cell_type type);
    unsigned int getX();
    void setX(unsigned int x);
    unsigned int getY();
    void setY(unsigned int y);
    color_type getColor();
    void setColor(color_type color);
    unsigned short getDirection();
    void setDirection(unsigned short direction);
    friend ostream& operator<<(ostream& os, const Cell& c);
    void addRay(ray_type ray);
    vector<ray_type> & getRays();
};

Cell::Cell() {
    this->type = NONE;
    this->color = BLANK;
}

Cell::Cell(cell_type type, unsigned int x, unsigned int y, unsigned short direction, color_type color) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->color = color;
}

Cell::Cell(string type, unsigned int x, unsigned int y, unsigned short direction, string color)
        : Cell(toCellType(type), x, y, direction, toColor(color)) {
}


cell_type Cell::getCellType() {
    return type;
}

void Cell::setType(cell_type type) {
    this->type = type;
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

void Cell::setColor(color_type color) {
    this->color = color;
}

unsigned short Cell::getDirection() {
    return direction;
}

void Cell::setDirection(unsigned short direction) {
    this->direction = direction;
}

ostream& operator<<(ostream& os, const Cell& c) {
    if (isBlock(c.type)) {
        os << "X";
        return os;
    }
    if (isLaser(c.type)) {
        os << "*";
        return os;
    }
    if (isMirror(c.type)) {
        os << ")";
        return os;
    }
    if (isPipe(c.type)) {
        os << "=";
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
    return os;
}

void Cell::addRay(ray_type ray) {
    rays.push_back(ray);
}

vector<ray_type> & Cell::getRays() {
    return rays;
}

// ============================================== DECLARATIONS =========================================================

void changeRays(vector<vector<Cell>> &board, unsigned int width, unsigned int height, Cell &device, bool remove);
pair<short, short> getRaySteps(unsigned short direction);
unsigned short laserToPipeDirection(unsigned short laserDirection);
bool solve(vector<vector<Cell>> &board, unsigned int width, unsigned int height, vector<Cell> &mirrors);
void printBoard(vector<vector<Cell>> board, unsigned int width, unsigned int height);
void prepareBoardCopy(vector<vector<Cell>> &boardCopy, unsigned int width, unsigned int height, vector<Cell> &mirrorsCopy,
                      unsigned int x, unsigned int y, unsigned short mirrorDirection);
unsigned short getReflectionDirection(cell_type mirror_type, unsigned short mirrorDirection,
                                      unsigned short rayDirection);
bool isBoardCompleted(vector<vector<Cell>> board, unsigned int width, unsigned int height);

unsigned int width, height, devicesCount = 0;

int main() {

    vector<Cell> devices;
    vector<Cell> mirrors;

    cin >> width >> height >> devicesCount;
    // extend board
    width++;
    height++;

    vector<vector<Cell>> board(width, vector<Cell>(height));

    for (unsigned int i = 0; i < devicesCount; i++) {
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

    // solve
    if (!solve(board, width, height, mirrors) && DEBUG) {
        cout << "No solution" << endl;
    }

    return 0;
}

void printBoard(vector<vector<Cell>> board, unsigned int width, unsigned int height) {
    cout << width - 1 << " " << height - 1 << endl;
    cout << devicesCount << endl;
    for (unsigned int y = 1; y < height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            Cell cell = board[x][y];
            cell_type type = cell.getCellType();
            if (isMirror(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell.getDirection() << " " << 0 << endl;
                continue;
            }
            if (isLaser(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell.getDirection() << " " << colorToString(cell.getColor()) << endl;
                continue;
            }
            if (isTarget(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << 0 << " " << colorToString(cell.getColor()) << endl;
                continue;
            }
            if (isPipe(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << cell.getDirection() << " " << 0 << endl;
                continue;
            }
            if (isPipe(type)) {
                cout << cellTypeToString(type) << " " << x << " " << y << " " << 0 << " " << 0 << endl;
                continue;
            }
        }
    }

    if (DEBUG) {
        for (unsigned int y = 1; y < height; y++) {
            for (unsigned int x = 1; x < width; x++) {
                cout << board[x][y];
            }
        }
    }
}

bool solve(vector<vector<Cell>> &board, unsigned int width, unsigned int height, vector<Cell> &mirrors) {
    if (isBoardCompleted(board, width, height)) {
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

void prepareBoardCopy(vector<vector<Cell>> &boardCopy, unsigned int width, unsigned int height,
                      vector<Cell> &mirrorsCopy, unsigned int x, unsigned int y, unsigned short mirrorDirection) {
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

void changeRays(vector<vector<Cell>> &board, unsigned int width, unsigned int height, Cell &device, bool remove) {
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

bool isBoardCompleted(vector<vector<Cell>> board, unsigned int width, unsigned int height) {
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