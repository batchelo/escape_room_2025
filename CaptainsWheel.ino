/**
 * Based on Pirate Wheel Puzzle - Copyright (c) 2023 Playful Technology
 *
 * Uses a AS5600 magnetic sensor to detect rotation of a ship's wheel (or any other object that can be freely-rotated - a bank vault wheel etc. etc.)
 * Can detect both the angle to which the wheel is currently turned, and the clockwise/counter-clockwise pattern of rotations used to get there
 * When the correct solution pattern is entered, a relay is activated to release a maglock
 */
// INCLUDES
// AS5600 Magnetic Encoder. See https://github.com/RobTillaart/AS5600
#include "src/AS5600.h"
// WS2812B Programmable LED strips. See FastLED.io
#include <FastLED.h>
#include <ESP32Servo.h>
#include "WiFiMQTT.h"

// CONSTANTS
// 21 & 22 used for i2C
const byte ledPin = 17;
static const int servoPin = 13;
int sevenSegs[] = {26,27,32,14,16,25,33};    // 7 segment display
int digits[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; // Outputs to the 7 segment

extern PubSubClient mqtt_client;
char *mqtt_topic = "puzzle";
char *mqtt_subtopic = "puzzle/wheel";
char *connected_message = "Captain's Wheel Connected";


// Number of LEDs in the LED strip
const byte numLeds = 15;

#define MATCHING 1
#define WAITING 2
#define FINISHED 3
#define POWEROFF 4

#define CLOSESERVO 0
#define OPENSERVO 180

#define MAXTURN 2700
#define MINTURN  990

// GLOBALS
// Declare an object to access the AS5600 sensor
AS5600 as5600;
// Create an array of RGB values for each LED in the strip
CRGB leds[numLeds];
// Servo
Servo servo1;
int currentTarget = 7;
int successes = 9;
int lastPixel;
int velocity = 0;
int waitingCount = 0;

int gameState = POWEROFF;
unsigned long stepBeginTime = 0;
unsigned long cumulativeReaction = 0;
unsigned long stopTime=0;

//*******************************************************

void plotTarget() {
  FastLED.clear();
  if((gameState == MATCHING) || (gameState == WAITING)) {
    leds[currentTarget] = CRGB::CornflowerBlue;
  }
}

//*******************************************************

void plotMe(CRGB color) {
  if((gameState == MATCHING) || (gameState == WAITING)) {
    int myLED = findMyPixel();
    leds[myLED] = color;
  }
}

//*******************************************************

void reset() {
  gameState = POWEROFF;
  currentTarget = 7;
  successes = 9;
  FastLED.clear();
  plotTarget();
  int myPixel = findMyPixel(); 
  if(myPixel!=currentTarget)
    plotMe(CRGB::Red);
  else
    plotMe(CRGB::Green);
  FastLED.show();
  servo1.write(CLOSESERVO);
  displayCount(successes);
  stepBeginTime = millis();
};

//*******************************************************

void setup() {
  // Initialise the serial connection used for debugging
  Serial.begin(115200);
  Serial.println(__FILE__ __DATE__);

  wiFiMQTTsetup();
  mqtt_client.subscribe(mqtt_subtopic);

  for (int i = 0; i<7; i++) pinMode(sevenSegs[i], OUTPUT); // Seven Segment Display

  // Start the magnetic field sensor
  as5600.begin();
  Serial.print("Connecting to A5600...");
  Serial.println(as5600.isConnected() ? "OK" : "Failed");
  
  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, numLeds);
  FastLED.clear();
  FastLED.setBrightness(20);
  FastLED.show();
  
  servo1.attach(servoPin, 500, 2500);
  reset();
}

//*******************************************************

void displayCount(int j) {
  for (int i = 0; i<7; i++) {
    if(gameState != POWEROFF)
      digitalWrite(sevenSegs[i], bitRead(digits[j], i));
    else
      digitalWrite(sevenSegs[i], 0); // Turn all segments off if poweroff
  }
}

//*******************************************************

