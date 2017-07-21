#include "EEPROMWifiCredentialsRepository.h"
#include "WifiCredentials.h"

EEPROMWifiCredentialsRepository::EEPROMWifiCredentialsRepository()
{
}
WifiCredentials EEPROMWifiCredentialsRepository::read(std::string ssid)
{
    //TODO: read credentials from EEPROM;
    WifiCredentials credentials;
    credentials.ssid = "ssid";
    credentials.password = "password";
    return credentials;
}

bool EEPROMWifiCredentialsRepository::save(WifiCredentials credentials)
{
    return false;
}
EEPROMWifiCredentialsRepository::~EEPROMWifiCredentialsRepository() {}
