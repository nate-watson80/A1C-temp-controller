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


void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
  //Initialize all to LOW
  pinMode(heatPin, OUTPUT);
  digitalWrite(heatPin,LOW);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
}

void loop()                     // run over and over again
{
 if (index ==EEPROM.length()) { // Kill if filled up EEPROM
    return;
 }
 //getting the voltage reading from the temperature sensor and converting to temp.
 float reading = analogRead(sensorPin);
 float voltage = reading * 5.0;
 voltage /= 1024.0;
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100
  Serial.println(temperatureC);

// Controller
 if (temperatureC >= tempMax) {
    digitalWrite(heatPin, LOW);
    digitalWrite(fanPin, HIGH);
 }
 if (temperatureC <= tempMin) {
    digitalWrite(heatPin, HIGH);
    digitalWrite(fanPin, LOW);
 }
 if (temperatureC > (target - hyst) && temperatureC <= (target+hyst)) {
    digitalWrite(heatPin, LOW);
    digitalWrite(fanPin, LOW);
 }

// Save a value every 20 readings
 if (counter % 2 == 0) {                         // save temperature every 20 seconds
    EEPROM.write(index, reading);
    index++;
 }
 counter++;
 delay(1000);                                     //waiting 1 second
}
