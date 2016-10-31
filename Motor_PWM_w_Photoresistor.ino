/*     -----------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code               |
 *     |  CIRC-03 .: Spin Motor Spin :. (Transistor and Motor)   |
 *     -----------------------------------------------------------
 * 

 */


 //PhotoResistor Pin
int lightPin = 0; //the analog pin the photoresistor is 
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
}


/*
 * loop() - this function will start after setup finishes and then repeat
 * we call a function called motorOnThenOff()
 */

void loop()                     // run over and over again
{
int lightLevel = analogRead(lightPin); //Read the
                                        // lightlevel

 lightLevel = map(lightLevel, 185, 560, 0, 255); 
         //adjust the value 0 to 900 to
         //span 0 to 255
         // go higher than 500 if the circuit is not turning off
 lightLevel = constrain(lightLevel, 0, 255);//make sure the 
                                           //value is between 
                                           //0 and 255
                                           
 analogWrite(ledPin, lightLevel);  //write the value
 analogWrite(motorPin, lightLevel);   //sets the new speed
 
}

