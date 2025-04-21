#include <Wire.h> 
#include <LCD_I2C.h>
#include <Keypad.h>

LCD_I2C lcd(0x27, 16, 2); 
String pad;
const byte numRows = 4;
const byte numCols = 3;
String password = "4321";
char keypressed;

char keymap[numRows][numCols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[numRows] = {4, 27, 26, 33};
byte colPins[numCols] = {32, 13, 25};

Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,numRows,numCols);

void readKeypad()
{
 keypressed = myKeypad.getKey();
 if (keypressed !='#')
  {
    String konv = String(keypressed);
    pad += konv;
  }
}
 void setup(){
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Keypad");
  lcd.setCursor(0,1);
  lcd.print("Test");
  delay(1000);
  lcd.clear();
  pinMode(27,INPUT);
  pinMode(26,INPUT);
  pinMode(25,INPUT);
  pinMode(33,INPUT);
  pinMode(32,INPUT);
  pinMode(4,INPUT); 
  pinMode(13,INPUT);
}

void loop(){
readKeypad();
if (keypressed =='#'){
  if (pad == password){
    lcd.setCursor(0,1);
    lcd.print("Access Granted");
  } else{
    lcd.setCursor(0,1);
    lcd.print("Access Denied");
    }
} if (keypressed =='*'){
    pad = "";
    lcd.clear();
  }
lcd.setCursor(0,0);
lcd.print(pad);
delay(100);
}