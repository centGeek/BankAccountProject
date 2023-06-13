//
// Created by student on 25.05.23.
//


#include "model/Client.h"
#include "exceptions/ClientException.h"

using namespace boost::uuids;
using namespace std;

Client::Client(const string &name, const string &surname, const string &phoneNumber, const AddressPtr &addressPtr, const ClientTypePtr &clientTypePtr) :
        name(std::move(name)),
        surname(std::move(surname)),
        phoneNumber(std::move(phoneNumber)),
        addressPtr(std::move(addressPtr)),
        clientTypePtr(std::move(clientTypePtr))
{
    if (name.empty()) throw ClientException(ClientException::firstNameException);
    if (surname.empty()) throw ClientException(ClientException::lastNameException);
    if(phoneNumber.empty()) throw ClientException(ClientException::phoneNumberException);
    if (addressPtr == nullptr) throw ClientException(ClientException::addressException);
    if (clientTypePtr == nullptr) throw ClientException(ClientException::clientTypeException);
    this->clientId = boost::uuids::random_generator()();
    isArchive = false;

}

string Client::getClientInfo()
{
    return "Client Id: " + to_string(this->clientId) + "\nClient First Name: " + this->name + "\nClient Last Name: " +
           this->surname + "\nClient's phone number: " + this->phoneNumber
           + "\nClient's archived status: " + to_string(this->isArchive) + "\nClient type: " +
           clientTypePtr->getClientTypeInfo() + "\nClient's address: " + this->addressPtr->getAddressInfo();
}

const string &Client::getName() const
{
    return name;
}

const string &Client::getSurname() const
{
    return surname;
}

const string &Client::getPhoneNumber() const
{
    return phoneNumber;
}

const AddressPtr &Client::getAddressPtr() const
{
    return addressPtr;
}

const uuid &Client::getClientId() const
{
    return clientId;
}

void Client::setArchiveStatus(bool isArchive)
{
    this->isArchive = isArchive;
}

void Client::setClientTypePtr(const ClientTypePtr &typePtr)
{
    if (clientTypePtr == nullptr) throw ClientException(ClientException::clientTypeException);
    this->clientTypePtr = typePtr;
}

bool Client::isArchiveStatus() const
{
    return isArchive;
}

void Client::setAddressPtr(const AddressPtr &addressPtr)
{
    if (addressPtr == nullptr) throw ClientException(ClientException::addressException);
    this->addressPtr = addressPtr;
}

string Client::getClientType() const
{
    return clientTypePtr->getClientTypeInfo();
}

int Client::getMaxActiveAccounts() const
{
    return clientTypePtr->getMaxActiveAccounts();
}

int Client::getActiveAccounts() const
{
    return activeAccounts;
}

void Client::setActiveAccounts(int activeAccounts)
{
    this->activeAccounts = activeAccounts;
}
