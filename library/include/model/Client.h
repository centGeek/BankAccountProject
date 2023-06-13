//
// Created by student on 25.05.23.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "typedefs.h"
#include "Address.h"
#include "ClientType.h"

class Client
{
private:
    boost::uuids::uuid clientId;
    std::string name;
    std::string surname;
    std::string phoneNumber;
    AddressPtr addressPtr;
    bool isArchive;
    ClientTypePtr clientTypePtr;
    int activeAccounts;

public:
    Client(const std::string &name, const std::string &surname, const std::string &phoneNumber, const AddressPtr &addressPtr, const ClientTypePtr &clientTypePtr);

    std::string getClientInfo();

    const std::string &getName() const;

    std::string getClientType() const;

    const std::string &getSurname() const;

    const std::string &getPhoneNumber() const;

    const AddressPtr &getAddressPtr() const;

    void setArchiveStatus(bool isArchive);

    bool isArchiveStatus() const;

    void setClientTypePtr(const ClientTypePtr &typePtr);

    void setAddressPtr(const AddressPtr &addressPtr);

    const boost::uuids::uuid &getClientId() const;

    int getMaxActiveAccounts() const;

    int getActiveAccounts() const;

    void setActiveAccounts(int activeAccounts);
};

#endif // PROJECT_CLIENT_H