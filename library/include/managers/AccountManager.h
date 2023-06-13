//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#ifndef CARRENTAL_ACCOUNTMANAGER_H
#define CARRENTAL_ACCOUNTMANAGER_H

#include "repositories/Repository.h"
#include "model/BankAccount.h"
#include "typedefs.h"
#include "model/CurrencyType.h"

class AccountManager
{
    Repository<BankAccount> activeAccounts;
    Repository<BankAccount> inActiveAccounts;
public:

    AccountManager();

    ~AccountManager();

    std::vector<BankAccountPtr> findAccountsByPredicate(const BankAccountPredicate &predicate) const;

    std::vector<BankAccountPtr> findAllAccounts() const;

    BankAccountPtr createCurrencyAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, CurrencyType currency);

    BankAccountPtr createStandardAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime);

    BankAccountPtr createJuniorAccount(const ClientPtr &ptrChild, const boost::posix_time::ptime &creationTime, const BankAccountPtr &ptrParentAccount);

    BankAccountPtr createSavingAccount(const ClientPtr &, const boost::posix_time::ptime &, const float &);

    void closeAccount(const BankAccountPtr &ptrBankAccount);

    void saveToFileAccounts();
};


#endif //CARRENTAL_ACCOUNTMANAGER_H
