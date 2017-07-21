#include "WifiConfCaptivePortal.h"
#include "EEPROMWifiCredentialsRepository.h"

WifiConfCaptivePortal::WifiConfCaptivePortal(
    int port,
    WifiCredentialsRepository &wifiCredentialsRepository)
    : dnsServer{DNSServer()},
      webServer{ESP8266WebServer(port)},
      apIP{IPAddress(192, 168, 1, 1)},
      netMsk{IPAddress(255, 255, 255, 0)},
      captiveTemplate{""}
{
}

void WifiConfCaptivePortal::setTemplate(String html)
{
  captiveTemplate = html;
}

void WifiConfCaptivePortal::start()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP("CaptivePortal");

  dnsServer.start(DNS_PORT, "*", apIP);
  webServer.onNotFound([this]() {
    handleWifi();
  });

  webServer.begin();
}
void WifiConfCaptivePortal::handleRequest()
{
  dnsServer.processNextRequest();
  webServer.handleClient();
}

WifiConfCaptivePortal::~WifiConfCaptivePortal() {}