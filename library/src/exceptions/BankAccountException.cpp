//
// Created by Wiktor Stępniewski on 02/06/2023.
//

#include "exceptions/BankAccountException.h"


using namespace std;

BankAccountException::BankAccountException(const std::string &exc) : logic_error(exc)
{}

const string BankAccountException::clientNotExistException = "Given client does not exist";
const string BankAccountException::incompleteCurrencyConverting = "you cannot convert currency to your own currency";
const string BankAccountException::positiveAccountBalance = "You cannot close your account, because your account balance is positive";
const string BankAccountException::nullAccountPointer = "Given bank account pointer is null";
const string BankAccountException::negativeAmount = "Given amount is negative";
const string BankAccountException::positiveDebit = "Your debit cannot be positive value";
const string BankAccountException::bankAccountNotExistException = "Given bank account does not exist";