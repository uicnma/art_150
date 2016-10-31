
//Force Sensor to Light Fade

//turn on the serial statements to DEBUG
//add in mapping statements to make for a better response

int ForceSensePin = A2;
int ledPin = 9;
int ForceSensorValue;

void setup() {
    pinMode (ledPin, OUTPUT);
    //Serial.begin(9600);
}

void loop() {
    ForceSensorValue = analogRead(ForceSensePin);
     analogWrite(ledPin, ForceSensorValue);
     
    // apply the calibration to the sensor reading
    //ForceSensorValue = map(ForceSensorValue, 0, 1023, 0, 255);

    // in case the sensor value is outside the range seen during calibration
    //ForceSensorValue = constrain(ForceSensorValue, 0, 255);
    
    // Serial.println(ForceSensorValue);
}

