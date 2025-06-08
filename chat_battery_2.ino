#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Simulated charge level
int simulatedPercent = 0;
bool chargingUp = true;

unsigned long previousMillis = 0;
int frame = 0;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Simulate battery charging
  simulateCharging();

  drawBattery(simulatedPercent);
  delay(150); // animation speed
}

void simulateCharging() {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > 150) {
    lastUpdate = now;

    if (chargingUp) {
      simulatedPercent += 2;
      if (simulatedPercent >= 100) {
        simulatedPercent = 100;
        chargingUp = false;
        delay(1000); // Pause at full charge
      }
    } else {
      simulatedPercent = 0;
      chargingUp = true;
    }
  }
}

void drawBattery(int percent) {
  display.clearDisplay();

  // Draw battery outline
  int x = 50, y = 20, w = 28, h = 20;
  display.drawRect(x, y, w, h, WHITE); // main battery body
  display.drawRect(x + w, y + 6, 3, 8, WHITE); // battery terminal

  // Calculate fill level
  int fillWidth = map(percent, 0, 100, 0, w - 2);
  display.fillRect(x + 1, y + 1, fillWidth, h - 2, WHITE);

  // Animate charging icon
  if (percent < 100) {
    drawChargingIcon((frame / 3) % 3);
    frame++;
  }

  // Show percentage text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(45, 45);
  display.print("Charging: ");
  display.print(percent);
  display.println("%");

  display.display();
}

void drawChargingIcon(int phase) {
  int cx = 90, cy = 25;

  switch (phase) {
    case 0:
      display.drawLine(cx, cy, cx + 5, cy + 10, WHITE);
      display.drawLine(cx + 5, cy + 10, cx + 2, cy + 10, WHITE);
      display.drawLine(cx + 2, cy + 10, cx + 7, cy + 20, WHITE);
      break;
    case 1:
      display.drawLine(cx + 1, cy + 1, cx + 6, cy + 11, WHITE);
      display.drawLine(cx + 6, cy + 11, cx + 3, cy + 11, WHITE);
      display.drawLine(cx + 3, cy + 11, cx + 8, cy + 21, WHITE);
      break;
    case 2:
      display.drawLine(cx + 2, cy + 2, cx + 7, cy + 12, WHITE);
      display.drawLine(cx + 7, cy + 12, cx + 4, cy + 12, WHITE);
      display.drawLine(cx + 4, cy + 12, cx + 9, cy + 22, WHITE);
      break;
  }
}
