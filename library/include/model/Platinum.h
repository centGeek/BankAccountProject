//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_PLATINUM_H
#define CARRENTAL_PLATINUM_H

#include "ClientType.h"

class Platinum : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;

};


#endif //CARRENTAL_PLATINUM_H
