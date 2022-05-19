#ifndef DEF_SEVENSEGMENTS
#define DEF_SEVENSEGMENTS

#include <Arduino.h>
#include "ShiftRegister.h"

class SevenSegments
{
private:
    typedef struct Number
    {
        uint8_t value;
        bool led[8];
    };
    Number m_number[12]{
        // {A, B, C, D, E, F, G, DP}
        0,{0, 0, 0, 0, 0, 0, 1, 1},
        1,{1, 0, 0, 1, 1, 1, 1, 1},
        2,{0, 0, 1, 0, 0, 1, 0, 1},
        3,{0, 0, 0, 0, 1, 1, 0, 1},
        4,{1, 0, 0, 1, 1, 0, 0, 1},
        5,{0, 1, 0, 0, 1, 0, 0, 1},
        6,{0, 1, 0, 0, 0, 0, 0, 1},
        7,{0, 0, 0, 1, 1, 1, 1, 1},
        8,{0, 0, 0, 0, 0, 0, 0, 1},
        9,{0, 0, 0, 0, 1, 0, 0, 1},
        10,{1, 1, 0, 1, 0, 0, 0, 0},
        11,{1, 1, 1, 0, 0, 1, 0, 0}};

    typedef struct Digit
    {
        uint8_t value;
        bool out[8];
    };
    Digit m_digit[4]{
        1,{1, 0, 0, 0, 0, 0, 0, 0},
        2,{0, 1, 0, 0, 0, 0, 0, 0},
        3,{0, 0, 1, 0, 0, 0, 0, 0},
        4,{0, 0, 0, 1, 0, 0, 0, 0},
    };
    bool m_point[8] = {1, 1, 1, 1, 1, 1, 1, 0};
    ShiftRegister m_register;

public:
    SevenSegments();
    SevenSegments(
        uint8_t serialPin,
        uint8_t registerClock,
        uint8_t serialClock,
        uint8_t numberShiftRegister);
    void initSevenSegments();
    void print(uint8_t out);
    void print(uint8_t out, uint8_t num);
    ~SevenSegments();
};

#endif