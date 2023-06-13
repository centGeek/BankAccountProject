//
// Created by student on 25.05.23.
//

#include "model/Address.h"
#include "exceptions/AddressException.h"

using namespace std;


Address::Address(const string &city, const string &street, const string &number) : city(city), street(street), number(number)
{
    if (city.empty()) throw AddressException(AddressException::cityException);
    if (street.empty()) throw AddressException(AddressException::streetException);
    if (number.empty()) throw AddressException(AddressException::streetNumberException);
}

string Address::getAddressInfo()
{
    return "Street: " + this->street + " | Street's number: " + this->number + " | City: " + this->city;
}