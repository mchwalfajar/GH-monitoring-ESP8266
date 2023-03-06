#include <AntaresESP8266HTTP.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>

/* Credentials */
#define ACCESSKEY "181b1730efb9f453:1860de96ede6acb0"
#define WIFISSID "GH-monitor"
#define PASSWORD "sakuraprada"
#define PROJECTNAME "greenhouse-nodemcu"
#define DEVICENAME "GH-monitor"

AntaresESP8266HTTP antares(ACCESSKEY);

#define DHTPIN 14          // 3=RX, 4=D2(SDA), 5=D1(SCL), 12=D6, 13=D7, 14=D5
#define DHTTYPE DHT22     
#define SOILPIN A0

BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  Wire.begin();
  lightMeter.begin();
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float s = analogRead(SOILPIN)/60.0;
  float l = lightMeter.readLightLevel();

  String data = String("{\"H\":") + h + ",\"T\":" + t + ",\"S\":" + s + ",\"L\":" + l + "}";

  antares.send(PROJECTNAME, DEVICENAME, data);

  delay(30000);          //600.000 = 10 menit
}
