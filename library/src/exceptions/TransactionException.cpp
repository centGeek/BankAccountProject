//
// Created by student on 03.06.23.
//

#include "exceptions/TransactionException.h"


TransactionException::TransactionException(const std::string &exc) : logic_error(exc)
{}

const std::string TransactionException::withdrawMoneyException = "You cannot withdraw this amount of money, "
                                                                 "because your account balance has insufficient funds";
const std::string TransactionException::outOfRangeException = "Transfer funds cannot be lower or equal 0";
const std::string TransactionException::nullBankAcountPointer = "Given bankAccount is null pointer";