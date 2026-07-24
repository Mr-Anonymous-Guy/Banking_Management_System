#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

namespace Authentication {
    bool validatePIN(const std::string& storedPIN);
}

#endif // AUTHENTICATION_H
