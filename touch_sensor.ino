/*
  Arduino Starter Kit example
 Project 13  - Touch Sensor Lamp
 This sketch is written to accompany Project 13 in the
 Arduino Starter Kit
 Parts required:
 1 Megohm resistor
 metal foil or copper mesh
 220 ohm resistor
 LED
 Software required :
 CapacitiveSensor library by Paul Badger
 http://arduino.cc/playground/Main/CapacitiveSensor
 Created 18 September 2012
 by Scott Fitzgerald
 http://arduino.cc/starterKit
 This example code is part of the public domain
 */

// import the library (must be located in the
// Arduino/libraries directory)
#include <CapacitiveSensor.h>

// create an instance of the library
// pin 4 sends electrical energy
// pin 2 senses senses a change
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);

// threshold for turning the lamp on
int threshold = 500;

// pin the LED is connected to
const int ledPin = 12;
int motorPin = 9;

void setup() {
  // open a serial connection
  Serial.begin(9600);
  // set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT); 
}

void loop() {
  // store the value reported by the sensor in a variable
  long sensorValue = capSensor.capacitiveSensor(30);

  // print out the sensor value
  Serial.println(sensorValue);

  // if the value is greater than the threshold
  if (sensorValue > threshold) {
    // turn the LED on
    digitalWrite(ledPin, HIGH);
    // digitalWrite(motorPin, HIGH);
     //analogWrite(motorPin, 150);
     
    for(int i = 0; i < 256; i++){ //goes through each speed from 0 to 255
    analogWrite(motorPin, i);   //sets the new speed
    delay(10);           // waits for delayTime milliseconds
  }
  }
  // if it's lower than the threshold
  else {
    // turn the LED off
    digitalWrite(ledPin, LOW);
      //digitalWrite(motorPin, LOW);
       //analogWrite(motorPin, 0);
      for(int i = 255; i >= 0; i--){ //goes through each speed from 255 to 0
    analogWrite(motorPin, i);   //sets the new speed
    delay(10);           // waits for delayTime milliseconds
  }}

  delay(10);
}
