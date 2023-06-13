//
// Created by Wiktor Stępniewski on 04/06/2023.
//

#ifndef CARRENTAL_CLIENTFIRSTNAMEPREDICATE_H
#define CARRENTAL_CLIENTFIRSTNAMEPREDICATE_H

#include "model/Client.h"


class FristNamePredicate
{
    std::string firstName;
public:
    explicit FristNamePredicate(const std::string &firstName) : firstName(firstName)
    {}

    bool operator()(const ClientPtr &ptr)
    {
        return ptr->getName() == firstName;
    }
};

#endif //CARRENTAL_CLIENTFIRSTNAMEPREDICATE_H
