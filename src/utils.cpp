#include "utils.h"
#include <iostream>
#include <limits>
#include <ctime>

namespace Utils {

    int getValidInt() {
        int value;
        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    double getValidDouble() {
        double value;
        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    std::string getValidString() {
        std::string value;
        std::getline(std::cin, value);
        while (value.empty() || value.find_first_not_of(" \t\r\n") == std::string::npos) {
            std::cout << "Input cannot be empty. Please enter again: ";
            std::getline(std::cin, value);
        }
        return value;
    }

    std::string getCurrentTimestamp() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char dateString[30];
        snprintf(dateString, sizeof(dateString), "%04d-%02d-%02d %02d:%02d:%02d", 
                 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
                 ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        return std::string(dateString);
    }

}
