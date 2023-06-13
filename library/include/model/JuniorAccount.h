//
// Created by student on 06.06.23.
//

#ifndef CARRENTAL_JUNIORACCOUNT_H
#define CARRENTAL_JUNIORACCOUNT_H


#include "BankAccount.h"
#include "StandardAccount.h"

class JuniorAccount : public BankAccount
{
private:
    BankAccountPtr parentAccountPtr;
public:
    JuniorAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, const BankAccountPtr &parentAccountPtr);

    std::string getBankAccountInfo();

    std::string getAccountType() override;

    std::string getAccountInfo() override;


};


#endif //CARRENTAL_JUNIORACCOUNT_H
