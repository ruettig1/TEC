/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K
  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269
  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   2
#define MAXCS   3
#define MAXCLK  4
#define POWREL  7


// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// Example creating a thermocouple instance with hardware SPI
// on a given CS pin.
//#define MAXCS   10
//Adafruit_MAX31855 thermocouple(MAXCS);

int target_temp = 0;

typedef enum {On, Off} state;

static state power_relay_state = Off;

void setup() {
  
  pinMode(POWREL, OUTPUT);
  
  Serial.begin(9600);
 
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  
  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize

  Serial.println("Enter your desired temperature");

  while(!Serial.available()) //wait for user input to read from serial
  {
  }

  target_temp = Serial.parseInt();
  Serial.print("Target temp: ");
  Serial.println(target_temp);

  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("C = "); 
     Serial.println(c);
   }
   Serial.print("F = ");
   Serial.println(thermocouple.readFarenheit());

   if(int(thermocouple.readFarenheit()) > target_temp)
   {
      digitalWrite(POWREL, HIGH);
      Serial.println("Turning power relay on!");
   }
   else
   {
      digitalWrite(POWREL, LOW);
      Serial.println("Turning power relay off!");
   }
 
   delay(1000);
}



