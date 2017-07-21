#ifndef WifiCredentialsRepository_h
#define WifiCredentialsRepository_h

#include <string>
#include "WifiCredentials.h"

class WifiCredentialsRepository
{
  public:
    virtual WifiCredentials read(std::string ssid) = 0;
    virtual bool save(WifiCredentials credentials) = 0;
    virtual ~WifiCredentialsRepository() {}
};

#endif