#include "customer.h"
#include <sstream>

Customer::Customer(int id, const std::string& name, const std::string& contact)
    : customerId(id), name(name), contact(contact) {}

int Customer::getId() const { return customerId; }
std::string Customer::getName() const { return name; }
std::string Customer::getContact() const { return contact; }

std::string Customer::toCSV() const {
    std::stringstream ss;
    ss << customerId << "," << name << "," << contact;
    return ss.str();
}

Customer Customer::fromCSV(const std::string& csvLine) {
    Customer cust;
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ',')) cust.customerId = std::stoi(token);
    if (std::getline(ss, token, ',')) cust.name = token;
    if (std::getline(ss, token, ',')) cust.contact = token;

    return cust;
}
