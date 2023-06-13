//
// Created by student on 06.06.23.
//

#ifndef CARRENTAL_SAVINGACCOUNT_H
#define CARRENTAL_SAVINGACCOUNT_H


#include "BankAccount.h"
#include <boost/date_time.hpp>


class SavingAccount : public BankAccount
{
private:
    float interestRate;

public:
    SavingAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, float interestRate);

    double monthEvaluation();

    std::string getBankAccountInfo();

    void setInterestRate(float interestRate);

    float getInterestRate() const;

    std::string getAccountType() override;

    std::string getAccountInfo() override;

};


#endif //CARRENTAL_SAVINGACCOUNT_H
