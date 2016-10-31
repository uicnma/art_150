/*
 * A simple programme that will change the intensity of
 * an LED based  * on the amount of light incident on 
 * the photo resistor.
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
                  
int buzzerPin = 4; // Connect Buzzer to Pin 4
long buzzerFreq; // The frequency to buzz the buzzer
// You can experiment with these values:
long BUZZ_FREQ_MAX = 32000; // Maximum frequency for the buzzer 
// keep increasing BUZZ_FREQ_MAX until you get the full range
long PR_MAX = 865; // Maximum value for the photoresistor




void setup() {
  pinMode(ledPin, OUTPUT); //sets the led pin to output
  pinMode(buzzerPin, OUTPUT); // set a pin for buzzer output
}

 /*
 * loop() - this function will start after setup 
 * finishes and then repeat
 */

void loop() {
 int lightLevel = analogRead(lightPin); //Read the
                                        // lightlevel

 lightLevel = map(lightLevel, 500, 865, 0, 255); 
         //adjust the value 0 to 900 to
         //span 0 to 255
         // go higher than 500 if the circuit is not turning off
 
 buzzerFreq = (lightLevel * BUZZ_FREQ_MAX) / PR_MAX;
 buzz(buzzerPin, buzzerFreq, 10);
         
 lightLevel = constrain(lightLevel, 0, 255);//make sure the 
                                           //value is between 
                                           //0 and 255
 analogWrite(ledPin, lightLevel);  //write the value
 
 buzzerFreq = (lightLevel * BUZZ_FREQ_MAX) / PR_MAX;
 buzz(buzzerPin, buzzerFreq, 10);
 // increase the third variable, long length to hear more stepping in tones 
 // try values 10 through 100
}

void buzz(int targetPin, long frequency, long length) {
    long delayValue = 1000000/frequency/2;
    long numCycles = frequency * length/ 1000;
    for (long i=0; i < numCycles; i++){
        digitalWrite(targetPin,HIGH);
        delayMicroseconds(delayValue);
        digitalWrite(targetPin,LOW);
        delayMicroseconds(delayValue);
    }
}
