//
// Created by student on 06.06.23.
//

#ifndef CARRENTAL_CURRENCYACCOUNT_H
#define CARRENTAL_CURRENCYACCOUNT_H

#include <iostream>
#include "CurrencyType.h"
#include "BankAccount.h"


class CurrencyAccount : public BankAccount
{
private:
    CurrencyType currency;
public:
    CurrencyAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, CurrencyType currency);

    void convertingCurrency(CurrencyType possessedCurr, CurrencyType expectedCurr);

    std::string getBankAccountInfo();

    CurrencyType getCurrency() const;

    std::string getAccountType() override;

    void setCurrency(CurrencyType currency);

    std::string getAccountInfo() override;

};


#endif //CARRENTAL_CURRENCYACCOUNT_H
