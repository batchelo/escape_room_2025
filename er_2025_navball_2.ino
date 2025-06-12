#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// TFT Pins
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Joystick pins
#define JOY1_X 36  // Pitch
#define JOY1_Y 39  // Roll
#define JOY2_X 34  // Yaw

// Navball settings
const int centerX = 120;
const int centerY = 160;
const int radius = 100;

float pitch = 0;
float roll = 0;
float yaw = 0;

int lastYawX = 0, lastYawY = 0;
int lastMarkX1 = 0, lastMarkY1 = 0;
int lastMarkX2 = 0, lastMarkY2 = 0;

float readAxis(int pin) {
  int val = analogRead(pin);
  return (val - 2048) / 2048.0;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  drawNavballBackground();
}

void drawNavballBackground() {
  tft.fillCircle(centerX, centerY, radius, ILI9341_DARKCYAN);
  tft.drawCircle(centerX, centerY, radius, ILI9341_WHITE);

  // Fixed crosshairs (static)
  tft.drawLine(centerX - 5, centerY, centerX + 5, centerY, ILI9341_WHITE);
  tft.drawLine(centerX, centerY - 5, centerX, centerY + 5, ILI9341_WHITE);
}

void drawYawMarker(float yaw) {
  // Clear previous
  tft.drawLine(lastYawX - 3, lastYawY, lastYawX + 3, lastYawY, ILI9341_DARKCYAN);
  tft.drawLine(lastYawX, lastYawY - 3, lastYawX, lastYawY + 3, ILI9341_DARKCYAN);

  // Draw new
  float yawRad = radians(yaw);
  int px = centerX + radius * 0.6 * sin(yawRad);
  int py = centerY - radius * 0.6 * cos(yawRad);
  tft.drawLine(px - 3, py, px + 3, py, ILI9341_RED);
  tft.drawLine(px, py - 3, px, py + 3, ILI9341_RED);

  lastYawX = px;
  lastYawY = py;
}

void drawOrientationMarker(float pitch, float roll) {
  // Clear previous orientation line
  tft.drawLine(lastMarkX1, lastMarkY1, lastMarkX2, lastMarkY2, ILI9341_DARKCYAN);

  float rollRad = radians(roll);
  float pitchOffset = (pitch / 90.0) * radius;

  int dx = radius * 0.4 * cos(rollRad);
  int dy = radius * 0.4 * sin(rollRad);

  int x1 = centerX - dx;
  int y1 = centerY - dy + pitchOffset;
  int x2 = centerX + dx;
  int y2 = centerY + dy + pitchOffset;

  tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);

  lastMarkX1 = x1;
  lastMarkY1 = y1;
  lastMarkX2 = x2;
  lastMarkY2 = y2;
}

void drawTextData() {
  tft.fillRect(0, 0, 240, 60, ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Pitch: "); tft.println(pitch, 1);
  tft.setCursor(10, 30);
  tft.print("Roll:  "); tft.println(roll, 1);
  tft.setCursor(10, 50);
  tft.print("Yaw:   "); tft.println(yaw, 1);
}

void updateAttitude() {
  pitch += -1.5 * readAxis(JOY1_X);
  roll  += -1.5 * readAxis(JOY1_Y);
  yaw   +=  2.0 * readAxis(JOY2_X);

  pitch = constrain(pitch, -90, 90);
  roll  = constrain(roll, -90, 90);
  yaw   = fmod(yaw + 360, 360);  // Wrap yaw to 0–360
}

void loop() {
  updateAttitude();
  drawOrientationMarker(pitch, roll);
  drawYawMarker(yaw);
  drawTextData();

  delay(50);
}
