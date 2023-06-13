//
// Created by student on 03.06.23.
//

#ifndef CARRENTAL_TRANSACTIONEXCEPTION_H
#define CARRENTAL_TRANSACTIONEXCEPTION_H

#include <stdexcept>
#include <string>


class TransactionException : public std::logic_error
{
public:
    explicit TransactionException(const std::string &);

    static const std::string withdrawMoneyException;
    static const std::string outOfRangeException;
    static const std::string nullBankAcountPointer;
};


#endif //CARRENTAL_TRANSACTIONEXCEPTION_H
