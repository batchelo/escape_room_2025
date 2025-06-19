#include "WiFiMQTT.h"
#include <TM1637Display.h>

extern PubSubClient mqtt_client;
char *mqtt_topic = "puzzle";
char *mqtt_subtopic = "puzzle/crank";
char *mqtt_subtopic2 = "puzzle/crank/timer";
char *connected_message = "Power Crank Connected";

#define PIN_CRANK 34
#define PIN_CHARGE_LED 21
#define PIN_DISCHARGE_LED 22
#define PIN_DEPLETED_LED 23
#define PIN_CLK 26
#define PIN_DIO 27
#define PIN_NEO_PIXEL 25
#define PIN_MOSFET 13

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>


#define NUM_PIXELS 23     // The number of LEDs (pixels) on NeoPixel LED strip
// Clock display connection pins (Digital Pins)

TM1637Display display(PIN_CLK, PIN_DIO);

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

#define DISCHARGE 1
#define CHARGE 2
#define DEPLETED 3

bool reachedFullPower = false;
long prevTime = 0;
int vValue = 0;
int timeStart = 60*20*1000;
const long MAXCHARGE = 60000;
long eachLevel = MAXCHARGE/NUM_PIXELS;
long timeLevel = timeStart/NUM_PIXELS;
const int CHARGEMULTIPLIER = 2;
char state = DISCHARGE;
long chargeAmt = MAXCHARGE;
unsigned long startMillis;
bool countdown = false;

void updateClock() {
  int timeLeft = getTimeLeft();
  if(timeLeft <= 0) {
    timeLeft = 0;
    state = DEPLETED;
    digitalWrite(PIN_MOSFET,HIGH);
  }
  int minutes = timeLeft / 60000;
  int seconds = (timeLeft - (minutes*60000))/1000;
  display.setBrightness(4);
  int timeOut = minutes*100+seconds;
  display.showNumberDecEx(timeOut, 0b01000000, false);

}
//*******************************************************

void reset() {
  digitalWrite(PIN_DISCHARGE_LED, LOW);
  digitalWrite(PIN_DEPLETED_LED, HIGH);
  digitalWrite(PIN_CHARGE_LED, LOW);
  digitalWrite(PIN_MOSFET,HIGH);
  prevTime = millis();
  state = DEPLETED;
  reachedFullPower = false;
  chargeAmt = 0;
  vValue = 0;
  countdown = false;
}

//*******************************************************

void setup() {
  Serial.begin(115200);
  wiFiMQTTsetup();
  mqtt_client.subscribe(mqtt_subtopic);
  mqtt_client.subscribe(mqtt_subtopic2);
  pinMode(PIN_CHARGE_LED, OUTPUT);
  pinMode(PIN_DISCHARGE_LED, OUTPUT);
  pinMode(PIN_DEPLETED_LED, OUTPUT);
  pinMode(PIN_MOSFET,OUTPUT);
  NeoPixel.begin();  // initialize NeoPixel strip object (REQUIRED)
  reset();
}

//*******************************************************

void showBars() {
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

  if(state != DEPLETED) {
    // turn pixels to green
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
      if(chargeAmt > pixel * eachLevel) {
          NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
      }
    }
  }
  NeoPixel.show();  // update to the NeoPixel Led Strip
}

