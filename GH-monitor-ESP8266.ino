#include <AntaresESP8266HTTP.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>

/* credential */
#define ACCESSKEY "181b1730efb9f453:1860de96ede6acb0"
#define WIFISSID "GH-monitor"
#define PASSWORD "sakuraprada"
#define projectName "greenhouse-nodemcu"
#define deviceName "GH-monitor"

AntaresESP8266HTTP antares(ACCESSKEY);

#define DHTPIN 14          // 3=RX, 4=D2(SDA), 5=D1(SCL), 12=D6, 13=D7, 14=D5
#define DHTTYPE DHT22     
#define soilPin A0
int soilValue;

BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);
float t,h,s,l;

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  Wire.begin();
  lightMeter.begin();
  dht.begin();
}

void loop() {
  delay(30000);          //600.000 = 10 menit

  h = dht.readHumidity();
  t = dht.readTemperature();
  soilValue = analogRead(soilPin);
  s = soilValue/60;
  l = lightMeter.readLightLevel();

  antares.add("H", h);
  antares.add("T", t);
  antares.add("S", s);
  antares.add("L", l);

  antares.send(projectName, deviceName);
}