int findMyPixel() {
  // Read a bunch of them to average a bit
  int sum = 0;
  for(int i = 0; i < 10; i++) {
    sum += as5600.readAngle();
  }
  // Map to the number of LEDs
  int myLED = map(sum, MINTURN*10, MAXTURN*10, 0, numLeds);
  // Endpoint clipping
  if(myLED < 0)
    myLED = 0;
  if(myLED >= numLeds)
    myLED = numLeds-1;
  
  // Try to account for noisiness. Only record
  // a change if 2 successive measurements are
  // in the same direction.
  if(myLED == lastPixel) {
    velocity = 0;
  }
  if(myLED > lastPixel) {
    if(velocity > 0) {
      lastPixel = myLED;
    }
    velocity = 1;
  }
  
  if(myLED < lastPixel) {
    if(velocity < 0) {
      lastPixel = myLED;
    }
    velocity = -1;
  }

  // If the player has gotten to the target
  // (gameState == WAITING) be particularly 
  // generous before you say it has moved.
  if(gameState == WAITING) {
    if(abs(myLED-currentTarget) <= 1) {
        waitingCount += 1;
        velocity = 0;
        myLED=currentTarget;
        lastPixel = myLED;
    }
    else {
      gameState = MATCHING;
    }
  }
  //Serial.println(myLED);
  return myLED;
}

//*******************************************************

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("\n-----------------------");

  payload[length] = '\0';
  Serial.println(String((char *)payload));
  if (String((char *)payload) == "OPENTRAY") {
    Serial.println("Recognized OPENTRAY");
    servo1.write(OPENSERVO);
  }
  if (String((char *)payload) == "CLOSETRAY") {
    Serial.println("Recognized CLOSETRAY");
    servo1.write(CLOSESERVO);
  }
  if (String((char *)payload) == "POWERON") {
    Serial.println("Recognized POWERON");
    displayCount(successes);
    gameState = MATCHING;
  }
  if (String((char *)payload) == "POWEROFF") {
    Serial.println("Recognized POWEROFF");
    displayCount(successes);
    gameState = POWEROFF;
  }
  if (String((char *)payload) == "RESET") {
    Serial.println("Recognized RESET");
    reset();
  }
  if (String((char *)payload) == "CHECK-IN") {
    Serial.println("Recognized CHECK-IN");
    mqtt_client.publish(mqtt_topic, connected_message);  // Publish message to verify connection
  }
}

//*******************************************************

void loop() {
  if((gameState == MATCHING) || (gameState == WAITING)) {

    unsigned long currLoop = millis();
    int myPixel = findMyPixel();
    plotTarget();
    if(myPixel!=currentTarget) {
      plotMe(CRGB::Red);
      gameState = MATCHING;
    }
    else {
      plotMe(CRGB::Green);
      if(gameState == MATCHING) {
          gameState = WAITING;
          stopTime = currLoop;
      }
    }

    if((currLoop > stopTime + 2000) && (gameState == WAITING))  {
      successes -= 1;
      displayCount(successes);
      // Shift the target
      int oldTarget = currentTarget;
      
      while((abs(oldTarget - currentTarget) < 2) || (abs(myPixel - currentTarget) < 2) || (currentTarget == (numLeds-3))) {
        currentTarget = random(1, numLeds-1);
      }
      
      plotTarget();
      if(myPixel!=currentTarget)
        plotMe(CRGB::Red);
      else
        plotMe(CRGB::Green);
      
      cumulativeReaction = cumulativeReaction + (stopTime - stepBeginTime);
      stepBeginTime = currLoop;
      gameState = MATCHING;
      Serial.println((float)(cumulativeReaction)/successes/1000.0);
      if((successes <= 0)) {//} && ((float)(cumulativeReaction)/successes/1000.0) <= 2.0) {
          Serial.println("DONE!");
          gameState = FINISHED;
          FastLED.clear();
          servo1.write(OPENSERVO);
          mqtt_client.publish(mqtt_topic, "Wheel Complete");  // Publish message to verify completion
      }
    }
    
    FastLED.setBrightness(20);
    FastLED.show();
    
    delay(50);
  }
  // Do this even when gameState == POWEROFF so that
  // you'll get the POWERON message
  if (!mqtt_client.connected()) {
        connectToMQTT();
    }
    mqtt_client.loop();
}