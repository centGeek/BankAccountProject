//
// Created by Wiktor Stępniewski on 02/06/2023.
//

#ifndef CARRENTAL_BANKACCOUNTEXCEPTION_H
#define CARRENTAL_BANKACCOUNTEXCEPTION_H

#include <stdexcept>
#include <string>


class BankAccountException : public std::logic_error
{
public:
    explicit BankAccountException(const std::string &);

    static const std::string clientNotExistException;
    static const std::string incompleteCurrencyConverting;
    static const std::string positiveAccountBalance;
    static const std::string nullAccountPointer;
    static const std::string negativeAmount;
    static const std::string positiveDebit;
    static const std::string bankAccountNotExistException;
};


#endif //CARRENTAL_BANKACCOUNTEXCEPTION_H
