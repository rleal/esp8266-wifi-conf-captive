#ifndef EEPROMWifiCredentialsRepository_h
#define EEPROMWifiCredentialsRepository_h


#include <string>
#include "WifiCredentialsRepository.h"

struct WifiCredentials;

class EEPROMWifiCredentialsRepository : public WifiCredentialsRepository
{

  public:
    EEPROMWifiCredentialsRepository();
    WifiCredentials read(std::string ssid);
    bool save(WifiCredentials credentials);
    ~EEPROMWifiCredentialsRepository();
};

#endif
