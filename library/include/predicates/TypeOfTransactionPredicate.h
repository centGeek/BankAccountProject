//
// Created by Wiktor Stępniewski on 10/06/2023.
//

#ifndef BANKACCOUNTS_TYPEOFTRANSACTIONPREDICATE_H
#define BANKACCOUNTS_TYPEOFTRANSACTIONPREDICATE_H

#include "model/Transaction.h"

class TypeOfTransactionPredicate
{
    std::string typeOfTransaction;
public:
    explicit TypeOfTransactionPredicate(const std::string &typeOfTransaction) : typeOfTransaction(typeOfTransaction)
    {}

    bool operator()(const TransactionPtr &ptr)
    {
        return ptr->getTransactionType() == typeOfTransaction;
    }
};

#endif //BANKACCOUNTS_TYPEOFTRANSACTIONPREDICATE_H
