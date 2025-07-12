#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

#define TFT_CS     5
#define TFT_DC     2
#define TFT_RST    4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int chargeLevel = 0;
unsigned long lastUpdate = 0;
bool lightningToggle = true;
int prevDigitCount = 0;

void setup() {
  tft.begin();
  tft.setRotation(1); // Landscape mode
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setCursor(50,180);
  tft.print("Charge to 100% to");
  tft.setCursor(30,200);
  tft.print ("awaken ship's systems");
  tft.setCursor(35,220);
  tft.print("from deep-sleep mode");
}

void drawBatteryOutline() {
  int batteryW = 160;
  int batteryH = 100;
  int x = (tft.width() - batteryW) / 2; //this centers the battery display
  int y = 40;

  // Outline of battery
  tft.drawRect(x, y, batteryW, batteryH, ILI9341_WHITE);
  // Terminal of battery
  tft.fillRect(x + batteryW, y + batteryH / 3, 6, batteryH / 3, ILI9341_WHITE);
}

void drawBatteryBarsAnimated(int level) {
  int totalBars = 20;
  int filledBars = map(level, 0, 100, 0, totalBars);
  int barWidth = 7;
  int spacing = 1;
  int barHeight = 96;

  int batteryW = 160;
  int xStart = (tft.width() - batteryW) / 2 + 2;
  int yStart = 42;
//sets the level at which the bars turn from red to yellow
  uint16_t color = (level <= 20) ? ILI9341_RED : ILI9341_YELLOW; 

  // Clear battery fill area
  tft.fillRect(xStart, yStart, batteryW - 4, barHeight, ILI9341_BLACK);

  for (int i = 0; i < filledBars; i++) {
    int x = xStart + i * (barWidth + spacing);
    tft.fillRect(x, yStart + 2, barWidth, barHeight - 4, color);
  }
}

void drawPercentage(int level) {
  static int lastDigits = 0;

  // Calculate digit width to clear only what’s needed
  int digitWidth = 12;  // approx per digit with text size 2
  int digits = (level < 10) ? 1 : (level < 100 ? 2 : 3);

  if (digits != lastDigits) {
    // Clear entire old percentage area
    tft.fillRect(90, 160, 140, 20, ILI9341_BLACK);
    lastDigits = digits;
  } else {
    // Clear just the numeric portion (not whole box)
    tft.fillRect(150, 160, 60, 20, ILI9341_BLACK);
  }

  tft.setTextSize(2);  // 50% smaller than before
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(40, 160);
  tft.fillRect(90, 160, 200, 20, ILI9341_BLACK);
  tft.print("Current Charge: ");
  tft.print(level);
  tft.print(" %");
}

void loop() {
  if (millis() - lastUpdate > 500) {
    chargeLevel += 5;
    if (chargeLevel > 100) chargeLevel = 0;

    drawBatteryOutline();
    drawBatteryBarsAnimated(chargeLevel);
    drawPercentage(chargeLevel);

    lastUpdate = millis();
  }
}
