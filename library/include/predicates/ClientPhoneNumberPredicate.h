//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#ifndef CARRENTAL_CLIENTPHONENUMBERPREDICATE_H
#define CARRENTAL_CLIENTPHONENUMBERPREDICATE_H

#include "model/Client.h"

class ClientPhoneNumberPredicate
{
    std::string phoneNumber;
public:
    explicit ClientPhoneNumberPredicate(const std::string &phoneNumber) : phoneNumber(phoneNumber)
    {}

    bool operator()(const ClientPtr &ptr)
    {
        return ptr->getPhoneNumber() == phoneNumber;
    }
};

#endif //CARRENTAL_CLIENTPHONENUMBERPREDICATE_H
