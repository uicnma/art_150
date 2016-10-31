/*
  For Loop Iteration

 Demonstrates the use of a for() loop.
 Lights multiple LEDs in sequence, then in reverse.

 The circuit:
 * LEDs from pins 2 through 7 to ground

 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/ForLoop
 */

 int pirPin = 2;

int timer = 300;           // The higher the number, the slower the timing.

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 3; thisPin < 9; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop() {

 //int reading = digitalRead(pirPin);
 //Serial.println(reading);
 
while (digitalRead(pirPin) == HIGH) {
  animation();
 
  }

  //else {
    //  for (int thisPin = 3; thisPin < 9; thisPin++) {  ////////////// 3 + 9 instead of 2 and 8
   // digitalWrite(thisPin, LOW);
   // delay(1000);
 // }
  //}
 
  
}

void animation () {
   // loop from the lowest pin to the highest: 
  for (int thisPin = 3; thisPin < 9; thisPin++) {  ////////////// 3 + 9 instead of 2 and 8
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(thisPin, LOW);
   
  }

  // loop from the highest pin to the lowest:
  for (int thisPin = 9; thisPin >= 3; thisPin--) { /////////////////  8 + 3 instead of 7 and 2
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(thisPin, LOW);
  }

}
