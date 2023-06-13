//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_SILVER_H
#define CARRENTAL_SILVER_H

#include "ClientType.h"

class Silver : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;

};


#endif //CARRENTAL_SILVER_H
