//
// Created by Wiktor Stępniewski on 04/06/2023.
//

#ifndef CARRENTAL_CLIENTSURNAMEPREDICATE_H
#define CARRENTAL_CLIENTSURNAMEPREDICATE_H

#include "model/Client.h"

class LastNamePredicate
{
    std::string lastName;

public:
    explicit LastNamePredicate(const std::string &firstName) : lastName(lastName)
    {}

    bool operator()(const ClientPtr &ptr)
    {
        return ptr->getSurname() == lastName;
    }
};

#endif //CARRENTAL_CLIENTSURNAMEPREDICATE_H
