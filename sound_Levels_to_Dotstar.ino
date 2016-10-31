/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
 #include <Adafruit_DotStar.h>

// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS  9  // Number of pixels in strand
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
  
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

 int i = 0;

 byte
  val      = 0,      // Used for falling dot
  dotCount  = 0;      // Frame counter for delaying dot-falling speed

 #define MIC_PIN   A0  // Microphone is attached to this analog pin
 #define PEAK_FALL 40  // Rate of peak falling dot
 
void setup() 
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
    strip.begin();
    strip.show();  // Turn all LEDs off ASAP
   Serial.begin(9600);
}
 
void loop() 
{
    unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
   int volts2 = volts * 100;
 
   Serial.println(volts2);
   val = map(val, 9, volts2, 0, NUMPIXELS);
 
   // Color pixels based on rainbow gradient
  for(i=0; i<NUMPIXELS; i++) {
    if(i >= val)  strip.setPixelColor(i,   0,   0, 0) ;      
    else strip.setPixelColor(i,Wheel(map(i,0,strip.numPixels()-1,30,150))) ;
  }

  // Draw peak dot  
if(val > 0 && val <= NUMPIXELS-1) 
 strip.setPixelColor(val,Wheel(map(val,0,strip.numPixels()-1,30,150)));
// strip.setBrightness(val);
  strip.show(); // Update strip

// Every few frames, make the peak pixel drop by 1:

    if(++dotCount >= PEAK_FALL) { //fall rate    
      if(val > 0) val--;
      dotCount = 0;
    }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
