#include "SSD1306.h"
//#include "WifiConfCaptivePortal.h"
//#include "EEPROMWifiCredentialsRepository.h"
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#define USE_SERIAL Serial
//SSD1306 display(0x3c, D1, D2);


uint32_t chipId = UINT32_MAX;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Setup ini");

  chipId = ESP.getChipId();
Serial.println(chipId);

  //captivePortal.start();
  WiFiManager wifiManager;
  wifiManager.autoConnect();

delay(500);
  Serial.println("Setup END");
}

int n = 0;

void loop()
{

  HTTPClient http;

  USE_SERIAL.print("[HTTP] begin...\n");

  String url = "https://redcheck-c4915.firebaseio.com/nodes/";

  url.concat(chipId);
  url.concat(".json");

  USE_SERIAL.println(url);

  int beginResult = http.begin(url, "B8:4F:40:70:0C:63:90:E0:07:E8:7D:BD:B4:11:D0:4A:EA:9C:90:F6"); //HTTP

  USE_SERIAL.print("[HTTP] PUT...\n");

  // start connection and send HTTP header
  
  
  USE_SERIAL.printf("Chip Id %d\n", chipId);

  //TODO: POST ack
  String postBody;

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["ack"] = true;

  root.printTo(postBody);

  int httpCode = http.sendRequest("PUT", postBody);

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("[HTTP] PUT... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      USE_SERIAL.println(payload);
    }
  }
  else
  {
    USE_SERIAL.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  delay(10000);

  //TODO: reset when press a button

  //TODO: every min ack server with id
}
