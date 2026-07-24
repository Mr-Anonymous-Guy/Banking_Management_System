#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    int customerId;
    std::string name;
    std::string contact;

public:
    Customer() : customerId(0) {}
    Customer(int id, const std::string& name, const std::string& contact);

    int getId() const;
    std::string getName() const;
    std::string getContact() const;

    std::string toCSV() const;
    static Customer fromCSV(const std::string& csvLine);
};

#endif // CUSTOMER_H
