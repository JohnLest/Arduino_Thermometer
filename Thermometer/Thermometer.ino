#include "DHT.h"
#include "SevenSegments.h"
#include <TimerOne.h>

// Define three buttons
#define LEFT A1
#define SELECT A2
#define RIGHT A3

// Boolean if I push a button
bool m_press = false;
// Boolean if the chrono is start
bool m_chorono = false;
// Variable for choice the menu. 
uint8_t m_choice = 126;
// Seconde for the chrono
uint16_t m_seconde = 0;

// Constructor of SevenSegments with param :
// The serial input, the regster clock, the serial clock, and the total number of shift register.
// (The input pin 14, 12, 11 to the 74HC595)
SevenSegments sev_seg(8, 4, 7, 2);
// Constructor of DHT with param :
// Data and type of DHT
DHT dht(5, DHT11);

void setup()
{
  dht.begin();
  sev_seg.initSevenSegments();
  Timer1.initialize(10000);
  Timer1.attachInterrupt(countSec);
}

void loop()
{
  pressButton();
  menu();
}


// Methode for check if I press a button
void pressButton()
{
  if (!digitalRead(LEFT) && !m_press)
  {
    m_choice--;
    m_press = true;
  }
  if (!digitalRead(RIGHT) && !m_press)
  {
    m_choice++;
    m_press = true;
  }
  if (!digitalRead(SELECT) && !m_press && m_choice % 3 == 2)
  {
    m_chorono = !m_chorono;
    m_press = true;
  }
  if (digitalRead(RIGHT) && digitalRead(LEFT) && digitalRead(SELECT))
  {
    m_press = false;
  }
}

// Methode for Set the menu with `m_choice % 3`
void menu()
{
  uint8_t menu = m_choice % 3;
  if (!m_chorono && menu != 2)
    m_seconde = 0;
  switch (menu % 3)
  {
  case 0:
    printTemp();
    break;
  case 1:
    printHum();
    break;
  case 2:
    printChrono();
    break;
  }
}

// Get the temperature in Celsius with the DHT11
// return the temperature in float
float getTemperature()
{
  float t = dht.readTemperature();
  if (isnan(t))
  {
    return NULL;
  }
  return t;
}

// Get percentage of humidity with de DHT11
// Return the percentage in tiny Int
uint8_t getHumidity()
{
  uint8_t h = dht.readHumidity();
  if (isnan(h))
  {
    return NULL;
  }
  return h;
}

// If the Chrono is start, count the seconde
void countSec()
{
  if (!m_chorono)
    return;
  static uint8_t centiSec = 0;
  centiSec++;

  if (centiSec >= 100)
  {
    m_seconde++;
    centiSec = 0;
  }
}

// Print the temperature to the seven segments
void printTemp()
{
  float t = getTemperature();
  sev_seg.print(1, int(t / 10) % 10);
  sev_seg.print(2, int(t) % 10);
  sev_seg.print(2);
  sev_seg.print(3, int(t * 10) % 10);
  sev_seg.print(4, 11);
}

// Print the humidity to the seven segments
void printHum()
{
  uint8_t h = getHumidity();
  sev_seg.print(1, 10);
  sev_seg.print(3, (h / 10) % 10);
  sev_seg.print(4, (h) % 10);
}

// Print the time of the chronometer
void printChrono()
{
  uint8_t min = m_seconde / 60;
  uint8_t sec = m_seconde % 60;

  sev_seg.print(1, (min / 10) % 10);
  sev_seg.print(2, (min) % 10);
  sev_seg.print(2);
  sev_seg.print(3, (sec / 10) % 10);
  sev_seg.print(4, (sec) % 10);
}
