#include "ShiftRegister.h"

ShiftRegister::ShiftRegister() {}

ShiftRegister::ShiftRegister(
    uint8_t serialPin,
    uint8_t registerClock,
    uint8_t serialClock,
    uint8_t numberShiftRegister)
{
    m_serPin = serialPin;
    m_rClkPin = registerClock;
    m_sClkPin = serialClock;
    m_numberShiftRegister = numberShiftRegister;
    m_numOfRegisterPins = m_numberShiftRegister * 8;
    m_registers[m_numOfRegisterPins];
}

void ShiftRegister::initRegister()
{
    pinMode(m_serPin, OUTPUT);
    pinMode(m_rClkPin, OUTPUT);
    pinMode(m_sClkPin, OUTPUT);
    clearRegister();
    writeRegister();
}
void ShiftRegister::clearRegister()
{
    for (short i = m_numOfRegisterPins - 1; i >= 0; i--)
        m_registers[i] = LOW;
}
void ShiftRegister::writeRegister()
{
    digitalWrite(m_rClkPin, LOW);
    for (short i = m_numOfRegisterPins - 1; i >= 0; i--)
    {
        digitalWrite(m_sClkPin, LOW);
        bool val = m_registers[i];
        digitalWrite(m_serPin, val);
        digitalWrite(m_sClkPin, HIGH);
    }
    digitalWrite(m_rClkPin, HIGH);
}
void ShiftRegister::setRegisterPin(short index, bool value)
{
    m_registers[index] = value;
}

ShiftRegister::~ShiftRegister() {}
