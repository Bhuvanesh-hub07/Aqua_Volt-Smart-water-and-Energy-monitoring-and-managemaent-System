#define BLYNK_TEMPLATE_ID "TMPL3nvVChEiY"
#define BLYNK_TEMPLATE_NAME "Water and Energy monitoring"
#define BLYNK_AUTH_TOKEN "wwMrshB1hpWtXlqEIbZl4zLLFQ8WnEcD"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "ESP32TEST";
char pass[] = "12345678";

float current;
float waterFlow;
float waterLevel;
float temperature;

BlynkTimer timer;

void sendSensorData()
{
  // Example values (replace with sensors)
  current = random(0,20)/100.0;      // 0-0.2 A
  waterFlow = random(0,15);          // 0-15 L/min
  waterLevel = random(0,100);        // %
  temperature = random(25,50);       // °C

  // Send to Blynk Dashboard
  Blynk.virtualWrite(V0, current);
  Blynk.virtualWrite(V1, waterFlow);
  Blynk.virtualWrite(V2, waterLevel);
  Blynk.virtualWrite(V3, temperature);

  // Notifications

  if(current > 0.15)
  {
    Blynk.logEvent("over_current","⚠ Current above 0.15A");
  }

  if(waterFlow > 10)
  {
    Blynk.logEvent("water_flow","⚠ Water Flow above 10 L/min");
  }

  if(waterLevel > 50)
  {
    Blynk.logEvent("water_level","⚠ Water Level above 50%");
  }
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData); // update every 2 sec
}

void loop()
{
  Blynk.run();
  timer.run();
}