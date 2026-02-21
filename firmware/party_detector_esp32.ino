#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

#define SOUND_PIN 34
#define SAMPLE_COUNT 40
#define THRESHOLD 650
#define COOLDOWN_MS 30000

unsigned long lastSentTime = 0;

int readSoundAverage() {
  long sum = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    sum += analogRead(SOUND_PIN);
    delay(2);
  }
  return sum / SAMPLE_COUNT;
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void sendAlert(int noiseLevel) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"deviceId\":\"" + String(DEVICE_ID) + "\",";
  json += "\"location\":\"" + String(LOCATION) + "\",";
  json += "\"noiseLevel\":" + String(noiseLevel) + ",";
  json += "\"duration\":5";
  json += "}";

  int response = http.POST(json);

  Serial.print("HTTP Response: ");
  Serial.println(response);

  http.end();
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(SOUND_PIN, INPUT);

  connectWiFi();
}

void loop() {
  int soundValue = readSoundAverage();

  Serial.print("Sound: ");
  Serial.println(soundValue);

  if (soundValue > THRESHOLD) {
    if (millis() - lastSentTime > COOLDOWN_MS) {
      Serial.println("Noise threshold exceeded! Sending alert...");
      sendAlert(soundValue);
      lastSentTime = millis();
    }
  }

  delay(500);
}