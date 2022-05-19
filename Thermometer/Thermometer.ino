#include "DHT.h"
#include "SevenSegments.h"

#define BUTTON1 A1
#define BUTTON2 A2

bool showTemp = true;

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

// Print the temperature to the seven segments
void printTemp()
{
  float t = getTemperature();
  sev_seg.print(1, int(t/10)%10);
  sev_seg.print(2, int(t)%10);
  sev_seg.print(2);
  sev_seg.print(3, int(t*10)%10);
  sev_seg.print(4, 11);
}

// Print the humidity to the seven segments 
void printHum()
{
  uint8_t h = getHumidity();
  sev_seg.print(1, 10);
  sev_seg.print(3, (h/10)%10);
  sev_seg.print(4, (h)%10);
}
