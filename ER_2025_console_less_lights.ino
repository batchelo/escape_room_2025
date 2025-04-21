#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LCD_I2C.h>

#define Pixel_pin_a 18 // Which pin a particular line of leds is connected to
#define Pixel_pin_b 14
#define Pixel_pin_c 16
#define Pixel_pin_d 15
#define NUMPIXELS 6 // Number of NeoPixels are attached to the Arduino?

const byte numRows = 4; //four rows
const byte numCols = 3; //three columns
char keymap[numRows][numCols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
char keypressed;
String guess;
String code;

byte rowPins[numRows] = {13, 27, 26, 33}; //connect to the row pinouts of the keypad
byte colPins[numCols] = {32, 4, 25}; //connect to the column pinouts of the keypad

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

Adafruit_NeoPixel pixels_a(NUMPIXELS, Pixel_pin_a, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_b(NUMPIXELS, Pixel_pin_b, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_c(NUMPIXELS, Pixel_pin_c, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_d(NUMPIXELS, Pixel_pin_d, NEO_GRB + NEO_KHZ800);
int delay_dur = 100;

LCD_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
boolean flag_a = 0;
boolean flag_b = 0;
boolean flag_c = 0;
boolean flag_d = 0;

void readKeypad()
{
  keypressed = myKeypad.getKey();
  if (keypressed !='#')
    {
      String padEntry= String(keypressed);
      guess += padEntry;
    }
  if (keypressed=='*')
    {
      guess = "";
      lcd.clear();
    }
  if (keypressed == '#')
    {
      guess = "";
      lcd.clear();
    }
lcd.setCursor(0,0);
lcd.print(guess);
delay(100);
}
void setup() {
  pixels_a.begin(); // INITIALIZE NeoPixel strip object
  delay(delay_dur);
  pixels_b.begin();
  delay(delay_dur);
  pixels_c.begin();
  delay(delay_dur);
  pixels_d.begin();
  delay(delay_dur);
  pixels_a.show();
  delay(delay_dur);
  pixels_b.show();
  delay(delay_dur);
  pixels_c.show();
  delay(delay_dur);
  pixels_d.show();
  delay(delay_dur);
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  pinMode(12,OUTPUT);//mosfet gate
  pinMode(4,INPUT);//keypad col2
  pinMode(27,INPUT);//keypad row2
  pinMode(26,INPUT);//keypad row3
  pinMode(25,INPUT);//keypad col3
  pinMode(33,INPUT);//keypad row4
  pinMode(32,INPUT);//keypad col1
/* pixels_a.clear();
  delay(delay_dur);
  pixels_b.clear();
  delay(delay_dur);
  pixels_c.clear();
  delay(delay_dur);
  pixels_d.clear();
  delay(delay_dur);
  */
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
  pixels_a.show();   // Send the updated pixel colors to the hardware.
  delay(delay_dur);
  pixels_b.clear(); // Set all pixel colors to 'off'
  pixels_b.setPixelColor(0, pixels_b.Color(255,0,0)); //red
  pixels_b.setPixelColor(1, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(2, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(3, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(4, pixels_b.Color(0,0,0));
  pixels_b.setPixelColor(5, pixels_b.Color(0,0,0));
  pixels_b.show();   // Send the updated pixel colors to the hardware.
  delay(delay_dur);
 // pixels_c.clear(); // Set all pixel colors to 'off'
  pixels_c.setPixelColor(0, pixels_c.Color(255,0,0)); //red
  pixels_c.setPixelColor(1, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(2, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(3, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(4, pixels_c.Color(0,0,0));
  pixels_c.setPixelColor(5, pixels_c.Color(0,0,0));
  pixels_c.show();   // Send the updated pixel colors to the hardware.
  delay(delay_dur);
 // pixels_d.clear(); // Set all pixel colors to 'off'
  pixels_d.setPixelColor(0, pixels_d.Color(255,0,0)); //red
  pixels_d.setPixelColor(1, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(2, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(3, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(4, pixels_d.Color(0,0,0));
  pixels_d.setPixelColor(5, pixels_d.Color(0,0,0));
  pixels_d.show();   // Send the updated pixel colors to the hardware.
  delay(delay_dur);
}
//test if all four flags are set, if so, then (1) unlock electromagent and (2) say congratulations
if (flag_a == 1 and flag_b == 1 and flag_c == 1 and flag_d == 1)
{
  digitalWrite (12, LOW);
  lcd.setCursor(0,0);
  lcd.print("Congratulations!");
  lcd.setCursor(0,1);
  lcd.print("You succeeded!");
  delay(5000);
  lcd.clear();
  while (1==1)
    {
    lcd.setCursor(0,0);
    lcd.print("Now--GENTLY--");
    lcd.setCursor(0,1);
    lcd.print("Take the Tubes");
    delay (2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GET OUT!!");
    lcd.setCursor(0,1);
    lcd.print("Save Yourself!!");
    delay(2000);
    }
}
//if correct for vile #1, then change state of lights and set flag
readKeypad();
if (guess == "3141") //The code from the orbital game
{
  flag_a = 1;
  pixels_a.clear();
  pixels_a.setPixelColor(0, pixels_a.Color(0,0,0));
  pixels_a.setPixelColor(1, pixels_a.Color(0,255,0)); //green
  pixels_a.setPixelColor(2, pixels_a.Color(255,0,0));//red
  pixels_a.setPixelColor(3, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(4, pixels_a.Color(255,0,0));
  pixels_a.setPixelColor(5, pixels_a.Color(255,0,0));
  pixels_a.show();   // Send the updated pixel colors to the hardware.
  delay(delay_dur);
}
//if correct for vile #2, then change state of lights and set flag
readKeypad();
if (guess == "2345")  // code from the ?? puzzle
    {
    flag_b = 1;
    pixels_b.clear();
    pixels_b.setPixelColor(0, pixels_b.Color(0,0,0));
    pixels_b.setPixelColor(1, pixels_b.Color(0,255,0)); //green
    pixels_b.setPixelColor(2, pixels_b.Color(255,255,0));//yellow
    pixels_b.setPixelColor(3, pixels_b.Color(255,255,0));
    pixels_b.setPixelColor(4, pixels_b.Color(255,255,0));
    pixels_b.setPixelColor(5, pixels_b.Color(255,255,0));
    pixels_b .show();   // Send the updated pixel colors to the hardware.
    delay(delay_dur);
  }
//if correct for vile #3, then change state of lights and set flag
readKeypad();
if (guess == "3456") //code from puzzle ??
    {
    flag_c = 1;
    pixels_c.clear();
    pixels_c.setPixelColor(0, pixels_c.Color(0,0,0));
    pixels_c.setPixelColor(1, pixels_c.Color(0,255,0)); //green
    pixels_c.setPixelColor(2, pixels_c.Color(0,0,255));//blue
    pixels_c.setPixelColor(3, pixels_c.Color(0,0,255));
    pixels_c.setPixelColor(4, pixels_c.Color(0,0,255));
    pixels_c.setPixelColor(5, pixels_c.Color(0,0,255));
    pixels_c.show();   // Send the updated pixel colors to the hardware.
    delay(delay_dur);
  }
//if correct for vile #4, then change state of lights and set flag
readKeypad();
if (guess == "4567")
    {
    flag_d = 1;
    pixels_d.clear();
    pixels_d.setPixelColor(0, pixels_d.Color(0,0,0));
    pixels_d.setPixelColor(1, pixels_d.Color(0,255,0)); //green
    pixels_d.setPixelColor(2, pixels_d.Color(0,255,0)); //green
    pixels_d.setPixelColor(3, pixels_d.Color(0,255,0));
    pixels_d.setPixelColor(4, pixels_d.Color(0,255,0));
    pixels_d.setPixelColor(5, pixels_d.Color(0,255,0));
    pixels_d.show();   // Send the updated pixel colors to the hardware.
    delay(delay_dur);
  }
}