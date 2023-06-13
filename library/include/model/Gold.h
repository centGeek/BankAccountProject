//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_GOLD_H
#define CARRENTAL_GOLD_H

#include "ClientType.h"

class Gold : public ClientType
{
public:
    std::string getClientTypeInfo() override;

    int getMaxActiveAccounts() override;

};


#endif //CARRENTAL_GOLD_H
