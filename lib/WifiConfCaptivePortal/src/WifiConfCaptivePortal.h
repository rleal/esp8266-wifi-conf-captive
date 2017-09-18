#ifndef WifiConfCaptivePortal_h
#define WifiConfCaptivePortal_h

#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "WifiCredentialsRepository.h"

class WifiConfCaptivePortal
{
private:
  const byte DNS_PORT = 53;
  IPAddress apIP;
  IPAddress netMsk;
  ESP8266WebServer webServer;
  DNSServer dnsServer;

  void handleSaveWifi()
  {
    Serial.println("handle save wifi");
  }
  void handleWifi()
  {

    webServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    webServer.sendHeader("Pragma", "no-cache");
    webServer.sendHeader("Expires", "-1");
    webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
    webServer.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    webServer.sendContent(
        "<html><head></head><body>"
        "<h1>Wifi config</h1>");
    webServer.sendContent(
        "<table><tr><th align='left'>WLAN config</th></tr>");
    webServer.sendContent(
        "</table>"
        "\r\n<br />"
        "<table><tr><th align='left'>WLAN list (refresh if any missing)</th></tr>");
    Serial.println("scan start");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n > 0)
    {
      for (int i = 0; i < n; i++)
      {
        webServer.sendContent(String() + "\r\n<tr><td>SSID " + WiFi.SSID(i) + String((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : " *") + " (" + WiFi.RSSI(i) + ")</td></tr>");
      }
    }
    else
    {
      webServer.sendContent(String() + "<tr><td>No WLAN found</td></tr>");
    }
    webServer.sendContent(
        "</table>"
        "\r\n<br /><form method='POST' action='wifisave'><h4>Connect to network:</h4>"
        "<input type='text' placeholder='network' name='n'/>"
        "<br /><input type='password' placeholder='password' name='p'/>"
        "<br /><input type='submit' value='Connect/Disconnect'/></form>"
        "<p>You may want to <a href='/'>return to the home page</a>.</p>"
        "</body></html>");
    webServer.client().stop(); // Stop is needed because we sent no content length
  }

public:
  WifiConfCaptivePortal(int port, WifiCredentialsRepository &wifiCredentialsRepository);
  void start();
  void handleRequest();
  ~WifiConfCaptivePortal();
};

#endif
