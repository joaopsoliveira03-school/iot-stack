#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>  // For WiFi boards

// WiFi Configuration
char ssid[] = "redacted";
char pass[] = "redacted";

// MQTT Configuration
const char broker[] = "192.168.0.13";
int port = 1883;
const char topic[] = "temp_sensor";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Sensor Configuration
int B = 3975;  // B value from original code
float resistance;
float temperature;

void setup() {
  Serial.begin(9600);
  
  // Connect to WiFi
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nWiFi connected!");
  
  // Connect to MQTT broker
  while (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code: ");
    Serial.println(mqttClient.connectError());
    delay(5000);
  }
  Serial.println("Connected to MQTT broker!");
}

void loop() {
  mqttClient.poll();  // Maintain connection
  
  int a = analogRead(A0);
  resistance = (float)(1023 - a) * 10000 / a;
  temperature = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15;

  // Send to both Serial and MQTT
  Serial.print("Current temperature is ");
  Serial.println(temperature);
  
  mqttClient.beginMessage(topic);
  mqttClient.print(temperature);
  mqttClient.endMessage();

  delay(1000);  // 5-second interval
}
