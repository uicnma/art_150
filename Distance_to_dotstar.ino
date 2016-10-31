
#include <Adafruit_DotStar.h>

// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define PIXEL_COUNT  9  // Number of pixels in strand
#define DATAPIN    4
#define CLOCKPIN   5

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_DotStar strip  = Adafruit_DotStar(PIXEL_COUNT, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

// named constant for the pin the sensor is connected to
const int sensorPin = A1;
// room inches in Celcius
const float baselineTemp = 22.0; // based on average room temp in Celcius

const int trigPin = 2;
const int echoPin = 3;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);

  if (inches < 2) {
  colorWipe(strip.Color(80, 80, 80), 100);  // White
     Serial.println("white");
 // 
  }
  if (inches >= 2 && inches < 4) {
    colorWipe(strip.Color(8,2,0), 100); // Yellow
    //colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      Serial.println("yellow");
  } 
  
  // if the inches rises 2-4 degrees, turn an LED on
  else if (inches >= 4 && inches < 6) {
    //colorWipe(strip.Color(0, 255, 0), 50);  // Green
   colorWipe(strip.Color(12,1,0), 100); // Orange
    Serial.println("orange");
  } 
  
  // if the inches rises 4-6 degrees, turn a second LED on
  else if (inches >= 6 && inches < 8) {
  colorWipe(strip.Color(255, 0, 0), 100);  // pink
   Serial.println("pink");
 }
  
  // if the inches rises more than 6 degrees, turn all LEDs on
  else if (inches >= 8) {
    colorWipe(strip.Color(200, 0, 0), 100);  // Red
     Serial.println("red");
  }
  delay(1);


}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
