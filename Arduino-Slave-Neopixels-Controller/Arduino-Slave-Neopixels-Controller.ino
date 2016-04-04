// Ref: https://www.arduino.cc/en/Tutorial/MasterWriter
// Neopixels: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library

#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define NUM_PIXELS 12

#define delayTime 1000

const int LEDPin = 13; // To see if it blinks

//TimeKeeper Code

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t counterTime=0;

int arbitaryDeviceNum = 8;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
    // End of trinket special code

  
  Wire.begin(arbitaryDeviceNum);  // join i2c bus with address #8

  Serial.begin(9600); // Start serial for output

  pinMode(LEDPin, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}



void loop(){
  
//  byte b = 10;
//  Serial.println( (int) b); //10
  
  colorWipe(strip.Color(10, 0, 0), 150); // Dim Red
  Wire.onReceive(receiveEvent); // register event
  delay(100);
}



// Function that executes whenever data is received from master
// This function is registered as an event, see setup()
void receiveEvent(int howMany) {
  
  
//  while (1 < Wire.available()) { // loop through all but the last
//    char c = Wire.read(); // receive byte as a character
//    Serial.print(c);         // print the character
//  }

 
  int x = (int)Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

  if(x == 0){
    colorWipe(strip.Color(0, 80, 0), 150); // Dim Green 
  }
  else{
    colorWipe(strip.Color(0, 0, 50), 150); // Dim Blue
  }

}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
