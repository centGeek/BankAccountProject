//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#ifndef CARRENTAL_CLIENTEXCEPTION_H
#define CARRENTAL_CLIENTEXCEPTION_H


#include <stdexcept>
#include <string>

class ClientException : public std::logic_error
{
public:
    explicit ClientException(const std::string &);

    static const std::string firstNameException;
    static const std::string lastNameException;
    static const std::string phoneNumberException;
    static const std::string clientTypeException;
    static const std::string addressException;
    static const std::string clientWrongIndex;
    static const std::string clientWrongPtr;
    static const std::string tooManyActiveAccounts;
};


#endif //CARRENTAL_CLIENTEXCEPTION_H
