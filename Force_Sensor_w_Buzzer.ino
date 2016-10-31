
//Force Sensor to Light Fade

//turn on the serial statements to DEBUG
//add in mapping statements to make for a better response

int ForceSensePin = A2;
int ledPin = 9;
int ForceSensorValue;
int buzzerPin = 4; // Connect Buzzer to Pin 4
long buzzerFreq; // The frequency to buzz the buzzer
// You can experiment with these values:
long BUZZ_FREQ_MAX = 24000; // Maximum frequency for the buzzer 
// keep increasing BUZZ_FREQ_MAX until you get the full range
long PR_MAX = 1023; // Maximum value for the forceResistor

void setup() {
    pinMode (ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT); // set a pin for buzzer output
    //Serial.begin(9600);
}

void loop() {
    ForceSensorValue = analogRead(ForceSensePin);
     analogWrite(ledPin, ForceSensorValue);
    // apply the calibration to the sensor reading
    ForceSensorValue = map(ForceSensorValue, 0, 1023, 0, 255);

    // in case the sensor value is outside the range seen during calibration
    ForceSensorValue = constrain(ForceSensorValue, 0, 255);
    
    buzzerFreq = (ForceSensorValue * BUZZ_FREQ_MAX) / PR_MAX;
    buzz(buzzerPin, buzzerFreq, 50);
     // increase the third variable, long length to hear more stepping in tones 
     // try values 10 through 100
     
    // Serial.println(ForceSensorValue);
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
