#ifndef WifiCredentialsRepository_h
#define WifiCredentialsRepository_h

#include <string>
#include "WifiCredentials.h"

class WifiCredentialsRepository
{
  public:
    virtual WifiCredentials read() = 0;
    virtual void save(WifiCredentials credentials) = 0;
    virtual ~WifiCredentialsRepository() {}
};

#endif