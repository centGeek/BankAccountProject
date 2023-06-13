//
// Created by student on 25.05.23.
//

#ifndef PROJECT_ADDRESS_H
#define PROJECT_ADDRESS_H

#include <iostream>


class Address
{
private:
    std::string city;
    std::string street;
    std::string number;

public:
    Address(const std::string &city, const std::string &street, const std::string &number);

    std::string getAddressInfo();
};

#endif //PROJECT_ADDRESS_H
