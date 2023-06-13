//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#include "exceptions/ClientException.h"

using namespace std;

ClientException::ClientException(const string &exc) : logic_error(exc)
{}

const string ClientException::firstNameException = "First name is empty";
const string ClientException::lastNameException = "Last name is empty";
const string ClientException::clientTypeException = "Client type does not exist";
const string ClientException::addressException = "Address does not exist";
const string ClientException::clientWrongIndex = "Client of that index does not exist";
const string ClientException::clientWrongPtr = "Such a client does not exist";
const string ClientException::tooManyActiveAccounts = "You have too many ative accounts to open new account";
const string ClientException::phoneNumberException = "Phone number is empty";
