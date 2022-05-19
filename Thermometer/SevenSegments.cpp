#include "SevenSegments.h"

SevenSegments::SevenSegments() {}
SevenSegments::SevenSegments(
    uint8_t serialPin,
    uint8_t registerClock,
    uint8_t serialClock,
    uint8_t numberShiftRegister)
    : m_register(serialPin, registerClock, serialClock, numberShiftRegister){}

void SevenSegments::initSevenSegments()
{
    m_register.initRegister();
}

void SevenSegments::print(uint8_t out)
{
    m_register.clearRegister();
    for (short i = 0; i < 8; i++)
        m_register.setRegisterPin(i, m_digit[out - 1].out[i]);
    for (short i = 8; i < 16; i++)
        m_register.setRegisterPin(i, m_point[i - 8]);
    m_register.writeRegister();
}
void SevenSegments::print(uint8_t out, uint8_t num)
{
    m_register.clearRegister();
    for (short i = 0; i < 8; i++)
        m_register.setRegisterPin(i, m_digit[out - 1].out[i]);
    for (short i = 8; i < 16; i++)
        m_register.setRegisterPin(i, m_number[num].led[i - 8]);
    m_register.writeRegister();
}

SevenSegments::~SevenSegments() {}