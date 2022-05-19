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
    // Code for print the number `0` to `9` and `h.` and `c.`
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
        10,{1, 1, 0, 1, 0, 0, 0, 0},  // Code for print `h.`
        11,{1, 1, 1, 0, 0, 1, 0, 0}}; // Code for print `c.`

    typedef struct Digit
    {
        uint8_t value;
        bool out[8];
    };
    // Code for the digit output
    Digit m_digit[4]{
        1,{1, 0, 0, 0, 0, 0, 0, 0},
        2,{0, 1, 0, 0, 0, 0, 0, 0},
        3,{0, 0, 1, 0, 0, 0, 0, 0},
        4,{0, 0, 0, 1, 0, 0, 0, 0},
    };
    // Code for print a dot
    bool m_point[8] = {1, 1, 1, 1, 1, 1, 1, 0};
    // Shiftregister object
    ShiftRegister m_register;

public:
    // Empty constructor
    SevenSegments();
    // Constructor of SevenSegments with param : 
    // The serial input, the regster clock, the serial clock, and the total number of shift register.
    // (The input pin 14, 12, 11 to the 74HC595)
    SevenSegments(
        uint8_t serialPin,
        uint8_t registerClock,
        uint8_t serialClock,
        uint8_t numberShiftRegister);
    // Method that must be initialized in the Arduino Setup
    void initSevenSegments();
    // Print with the seven segments a dot to the specific digit 
    void print(uint8_t out);
    // Print with the seven segments a digit to the specific digit
    void print(uint8_t out, uint8_t num);
    // Destructor
    ~SevenSegments();
};

#endif