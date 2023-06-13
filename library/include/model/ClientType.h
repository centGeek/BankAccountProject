//
// Created by student on 25.05.23.
//

#ifndef CARRENTAL_CLIENTTYPE_H
#define CARRENTAL_CLIENTTYPE_H

#include <iostream>

class ClientType
{
public:
    virtual ~ClientType();

    virtual std::string getClientTypeInfo();

    virtual int getMaxActiveAccounts();
};


#endif //CARRENTAL_CLIENTTYPE_H
