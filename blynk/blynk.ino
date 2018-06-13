#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <SimpleTimer.h>

#define DHTTYPE DHT11
#define DHT_PIN D4

char auth[] = "e9f72000659b438c9ead39d890f7312f";

char ssid[] = "Wifi PTC3";
char pass[] = "246813579";

DHT dht(DHT_PIN, DHTTYPE);
float t;
float h;

SimpleTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  timer.setInterval(2000, sendUptime);
}

void sendUptime()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Humidity and Temperature\n\n");
  Serial.print("Current Humidity: ");
  Serial.println(h);
  Serial.print("Current Temperature: ");
  Serial.println(t);

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

void loop()
{
  Blynk.run();
  timer.run();
}

