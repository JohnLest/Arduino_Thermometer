#include "DHT.h"
#include "SevenSegments.h"

#define BUTTON1 A1
#define BUTTON2 A2

bool showTemp = true;

SevenSegments sev_seg(8, 4, 7, 2);
DHT dht(5, DHT11);

void setup()
{
  dht.begin();
  sev_seg.initSevenSegments();
  Serial.begin(9600);
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
  //Serial.println(showTemp);
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

float getHumidity()
{
  float h = dht.readHumidity();
  if (isnan(h))
  {
    return NULL;
  }
  return h;
}

void printTemp()
{
  float t = getTemperature();
  sev_seg.print(1, int(t/10)%10);
  sev_seg.print(2, int(t)%10);
  sev_seg.print(2);
  sev_seg.print(3, int(t*10)%10);
  sev_seg.print(4, 11);
}

void printHum()
{
  float h = getHumidity();
  sev_seg.print(1, 10);
  sev_seg.print(3, int(h/10)%10);
  sev_seg.print(4, int(h)%10);
}
