//
// Created by Wiktor Stępniewski on 04/06/2023.
//

#ifndef CARRENTAL_CLIENTACCOUNTSPREDICATE_H
#define CARRENTAL_CLIENTACCOUNTSPREDICATE_H

#include "model/Client.h"
#include "model/BankAccount.h"

class ClientAccountPredicate
{
    std::string clientPhoneNumber;
public:
    explicit ClientAccountPredicate(const std::string clientPhoneNumber) : clientPhoneNumber(clientPhoneNumber)
    {}

    bool operator()(const BankAccountPtr &ptr)
    {
        return ptr->getPtrClient()->getPhoneNumber() == clientPhoneNumber;
    }
};

#endif //CARRENTAL_CLIENTACCOUNTSPREDICATE_H
