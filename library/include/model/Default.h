//
// Created by student on 25.05.23.
//

#ifndef CARRENTAL_DEFAULT_H
#define CARRENTAL_DEFAULT_H


#include "ClientType.h"

class Default : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;

};


#endif //CARRENTAL_DEFAULT_H
