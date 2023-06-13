//
// Created by Wiktor Stępniewski on 12/06/2023.
//

#include "exceptions/AddressException.h"
using namespace std;

AddressException::AddressException(const std::string &exc) : logic_error(exc)
{}

const string AddressException::cityException = "City is empty";
const string AddressException::streetException = "Street is empty";
const string AddressException::streetNumberException = "Street's number is empty";