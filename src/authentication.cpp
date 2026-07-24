#include "authentication.h"
#include "utils.h"
#include <iostream>

namespace Authentication {

    bool validatePIN(const std::string& storedPIN) {
        int attempts = 3;
        while (attempts > 0) {
            std::cout << "Enter 4-digit PIN: ";
            std::string inputPIN = Utils::getValidString();
            
            if (inputPIN == storedPIN) {
                return true;
            }
            
            attempts--;
            if (attempts > 0) {
                std::cout << "Incorrect PIN. " << attempts << " attempts remaining.\n";
            }
        }
        
        std::cout << "Authentication failed. Account temporarily locked for this session.\n";
        return false;
    }

}
