#ifndef CHROMATRON_CPP_SOLVER_COLOR_H
#define CHROMATRON_CPP_SOLVER_COLOR_H

#include <string>

using namespace std;

enum color_type {BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, YELLOW = 6, WHITE = 7};

inline color_type toColor(string s);
inline string colorToString(color_type c);

inline color_type toColor(string s) {
    if (s == "001") return BLUE;
    if (s == "010") return GREEN;
    if (s == "011") return CYAN;
    if (s == "100") return RED;
    if (s == "101") return MAGENTA;
    if (s == "110") return YELLOW;
    if (s == "111") return WHITE;
    return WHITE;
}

inline string colorToString(color_type c) {
    switch (c) {
        case BLUE: return "BLUE";
        case GREEN: return "GREEN";
        case CYAN: return "CYAN";
        case RED: return "RED";
        case MAGENTA: return "MAGENTA";
        case YELLOW: return "YELLOW";
        case WHITE: return "WHITE";
    }
    return "";
}

#endif //CHROMATRON_CPP_SOLVER_COLOR_H
