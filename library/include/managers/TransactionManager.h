//
// Created by Wiktor Stępniewski on 08/06/2023.
//

#ifndef BANKACCOUNTS_TRANSACTIONMANAGER_H
#define BANKACCOUNTS_TRANSACTIONMANAGER_H

#include "typedefs.h"
#include "repositories/Repository.h"
#include "model/Transaction.h"


class TransactionManager
{
    Repository<Transaction> transactions;

public:

    TransactionManager();

    ~TransactionManager();

    std::vector<TransactionPtr> findAllTransactions();

    std::vector<TransactionPtr> findTransactionsByPredicate(const TransactionPredicate &predicate);

    bool moneyTransfer(const BankAccountPtr &destinationAcc, const BankAccountPtr &sourceAcc, const double &value);

    bool depositMoney(const BankAccountPtr &account, double amount);

    bool withdrawMoney(const BankAccountPtr &account, double amount);

    void saveToFileTransactions();

private:
    void changeClientType(const ClientPtr &ptrClient);

    double countClientDeposit(const ClientPtr &ptrClient);
};

#endif // BANKACCOUNTS_TRANSACTIONMANAGER_H
