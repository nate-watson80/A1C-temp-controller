/* temperatureController-nw.ino
 *  Temperature regulation software
 *  Written by: Nate Watson
 *  12/5/2018
 */


#include <EEPROM.h> // Include EEPROM library

//TMP36 Pin Variables
int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
int heatPin = 5;
int fanPin = 10;
int target = 23;

float hyst = 3;
float tempMax = target + hyst;
float tempMin = target - hyst;

// Track when to store values
int counter = 0;
int index = 0;


void setup() {
  /* setup() is a module to initiate the system.
  Begin serial monitor and initialize system units as outputs
  */

  Serial.begin(9600);  //Start the serial connection with the computer
  //Initialize all to LOW
  pinMode(heatPin, OUTPUT);
  digitalWrite(heatPin,LOW);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
}

void loop() {
  /* loop() is the main iterating loop.
  (1) Check to see if EEPROM has space left on its memory.
  (2) Take temperature measurement.
  (3) Turn on appropriate regulatoion units.
  (4) Save measurement in EEPROM memory.
  */

  // End the main loop if EEPROM memory is full
  if (index ==EEPROM.length()) {
     return;
  }

  // Take temperature reading:
  float temperatureC, reading = takeReading();

  Serial.println(temperatureC);

  // Based on temperature turn units on or off:
  controller(temperatureC);

  // Save a value every 20 readings
  if (counter % 2 == 0) { // save temperature every 2 seconds
     EEPROM.write(index, reading);
     index++;
  }
  counter++;
  delay(1000);  //Delay system 1 second to slow down readings
}


float takeReading() {
  /* takeReading()
  This module takes a raw reading from analog pin and converts it to degC
  */
  float reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temp = (voltage - 0.5) * 100;  //converting from 10 mv per degree wit 500 mV offset
  return temp, reading;
}

void controller(float temp_input) {

  /* controller() is a module to turn on appropriate regulation units.
  Cut off values of tempMax and tempMin define switching behavior.
  */
  if (temp_input >= tempMax) {
     digitalWrite(heatPin, LOW);
     digitalWrite(fanPin, HIGH);
  }
  if (temp_input <= tempMin) {
     digitalWrite(heatPin, HIGH);
     digitalWrite(fanPin, LOW);
  }
  if (temp_input > tempMin && temp_input <= tempMax) {
     digitalWrite(heatPin, LOW);
     digitalWrite(fanPin, LOW);
  }
}
