const int ledPin = 13; //the led attach to 
const int soundPin = A0;  

void setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(soundPin);
  Serial.println(value);
  if(value > 600)
  {
    digitalWrite(ledPin,HIGH);
    delay(200);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
}
