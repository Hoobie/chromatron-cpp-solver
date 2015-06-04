#ifndef CHROMATRON_CPP_SOLVER_UTIL_H
#define CHROMATRON_CPP_SOLVER_UTIL_H

#include <string>

using namespace std;

enum device_type {ES = 0, LU = 1, LP = 2, LK = 3, RU = 4, TG = 5, BL = 6};

inline device_type toDeviceType(string s);
inline string deviceTypeToString(device_type dt);
inline bool isLaser(device_type dt);
inline bool isMirror(device_type dt);

inline device_type toDeviceType(string s) {
    if (s == "ES") return ES;
    if (s == "LU") return LU;
    if (s == "LP") return LP;
    if (s == "LK") return LK;
    if (s == "RU") return RU;
    if (s == "TG") return TG;
    if (s == "BL") return BL;
    return ES;
}

inline string deviceTypeToString(device_type dt) {
    switch (dt) {
        case ES: return "ES";
        case LU: return "LU";
        case LP: return "LP";
        case LK: return "LK";
        case RU: return "RU";
        case TG: return "TG";
        case BL: return "BL";
    }
    return "";
}

inline bool isLaser(device_type dt) {
    return dt == ES;
}

inline bool isMirror(device_type dt) {
    return dt == LU || dt == LP || dt == LK;
}

#endif //CHROMATRON_CPP_SOLVER_UTIL_H
