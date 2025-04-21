#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define Pixel_pin_a 18 // Which pin a particular line of leds is connected to
#define Pixel_pin_b 5
#define Pixel_pin_c 4
#define Pixel_pin_d 2
#define NUMPIXELS 12 // Number of NeoPixels are attached to the Arduino?

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {35, 27, 26, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {32, 34, 25}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Adafruit_NeoPixel pixels_a(NUMPIXELS, Pixel_pin_a, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_b(NUMPIXELS, Pixel_pin_b, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_c(NUMPIXELS, Pixel_pin_c, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_d(NUMPIXELS, Pixel_pin_d, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
boolean flag_a = 0;
boolean flag_b = 0;
boolean flag_c = 0;
boolean flag_d = 0;

void setup() {
  pixels_a.begin(); // INITIALIZE NeoPixel strip object
  pixels_b.begin();
  pixels_c.begin();
  pixels_d.begin();
  Serial.begin(9600);
  pinMode (12, OUTPUT);
}

void loop() 
{
//set the initial state
if (flag_a == 0 and flag_b == 0 and flag_c == 0 and flag_d == 0)
{
    digitalWrite (12, HIGH);  //lock the electromagnet

        //display initial "stasis" state for each of the tube slots
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
    pixels_b.show();   // Send the updated pixel colors to the hardware.
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
    pixels_d.show();   // Send the updated pixel colors to the hardware.
  }
//get keypad entry
  char key = keypad.getKey();
  if (key)
  {
    Serial.println(key);
  }
//test if all four flags are set, if so, then (1) unlock electromagent and (2) say congratulations
if (flag_a == 1 and flag_b == 1 and flag_c == 1 and flag_d == 1)
  {
    digitalWrite (12, LOW);
    //celebrate something
  }
//if correct for vile #1, then change state of lights and set flag
if (key == 3141) //The code from the orbital game
{
  flag_a = 1;
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
}
//if correct for vile #2, then change state of lights and set flag
if (key == 2345)  // code from the ?? puzzle
{
  flag_b = 1;
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
}
//if correct for vile #3, then change state of lights and set flag
if (key == 3456) //code from puzzle ??
{
  flag_c = 1;
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
}
//if correct for vile #4, then change state of lights and set flag
if (key == 4567)
{
  flag_d = 1;
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
  pixels_d.show();   // Send the updated pixel colors to the hardware.
}
}