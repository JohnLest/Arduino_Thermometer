#include "ShiftRegister.h"

ShiftRegister::ShiftRegister() {}

ShiftRegister::ShiftRegister(
    uint8_t serialPin,
    uint8_t registerClock,
    uint8_t serialClock,
    uint8_t numberShiftRegister)
{
    _serPin = serialPin;
    _rClkPin = registerClock;
    _sClkPin = serialClock;
    _numberShiftRegister = numberShiftRegister;
    _numOfRegisterPins = _numberShiftRegister * 8;
    _registers[_numOfRegisterPins];
}

void ShiftRegister::initRegister()
{
    pinMode(_serPin, OUTPUT);
    pinMode(_rClkPin, OUTPUT);
    pinMode(_sClkPin, OUTPUT);
    clearRegister();
    writeRegister();
}
void ShiftRegister::clearRegister()
{
    for (int i = _numOfRegisterPins - 1; i >= 0; i--)
        _registers[i] = LOW;
}
void ShiftRegister::writeRegister()
{
    digitalWrite(_rClkPin, LOW);
    for (int i = _numOfRegisterPins - 1; i >= 0; i--)
    {
        digitalWrite(_sClkPin, LOW);
        int val = _registers[i];
        digitalWrite(_serPin, val);
        digitalWrite(_sClkPin, HIGH);
    }
    digitalWrite(_rClkPin, HIGH);
}
void ShiftRegister::setRegisterPin(int index, int value)
{
    _registers[index] = value;
}

ShiftRegister::~ShiftRegister() {}
