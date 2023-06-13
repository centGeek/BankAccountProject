//
// Created by student on 01.06.23.
//

#include "model/ClientType.h"

ClientType::~ClientType() = default;


std::string ClientType::getClientTypeInfo()
{
    return "Type";
}

int ClientType::getMaxActiveAccounts()
{
    return 0;
}

