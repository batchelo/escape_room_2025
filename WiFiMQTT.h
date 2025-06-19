#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
// Function Declarations
extern void wiFiMQTTsetup();  // Put this one call into the setup function
extern void connectToWiFi();
extern void connectToMQTT();

// declare this in your code (changing the strings as desired)
//char *mqtt_topic = "puzzle";
//char *connected_message = "Vial Console Connected";

// Make sure you declare this function in your code
extern void mqttCallback(char *topic, byte *payload, unsigned int length);
/* As an example

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("\n-----------------------");

  if (String(topic) == "puzzle") {
    Serial.println("Read the topic");
    payload[length] = '\0';
    Serial.println(String((char *)payload));
    if (String((char *)payload) == "POWERON") {
      powerOn = true;
      powerUp();
    }



/*
Inside of loop() call MQTT like this

void loop() {
     if (!mqtt_client.connected()) {
        connectToMQTT();
    }
    mqtt_client.loop();
}
*/