// For WiFi and MQTT
#include "WiFiMQTT.h"

//********************************************************************
//****        WiFi and MQTT
//********************************************************************
// WiFi credentials

//Escape
const char *ssid = "escape-route";   // network SSID (name)
const char *password = "goodlife";  // network password


// MQTT Broker settings
const char *mqtt_broker = "192.168.8.248";
extern char *mqtt_topic;
extern char *connected_message;
const char *mqtt_username = "escape";
const char *mqtt_password = "escape";
const int mqtt_port = 1883;

// WiFi and MQTT client initialization
WiFiClient esp_client;
PubSubClient mqtt_client(esp_client);

// Function Declarations
//void wiFiMQTTsetup();
//void connectToWiFi();
//void connectToMQTT();
//void mqttCallback(char *topic, byte *payload, unsigned int length);

void wiFiMQTTsetup() {
  connectToWiFi();
  Serial.println("\nLEFT THE WiFi PROCEDURE");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setKeepAlive(60);
  mqtt_client.setCallback(mqttCallback);
  connectToMQTT();
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
}

void connectToMQTT() {
    while (!mqtt_client.connected()) {
        String client_id = "esp32-client-" + String(WiFi.macAddress());
        Serial.printf("Connecting to MQTT Broker as %s...\n", client_id.c_str());
        if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Connected to MQTT broker");
            mqtt_client.subscribe(mqtt_topic);
            mqtt_client.publish(mqtt_topic, connected_message);  // Publish message upon connection
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" Retrying in 5 seconds.");
            delay(5000);
        }
    }
}

/*
void loop() {
     if (!mqtt_client.connected()) {
        connectToMQTT();
    }
    mqtt_client.loop();

}
*/