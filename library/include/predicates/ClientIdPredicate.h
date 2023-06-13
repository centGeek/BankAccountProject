//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#ifndef CARRENTAL_CLIENTIDPREDICATE_H
#define CARRENTAL_CLIENTIDPREDICATE_H

#include "model/Client.h"


class ClientIdPredicate
{
    boost::uuids::uuid clientId;
public:
    explicit ClientIdPredicate(const boost::uuids::uuid &clientId) : clientId(clientId)
    {}

    bool operator()(const ClientPtr &ptr)
    {
        return ptr->getClientId() == clientId;
    }
};

#endif //CARRENTAL_CLIENTIDPREDICATE_H