//*******************************************************
int getTimeLeft() {
  unsigned long currMillis = millis();
  int timeLeft = timeStart - (currMillis - startMillis);
  return timeLeft;
}
//*******************************************************
void showBarsOfTime() {
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  int timeLeft = getTimeLeft();

  if(state != DEPLETED) {
    // turn pixels to green
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
      if(timeLeft > pixel * timeLevel) {
        if(timeLeft <= 5 * timeLevel)
          NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0)); // red if low time
        else
          NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));  // green if long time
      }
    }
    if(timeLeft <= 0) {
      state = DEPLETED;
      digitalWrite(PIN_MOSFET,HIGH);
    }
  }

  NeoPixel.show();  // update to the NeoPixel Led Strip
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
  if (String(topic) == "puzzle/crank/timer") {
      startMillis = millis();
      timeStart = String((char *)payload).toInt();  // time left when power came on
      countdown = true;
      updateClock();
  }
  if (String((char *)payload) == "FLASHEROFF") {
    Serial.println("Recognized FLASHEROFF");
    digitalWrite(PIN_MOSFET, LOW);
  }
  if (String((char *)payload) == "FLASHERON") {
    Serial.println("Recognized FLASHERON");
    digitalWrite(PIN_MOSFET, HIGH);
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


void loop() {
  long currTime = millis();
  if(state == DISCHARGE) {
    if(reachedFullPower == true) {  // if you've reached full charge, discharge based on time
      if(getTimeLeft() <= 0) {
        chargeAmt = 0;
        Serial.println("DEPLETED");
        state = DEPLETED;
        mqtt_client.publish(mqtt_topic, "POWEROFF");  // Publish message to turn others off
        digitalWrite(PIN_CHARGE_LED, LOW);
        digitalWrite(PIN_DISCHARGE_LED, LOW);
        digitalWrite(PIN_DEPLETED_LED, HIGH);
      }
    }
    else { // if you haven't reached full charge, discharge slowly
      chargeAmt = max(chargeAmt - (currTime - prevTime), 0L);
      if(chargeAmt <= 0) {
        chargeAmt = 0;
        Serial.println("DEPLETED");
        state = DEPLETED;
        mqtt_client.publish(mqtt_topic, "POWEROFF");  // Publish message to turn others off
        digitalWrite(PIN_CHARGE_LED, LOW);
        digitalWrite(PIN_DISCHARGE_LED, LOW);
        digitalWrite(PIN_DEPLETED_LED, HIGH);
      }
    }
  }

  if(reachedFullPower == false) { // if you haven't reached full charge, allow charging
    vValue = vValue * 0.8 + 0.2*analogRead(PIN_CRANK);
    Serial.println(vValue);
  }
  else { // if you have reached full charge, don't bother allowing more. This will cause discharge.
     vValue = 0;
  }
   
  if(vValue > 50) {
    // Someone is cranking
    if (state != CHARGE) {
      Serial.println("CHARGING");
    }
    state = CHARGE;
    chargeAmt = min(chargeAmt + CHARGEMULTIPLIER*(currTime - prevTime), MAXCHARGE);
    if((chargeAmt == MAXCHARGE) && (reachedFullPower == false)) {
      reachedFullPower = true;
      vValue = 0;
      mqtt_client.publish(mqtt_topic, "POWERON");  // Publish message to turn others on
      mqtt_client.publish(mqtt_topic, "Crank Complete");  // Publish message to verify completion
      mqtt_client.publish(mqtt_subtopic, "Crank Complete");  // Publish message to verify completion
      digitalWrite(PIN_MOSFET, LOW);
    }
    digitalWrite(PIN_CHARGE_LED, HIGH);
    digitalWrite(PIN_DISCHARGE_LED, LOW);
    digitalWrite(PIN_DEPLETED_LED, LOW);
  } else if (state == CHARGE) {
    // Not cranking
    state = DISCHARGE;
    Serial.println("DISCHARGING");
    digitalWrite(PIN_CHARGE_LED, LOW);
    digitalWrite(PIN_DISCHARGE_LED, HIGH);
  }
  prevTime = currTime;
  
  if(countdown == false) {  // No time to show yet.
    display.setBrightness(4, false);
    display.showNumberDec(0);
  }
  else    
    updateClock();

  if(reachedFullPower == true) {
    // Lets plot the bars based on time remaining
    showBarsOfTime();
  }
  else
    showBars();

  // Do this always so that
  // you'll get the reset messages
  if (!mqtt_client.connected()) {
        connectToMQTT();
    }
    mqtt_client.loop();
}
