#ifndef DEF_SHIFTREGISTER
#define DEF_SHIFTREGISTER

#include <Arduino.h>

class ShiftRegister
{
private:
    // Serial input (pin 14 to the 74HC595)
    uint8_t m_serPin; 
    // Register clock (pin 12 to the 74HC595) 
    uint8_t m_rClkPin;
    // Serial clock (pin 11 to the 74HC595)
    uint8_t m_sClkPin; 
    // Total number of shift register
    uint8_t m_numberShiftRegister;
    // Total output shift register pin 
    short m_numOfRegisterPins;
    // Table for work with the shift register
    boolean m_registers[];

public:
    // Empty constructor
    ShiftRegister();
    // Constructor of SevenSegments with param : 
    // The serial input, the regster clock, the serial clock, and the total number of shift register.
    // (The input pin 14, 12, 11 to the 74HC595) 
    ShiftRegister(
        uint8_t serialPin, 
        uint8_t registerClock, 
        uint8_t serialClock, 
        uint8_t numberShiftRegister);
    // Method that must be initialized in the Arduino Setup
    void initRegister();
    // Set all values of m_register[] to 1
    void clearRegister();
    // Send m_register[] to the shift register
    void writeRegister();
    // Set m_register[] with an index and a value
    void setRegisterPin(short index, bool value);
    // Destructor
    ~ShiftRegister();

};
#endif