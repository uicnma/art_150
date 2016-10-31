/*     -----------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code               |
 *     |  CIRC-03 .: Spin Motor Spin :. (Transistor and Motor)   |
 *     -----------------------------------------------------------
 * 
 * The Arduinos pins are great for driving LEDs however if you hook 
 * up something that requires more power you will quickly break them.
 * To control bigger items we need the help of a transistor. 
 * Here we will use a transistor to control a small toy motor
 * 
 * http://tinyurl.com/d4wht7
 *
 */

int motorPin = 3;  // define the pin the motor is connected to
                   // (if you use pin 9,10,11 or 3you can also control speed)
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the motors pin to be an output (turning the pin high (+5v) or low (ground) (-))
 * rather than an input (checking whether a pin is high or low)
 */
void setup()
{
 pinMode(motorPin, OUTPUT); 
 pinMode(buttonPin, INPUT);   
}


/*
 * loop() - this function will start after setup finishes and then repeat
 * we call a function called motorOnThenOff()
 */

void loop()                     // run over and over again
{
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
   // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
     
    digitalWrite(motorPin, HIGH); // turns the motor On 
  } 
  else {
    // turn motor off:
   digitalWrite(motorPin, LOW); // turns the motor off 
  }

}

