#include "SSD1306.h"
#include "WifiConfCaptivePortal.h"
#include "EEPROMWifiCredentialsRepository.h"

SSD1306 display(0x3c, D1, D2);

EEPROMWifiCredentialsRepository* wifiCredentialsRepository = new EEPROMWifiCredentialsRepository;
WifiConfCaptivePortal captivePortal(80, *wifiCredentialsRepository);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Setup ini");
  captivePortal.setTemplate("new template");
  captivePortal.start();
  Serial.println("Setup END");
}

void loop()
{
  captivePortal.handleRequest();
}
