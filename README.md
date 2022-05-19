# Arduino Thermomter
---
This project was created in order to be able to take the temperature and the percentage of humidity in my kitchen.
For the display I use a seven segment display on the multi-function shield and for the data sensor I use a DHT11

## The Multi-Function Shield
---
The multi-function shield features some most useful electronics divided into segments : [1]

 - Four LEDs
 - Three pushbuttons
 - A reset button
 - A piezo-buzzer
 - An LED display module (four-digit, seven-segment)
 - Two serial LED display driver ICs(74HC595)
 - A multi-turn trimpot (10K)
 - A port for DS18B20 temperature sensor
 - A port for TSOP1838 infrared receiver module
 - A APC220 wireless module interface (serial/UART interface)
![alt text](https://raw.githubusercontent.com/JohnLest/Arduino_Thermometer/main/Resources/MultifunctionShield-Schematic.webp) 

For this project I only use the two `serial LED display driver ICs (74HC595)` and the `LED display module`, as well as two pushbuttons.

## The DHT11 sensor
---
DHT11 is a low-cost digital sensor for sensing temperature and humidity. The temperature range of DHT11 is from 0 to 50 degree Celsius with a 2-degree accuracy. Humidity range of this sensor is from 20 to 80% with 5% accuracy. The sampling rate of this sensor is 1Hz .i.e. it gives one reading for every second.  DHT11 is small in size with operating voltage from 3 to 5 volts. The maximum current used while measuring is 2.5mA. [2]

The DHT11 is plugged into `Header 3` on the Multi-Function Shield



[1]: https://www.electroschematics.com/getting-started-with-the-arduino-multifunction-shield/
[2]: https://www.elprocus.com/a-brief-on-dht11-sensor/
