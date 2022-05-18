#include "DHT.h"

#define BUTTON1 A1
#define BUTTON2 A2

const byte serPin = 8;     // Pin Serial
const byte rClkPin = 4;    // Register Clock
const byte sClkPin = 7;    // Serial Clock

// Combier de Registre a decallage y a t'il?
const int number_of_74hc595s = 2;
// Nombre total de sortie (nombre de registre * 8)
const int numOfRegisterPins = number_of_74hc595s * 8;
// Tableau qui donnera le nombre de pin total
boolean registers[numOfRegisterPins];

typedef struct Number {
  short value;
  bool led[8];
};
Number number[12] {
  // {A, B, C, D, E, F, G, DP}
  0, {0, 0, 0, 0, 0, 0, 1, 1},
  1, {1, 0, 0, 1, 1, 1, 1, 1},
  2, {0, 0, 1, 0, 0, 1, 0, 1},
  3, {0, 0, 0, 0, 1, 1, 0, 1},
  4, {1, 0, 0, 1, 1, 0, 0, 1},
  5, {0, 1, 0, 0, 1, 0, 0, 1},
  6, {0, 1, 0, 0, 0, 0, 0, 1},
  7, {0, 0, 0, 1, 1, 1, 1, 1},
  8, {0, 0, 0, 0, 0, 0, 0, 1},
  9, {0, 0, 0, 0, 1, 0, 0, 1},
  10, {1, 1, 0, 1 ,0, 0, 0, 0},
  11, {1, 1, 1, 0, 0, 1, 0, 0}
};

typedef struct Digit {
  short value;
  bool out[8];
};
Digit digit[4] {
  1, {1, 0, 0, 0, 0, 0, 0, 0},
  2, {0, 1, 0, 0, 0, 0, 0, 0},
  3, {0, 0, 1, 0, 0, 0, 0, 0},
  4, {0, 0, 0, 1, 0, 0, 0, 0},
};

bool point[8] = {1, 1, 1, 1, 1, 1, 1, 0};
bool showTemp = true;

DHT dht(5, DHT11);

void setup()
{
  pinMode(serPin, OUTPUT);
  pinMode(rClkPin, OUTPUT);
  pinMode(sClkPin, OUTPUT);

  dht.begin();
  //Serial.begin(9600);
  //reset de toutes les pin de sortie
  clearRegisters();
  writeRegisters();
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

void printTemp() {
  float t = getTemperature();
  String th = String(t, 1);
  th.remove(2, 1);
  printNumber(1, th.charAt(0) - '0');
  printNumber(2, th.charAt(1) - '0');
  printNumber(3, th.charAt(2) - '0');
  printNumber(4, 11);
  printPoint(2);
}

void printHum() {
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

//set toute les pin a LOW
void clearRegisters()
{
  for (int i = numOfRegisterPins - 1; i >= 0; i--)
    registers[i] = LOW;

  for (int i = numOfRegisterPins - 1; i >= 8 ; i--)
    registers[i] = HIGH;
}

void printNumber(short out, short num) {
  clearRegisters();
  for (int i = 0; i < 8; i++)
    setRegisterPin(i, digit[out - 1].out[i]);
  for (int i = 8; i < 16; i++)
    setRegisterPin(i, number[num].led[i - 8]);
  writeRegisters();
}

void printPoint(short out) {
  clearRegisters();
  for (int i = 0; i < 8; i++)
    setRegisterPin(i, digit[out - 1].out[i]);
  for (int i = 8; i < 16; i++)
    setRegisterPin(i, point[i - 8]);
  writeRegisters();
}

// affectation des valeurs enregistrées dans le tableau "registres" et application des valeurs �  la fin.
void writeRegisters()
{
  // tant que LOW les modifications ne seront pas affectées
  digitalWrite(rClkPin, LOW);

  // boucle pour affecter chaque pin du 74HC595
  for (int i = numOfRegisterPins - 1; i >= 0; i--)
  {
    // doit être à l'état bas pour changer de colonne plus tard
    digitalWrite(sClkPin, LOW);
    // récupération de la valeur dans le tableau registres
    int val = registers[i];
    // affecte la valeur sur la pin serPin correspondant à une pine du 74HC595
    digitalWrite(serPin, val);
    // colonne suivante
    digitalWrite(sClkPin, HIGH);
  }
  // applique toutes les valeurs au 74HC595
  digitalWrite(rClkPin, HIGH);
}

// enregistre une valeur pour un registre état haut ou bas
void setRegisterPin(int index, int valeur)
{
  registers[index] = valeur;
}