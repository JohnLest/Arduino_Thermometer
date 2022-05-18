#ifndef DEF_SHIFTREGISTER
#define DEF_SHIFTREGISTER

#include <Arduino.h>

class ShiftRegister
{
private:
    uint8_t _serPin; 
    uint8_t _rClkPin;    
    uint8_t _sClkPin; 
    uint8_t _numberShiftRegister;
    short _numOfRegisterPins;
    boolean _registers[];

public:
    ShiftRegister();
    ShiftRegister(
        uint8_t serialPin, 
        uint8_t registerClock, 
        uint8_t serialClock, 
        uint8_t numberShiftRegister);
    void initRegister();
    void clearRegister();
    void writeRegister();
    void setRegisterPin(int index, int value);
    ~ShiftRegister();

};
#endif