/*     -----------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code               |
 *     |  CIRC-03 .: Spin Motor Spin :. (Transistor and Motor)   |
 *     -----------------------------------------------------------
 * 

 */


 //PhotoResistor Pin
int lightPin = A0; //the analog pin the photoresistor is 
                  //connected to
                  //the photoresistor is not calibrated to any units so
                  //this is simply a raw sensor value (relative light)
//LED Pin
int ledPin = 9;   //the pin the LED is connected to
                  //we are controlling brightness so 
                  //we use one of the PWM (pulse width
                  // modulation pins)
                  
int motorPin = 3;  // define the pin the motor is connected to
                   // (if you use pin 9,10,11 or 3 you can also control speed)                                    

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the motors pin to be an output (turning the pin high (+5v) or low (ground) (-))
 * rather than an input (checking whether a pin is high or low)
 */
void setup()
{
 pinMode(motorPin, OUTPUT); 
 pinMode(ledPin, OUTPUT); //sets the led pin to output
 Serial.begin(9600);
}


/*
 * loop() - this function will start after setup finishes and then repeat
 * we call a function called motorOnThenOff()
 */

void loop()                     // run over and over again
{
int lightLevel = analogRead(lightPin); //Read the
                                        // lightlevel

 lightLevel = map(lightLevel, 185, 560, 0, 3); 
         //adjust the value 0 to 900 to
         //span 0 to 255
         // go higher than 500 if the circuit is not turning off
 lightLevel = constrain(lightLevel, 0, 3);//make sure the 
                                           //value is between 
                                           //0 and 255
   // do something different depending on the
// range value:
switch (lightLevel) {
case 0: // your hand is on the sensor
Serial.println("dark");
analogWrite(ledPin, 0);  //write the value
 analogWrite(motorPin, 0);   //sets the new speed
break;
case 1: // your hand is close to the sensor
Serial.println("dim");
analogWrite(ledPin, 70);  //write the value
 analogWrite(motorPin, 70);   //sets the new speed
break;
case 2: // your hand is a few inches from the sensor
Serial.println("medium");
analogWrite(ledPin, 140);  //write the value
 analogWrite(motorPin, 140);   //sets the new speed
break;
case 3: // your hand is nowhere near the sensor
Serial.println("bright");
analogWrite(ledPin, 255);  //write the value
analogWrite(motorPin, 200);   //sets the new speed
break;                                        
}
 
}

