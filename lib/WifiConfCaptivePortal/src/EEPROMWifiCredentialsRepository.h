#ifndef EEPROMWifiCredentialsRepository_h
#define EEPROMWifiCredentialsRepository_h

#include <string>
#include "WifiCredentialsRepository.h"
#include <EEPROM.h>
#include "SSD1306.h"
struct WifiCredentials;

class EEPROMWifiCredentialsRepository : public WifiCredentialsRepository
{

  public:
    EEPROMWifiCredentialsRepository();
    WifiCredentials read();
    void save(WifiCredentials credentials);
    ~EEPROMWifiCredentialsRepository();
};

#endif
