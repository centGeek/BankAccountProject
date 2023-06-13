//
// Created by Wiktor Stępniewski on 12/06/2023.
//

#ifndef BANKACCOUNTS_ADDRESSEXCEPTION_H
#define BANKACCOUNTS_ADDRESSEXCEPTION_H


#include <stdexcept>
#include <string>

class AddressException : public std::logic_error
{
public:
    explicit AddressException(const std::string &);

    static const std::string streetException;
    static const std::string cityException;
    static const std::string streetNumberException;
};

#endif //BANKACCOUNTS_ADDRESSEXCEPTION_H
