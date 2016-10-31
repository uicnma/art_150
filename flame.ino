const int analogInPin = A0;
const int digitalInPin = 8;
const int ledPin = 13;
const int buzzerPin=7;

void setup()
{
  pinMode(digitalInPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  pinMode(buzzerPin,OUTPUT);
}

void loop()
{
  int analogVal = analogRead(analogInPin);
  Serial.println(analogVal);
  boolean stat = digitalRead(digitalInPin);
  if(stat == HIGH)
  {
    digitalWrite(ledPin,LOW);
    noTone(7);//if you want to play different pitches on multiple pins, you need to call noTone() on one pin before calling tone() on the next pin.
  }
  if(stat == LOW)
  {
    digitalWrite(ledPin,HIGH);
  tone(7,320,200);//in pin7 generate a tone ,it's frequency is 320hz and the duration of the tone is 500 milliseconds
  }
}
