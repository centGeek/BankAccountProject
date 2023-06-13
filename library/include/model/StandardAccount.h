//
// Created by student on 06.06.23.
//

#ifndef CARRENTAL_STANDARDACCOUNT_H
#define CARRENTAL_STANDARDACCOUNT_H


#include "BankAccount.h"

class StandardAccount : public BankAccount
{
    double debit;
public:
    StandardAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime);

    void payOffDebit(double value);

    std::string getBankAccountInfo() const;

    std::string getAccountInfo() override;

    double getDebit() const;

    void setDebit(double debit);

    std::string getAccountType() override;

};


#endif //CARRENTAL_STANDARDACCOUNT_H
