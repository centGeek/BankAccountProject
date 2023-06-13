//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_DIAMOND_H
#define CARRENTAL_DIAMOND_H

#include "ClientType.h"

class Diamond : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;

};


#endif //CARRENTAL_DIAMOND_H
