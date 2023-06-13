//
// Created by student on 02.06.23.
//

#ifndef CARRENTAL_TRANSACTION_H
#define CARRENTAL_TRANSACTION_H

#include <iostream>
#include "typedefs.h"
#include "Client.h"
#include "BankAccount.h"

class Transaction
{
    boost::uuids::uuid transactionId;
    BankAccountPtr sourceAcc;
    BankAccountPtr destinationAcc;
    double amount;
    std::string transactionType;
public:
    Transaction(BankAccountPtr sourceAcc, BankAccountPtr destinationAcc, double amount);

    Transaction(const BankAccountPtr &sourceAcc, double amount);

    bool moneyTransfer(const BankAccountPtr &sourceAcc, const BankAccountPtr &destinationAcc, double value);

    bool moneyTransferCurrencyAccount(const CurrencyAccountPtr &sourceAcc, const CurrencyAccountPtr &destinationAcc, double value);

    bool moneyTransferCurrencyAccount(const BankAccountPtr &sourceAcc, const CurrencyAccountPtr &destinationAcc, double value);

    bool moneyTransferCurrencyAccount(const CurrencyAccountPtr &sourceAcc, const BankAccountPtr &destinationAcc, double value);

    bool depositMoney(const BankAccountPtr &account, double amount);

    bool depositMoneyCurrencyAccount(const CurrencyAccountPtr &account, double amount);

    bool withdrawMoney(const BankAccountPtr &account, double amount);

    bool withdrawMoney(const StandardAccountPtr &account, double amount);

    bool withdrawMoneyCurrencyAccount(const CurrencyAccountPtr &account, double amount);

    BankAccountPtr getSourceAccount();

    double getTransactionValue();

    std::string getTransactionInfo();

    std::string getTransactionType() const;
};


#endif //CARRENTAL_TRANSACTION_H
