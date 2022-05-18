#include "DHT.h"
#include "ShiftRegister.h"

#define BUTTON1 A1
#define BUTTON2 A2

ShiftRegister reg(8, 4, 7, 2);

typedef struct Number
{
  short value;
  bool led[8];
};
Number number[12]{
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
  short value;
  bool out[8];
};
Digit digit[4]{
    1,{1, 0, 0, 0, 0, 0, 0, 0},
    2,{0, 1, 0, 0, 0, 0, 0, 0},
    3,{0, 0, 1, 0, 0, 0, 0, 0},
    4,{0, 0, 0, 1, 0, 0, 0, 0},
};

bool point[8] = {1, 1, 1, 1, 1, 1, 1, 0};
bool showTemp = true;

DHT dht(5, DHT11);

void setup()
{
  reg.initRegister();
  dht.begin();
  // Serial.begin(9600);
}

void loop()
{
  if (!digitalRead(BUTTON1))
    showTemp = true;
  if (!digitalRead(BUTTON2))
    showTemp = false;
  if (showTemp)
    printTemp();
  else
    printHum();
}

float getTemperature()
{
  float t = dht.readTemperature();
  if (isnan(t))
  {
    return NULL;
  }
  return t;
}

void printTemp()
{
  float t = getTemperature();
  String th = String(t, 1);
  th.remove(2, 1);
  printNumber(1, th.charAt(0) - '0');
  printNumber(2, th.charAt(1) - '0');
  printNumber(3, th.charAt(2) - '0');
  printNumber(4, 11);
  printPoint(2);
}

void printHum()
{
  float h = getHumidity();
  String hum = String(int(h));
  printNumber(1, 10);
  printNumber(3, hum.charAt(0) - '0');
  printNumber(4, hum.charAt(1) - '0');
}
float getHumidity()
{
  float h = dht.readHumidity();
  if (isnan(h))
  {
    return NULL;
  }
  return h;
}

void printNumber(short out, short num)
{
  reg.clearRegister();
  for (int i = 0; i < 8; i++)
    reg.setRegisterPin(i, digit[out - 1].out[i]);
  for (int i = 8; i < 16; i++)
    reg.setRegisterPin(i, number[num].led[i - 8]);
  reg.writeRegister();
}

void printPoint(short out)
{
  reg.clearRegister();
  for (int i = 0; i < 8; i++)
    reg.setRegisterPin(i, digit[out - 1].out[i]);
  for (int i = 8; i < 16; i++)
    reg.setRegisterPin(i, point[i - 8]);
  reg.writeRegister();
}
