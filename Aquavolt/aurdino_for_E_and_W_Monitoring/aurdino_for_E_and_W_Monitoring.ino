// 🔷 BLYNK CONFIG (MUST BE FIRST)
#define BLYNK_TEMPLATE_ID "TMPL3ILjGwqjZ"
#define BLYNK_TEMPLATE_NAME "AI based Water monitoring System"
#define BLYNK_AUTH_TOKEN "ulzoGVLJ-tNh5XOXHpy9ePF0UqUeM9SP"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// 🔐 WiFi Credentials
char ssid[] = "RAJASANKARAKUMAR5G";
char pass[] = "Aishu@12345";

// 🔌 Use Serial2 (IMPORTANT FIX)
#define RXD2 16   // GPIO16

void setup() {
  Serial.begin(9600);    // Debug monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, -1); // Arduino data

  // 🌐 Connect Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {

  Blynk.run();

  // 📥 Read data from Arduino
  if (Serial2.available() > 0) {

    String data = Serial2.readStringUntil('\n');
    data.trim();

    Serial.print("Received: ");
    Serial.println(data);

    float current = 0, flow = 0, level = 0, temp = 0;

    sscanf(data.c_str(), "%f,%f,%f,%f", &current, &flow, &level, &temp);

    // 🔵 Send LIVE values to Blynk
    Blynk.virtualWrite(V4, current);   // Current
    Blynk.virtualWrite(V2, flow);      // Flow
    Blynk.virtualWrite(V1, level);     // Level
    Blynk.virtualWrite(V3, temp);      // Temperature
  }
}