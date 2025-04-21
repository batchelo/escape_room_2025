#include <Adafruit_NeoPixel.h>

#define Pixel_pin 15// Which pin a particular line of leds is connected to

#define NUMPIXELS 6 // Number of NeoPixels are attached to the Arduino?

Adafruit_NeoPixel pixels(NUMPIXELS, Pixel_pin, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object

}

void loop() 
{
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(0, pixels.Color(255,0,0)); //red
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.setPixelColor(2, pixels.Color(0,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,0));
  pixels.setPixelColor(4, pixels.Color(0,0,0));
  pixels.setPixelColor(5, pixels.Color(0,0,0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(2000);
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,255,0)); //green
  pixels.setPixelColor(2, pixels.Color(0,0,255)); //blue
  pixels.setPixelColor(3, pixels.Color(0,0,255));
  pixels.setPixelColor(4, pixels.Color(0,0,255));
  pixels.setPixelColor(5, pixels.Color(0,255,0));
  pixels.show(); 
  delay(2000);
  }