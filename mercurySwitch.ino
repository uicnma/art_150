const int buttonPin = 7;     // the number of the Mercury Switch pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
boolean buttonState = 0;         // variable for reading the Mercury Switch status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the Mercury Switch pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the Mercury Switch value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) 
  {       
    digitalWrite(ledPin, LOW);  
  } 
  else 
  {
    digitalWrite(ledPin, HIGH); 
  }
}
