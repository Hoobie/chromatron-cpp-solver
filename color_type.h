#ifndef CHROMATRON_CPP_SOLVER_COLOR_H
#define CHROMATRON_CPP_SOLVER_COLOR_H

#include <string>

using namespace std;

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

#endif //CHROMATRON_CPP_SOLVER_COLOR_H
