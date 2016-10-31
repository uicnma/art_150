/*
  Arduino Starter Kit example
 Project 3  - Love-O-Meter

 This sketch is written to accompany Project 3 in the
 Arduino Starter Kit

 Parts required:
 1 TMP36 temperature sensor
 3 red LEDs
 3 220 ohm resistors

 Created 13 September 2012
 by Scott Fitzgerald

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
 */

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
// room temperature in Celcius
const float baselineTemp = 22.0; // based on average room temp in Celcius

void setup() {
  Serial.begin(9600); // open a serial connection to display values
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // read the value on AnalogIn pin 0
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // send the 10-bit sensor value out the serial port
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);

  // convert the ADC reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;

  // Send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((volatge - 500mV) times 100)
  
  Serial.print(", degrees C: ");
  float temperature = sensorVal * 0.48828125; //gives celcius value
   Serial.print(temperature);
   Serial.print(", degrees F: ");
  float farh = (temperature *9.0)/5.0 + 32.00;  // far temp
  Serial.print(farh);
  // if the current temperature is lower than the baseline
  // turn off all LEDs

 Serial.print(", Color : ");
  
  if (temperature < baselineTemp + 1) {
  colorWipe(strip.Color(80, 80, 80), 100);  // White
     Serial.println("white");
 // 
  }
  if (temperature >= baselineTemp + 1.0 && temperature < baselineTemp + 2.0) {
    colorWipe(strip.Color(8,2,0), 100); // Yellow
    //colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      Serial.println("yellow");
  } 
  
  // if the temperature rises 2-4 degrees, turn an LED on
  else if (temperature >= baselineTemp + 2.0 && temperature < baselineTemp + 4.0) {
    //colorWipe(strip.Color(0, 255, 0), 50);  // Green
   colorWipe(strip.Color(12,1,0), 100); // Orange
    Serial.println("orange");
  } 
  
  // if the temperature rises 4-6 degrees, turn a second LED on
  else if (temperature >= baselineTemp + 4.0 && temperature < baselineTemp + 6.0) {
  //  colorWipe(strip.Color(255, 0, 0), 100);  // pink
     colorWipe(strip.Color(255, 40, 40), 100); // Hot Pink

  //Throb read and then fade out
  heartThrob(20);
   Serial.println("pink");
 }
  
  // if the temperature rises more than 6 degrees, turn all LEDs on
  else if (temperature >= baselineTemp + 6.0) {
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

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void heartThrob(uint8_t wait) {
  uint16_t i, j;

  //Adjust 60 and 90 to the starting and ending colors you want to fade between. 
  for(j=0; j<8; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
 //   strip.show();
 // delay(wait);
  }
}
