#include <Adafruit_NeoPixel.h>

#define Pixel_pin_a 18 // Which pin a particular line of leds is connected to
#define Pixel_pin_b 14
#define Pixel_pin_c 23
#define Pixel_pin_d 19
#define NUMPIXELS 4 // Number of NeoPixels are attached to the Arduino?

Adafruit_NeoPixel pixels_a(NUMPIXELS, Pixel_pin_a, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_b(NUMPIXELS, Pixel_pin_b, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_c(NUMPIXELS, Pixel_pin_c, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_d(NUMPIXELS, Pixel_pin_d, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels_a.begin(); // INITIALIZE NeoPixel strip object
  pixels_b.begin();
  pixels_c.begin();
  pixels_d.begin();
}
void loop() 
{
  pixels_a.clear(); // Set all pixel colors to 'off'
  pixels_a.setPixelColor(0, pixels_a.Color(255,0,0)); //red
  pixels_a.setPixelColor(1, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(2, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(3, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(4, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(5, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(6, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(7, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(8, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(9, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(10,pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(11,pixels_a.Color(0,0,0));  
  pixels_a.show();   // Send the updated pixel colors to the hardware.
  delay(20);
  pixels_b.clear(); // Set all pixel colors to 'off'
  pixels_b.setPixelColor(0, pixels_b.Color(255,0,0)); //red
  pixels_b.setPixelColor(1, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(2, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(3, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(4, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(5, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(6, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(7, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(8, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(9, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(10,pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(11,pixels_b.Color(0,0,0));  
  pixels_b.show();
  delay(20); 
  //Send the updated pixel colors to the hardware.
  pixels_c.clear(); // Set all pixel colors to 'off'
  pixels_c.setPixelColor(0, pixels_c.Color(255,0,0)); //red
  pixels_c.setPixelColor(1, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(2, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(3, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(4, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(5, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(6, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(7, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(8, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(9, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(10,pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(11,pixels_c.Color(0,0,0));  
  pixels_c.show();   // Send the updated pixel colors to the hardware.
  delay(20);
  pixels_d.clear(); // Set all pixel colors to 'off'
  pixels_d.setPixelColor(0, pixels_d.Color(255,0,0)); //red
  pixels_d.setPixelColor(1, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(2, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(3, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(4, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(5, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(6, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(7, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(8, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(9, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(10,pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(11,pixels_d.Color(0,0,0));  
  pixels_d.show();   // Send the updated pixel colors to the hardware
  delay(2000);
  pixels_a.setPixelColor(0, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(1, pixels_a.Color(0,255,0)); //green
  pixels_a.setPixelColor(2, pixels_a.Color(255,0,0));//red
  pixels_a.setPixelColor(3, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(4, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(5, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(6, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(7, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(8, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(9, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(10,pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(11,pixels_a.Color(255,0,0));
  pixels_a.show();   // Send the updated pixel colors to the hardware.
  delay(2000);
  pixels_b.setPixelColor(0, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(1, pixels_b.Color(0,255,0)); //green
  pixels_b.setPixelColor(2, pixels_b.Color(255,255,0));//yellow
  pixels_b.setPixelColor(3, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(4, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(5, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(6, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(7, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(8, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(9, pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(10,pixels_b.Color(255,255,0));
  pixels_b.setPixelColor(11,pixels_b.Color(255,255,0));
  pixels_b .show();   // Send the updated pixel colors to the hardware.
  delay(2000);
  pixels_c.setPixelColor(0, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(1, pixels_c.Color(0,255,0)); //green
  pixels_c.setPixelColor(2, pixels_c.Color(0,0,255));//blue
  pixels_c.setPixelColor(3, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(4, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(5, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(6, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(7, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(8, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(9, pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(10,pixels_c.Color(0,0,255));
  pixels_c.setPixelColor(11,pixels_c.Color(0,0,255));
  pixels_c.show();   // Send the updated pixel colors to the hardware.
  delay(2000);
  pixels_d.setPixelColor(0, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(1, pixels_d.Color(0,255,0)); //green
  pixels_d.setPixelColor(2, pixels_d.Color(0,255,0)); //green
  pixels_d.setPixelColor(3, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(4, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(5, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(6, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(7, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(8, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(9, pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(10,pixels_d.Color(0,255,0));
  pixels_d.setPixelColor(11,pixels_d.Color(0,255,0));
  pixels_d.show(); 
  delay(2000);
  }