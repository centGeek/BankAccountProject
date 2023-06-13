//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_BRONZE_H
#define CARRENTAL_BRONZE_H

#include "ClientType.h"

class Bronze : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;
};


#endif //CARRENTAL_BRONZE_H
