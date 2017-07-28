#include "EEPROMWifiCredentialsRepository.h"
#include "WifiCredentials.h"

EEPROMWifiCredentialsRepository::EEPROMWifiCredentialsRepository()
{
}
WifiCredentials EEPROMWifiCredentialsRepository::read()
{
    EEPROM.begin(512);
    WifiCredentials credentials;
    EEPROM.get(0, credentials.ssid);
    EEPROM.get(0 + sizeof(credentials.ssid), credentials.password);
    char ok[2 + 1];
    EEPROM.get(0 + sizeof(credentials.ssid) + sizeof(credentials.password), ok);
    EEPROM.end();
    if (std::string(ok) != std::string("OK"))
    {
        credentials.ssid[0] = 0;
        credentials.password[0] = 0;
    }

    Serial.println("Recovered credentials:");
    Serial.println(credentials.ssid);
    Serial.println(strlen(credentials.password) > 0 ? "********" : "<no password>");
    return credentials;
}

void EEPROMWifiCredentialsRepository::save(WifiCredentials credentials)
{
    EEPROM.begin(512);
    EEPROM.put(0, credentials.ssid);
    EEPROM.put(0 + sizeof(credentials.ssid), credentials.password);
    char ok[2 + 1] = "OK";
    EEPROM.put(0 + sizeof(credentials.ssid) + sizeof(credentials.password), ok);
    EEPROM.commit();
    EEPROM.end();
}

EEPROMWifiCredentialsRepository::~EEPROMWifiCredentialsRepository() {}
