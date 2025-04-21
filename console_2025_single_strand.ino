#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LCD-I2C.h>

#define Pixel_pin 18 // Which pin a particular line of leds is connected to
#define NUMPIXELS 24 // Number of NeoPixels are attached to the Arduino?

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

Adafruit_NeoPixel pixels(NUMPIXELS, Pixel_pin, NEO_GRB + NEO_KHZ800);

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
  pixels.begin(); // INITIALIZE NeoPixel strip object
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
}

void loop() 
{
//set the initial state
if (flag_a == 0 and flag_b == 0 and flag_c == 0 and flag_d == 0)
{
  digitalWrite (12, HIGH);  //lock the electromagnet
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(0, pixels.Color(255,0,0));    //display initial "stasis" state for each of the tube slots
  pixels.setPixelColor(11, pixels.Color(255,0,0));
  pixels.setPixelColor(12, pixels.Color(255,0,0));
  pixels.setPixelColor(23, pixels.Color(255,0,0));
  pixels.show();
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
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,255,0));
  pixels.setPixelColor(0, pixels.Color(255,0,0));
  pixels.setPixelColor(0, pixels.Color(255,0,0));
  pixels.setPixelColor(0, pixels.Color(255,0,0));  
  pixels.show();   // Send the updated pixel colors to the hardware.
}
//if correct for vile #2, then change state of lights and set flag
if (guess == "2345")  // code from the ?? puzzle
{
  flag_b = 1;
  pixels.setPixelColor(6, pixels.Color(255,255,0));
  pixels.setPixelColor(7, pixels.Color(255,255,0));
  pixels.setPixelColor(8, pixels.Color(255,255,0));
  pixels.setPixelColor(9, pixels.Color(255,255,0));
  pixels.setPixelColor(10, pixels.Color(0,255,0)); 
  pixels.setPixelColor(11, pixels.Color(0,0,0)); 
  pixels.show();   // Send the updated pixel colors to the hardware.
}
//if correct for vile #3, then change state of lights and set flag
if (guess == "3456") //code from puzzle ??
{
  flag_c = 1;
  pixels.setPixelColor(12, pixels.Color(0,0,0));
  pixels.setPixelColor(13, pixels.Color(0,255,0));
  pixels.setPixelColor(14, pixels.Color(0,0,255));
  pixels.setPixelColor(15, pixels.Color(0,0,255));
  pixels.setPixelColor(16, pixels.Color(0,0,255)); 
  pixels.setPixelColor(17, pixels.Color(0,0,255)); 
  pixels.show();   // Send the updated pixel colors to the hardware.
}
//if correct for vile #4, then change state of lights and set flag
if (guess == "4567")
{
  flag_d = 1;
  pixels.setPixelColor(18, pixels.Color(0,255,0));
  pixels.setPixelColor(19, pixels.Color(0,255,0));
  pixels.setPixelColor(20, pixels.Color(0,255,0));
  pixels.setPixelColor(21, pixels.Color(0,255,0));
  pixels.setPixelColor(22, pixels.Color(0,255,0)); 
  pixels.setPixelColor(23, pixels.Color(0,0,0)); 
  pixels.show();   // Send the updated pixel colors to the hardware.
}
}
