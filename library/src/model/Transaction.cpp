//
// Created by student on 02.06.23.
//

#include "model/Transaction.h"

#include <utility>
#include "exceptions/TransactionException.h"
#include "model/CurrencyAccount.h"
#include "model/StandardAccount.h"


using namespace std;

Transaction::Transaction(BankAccountPtr sourceAcc, BankAccountPtr destinationAcc, double amount)
        : sourceAcc(sourceAcc), destinationAcc(destinationAcc), amount(amount)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(destinationAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    this->transactionId = boost::uuids::random_generator()();
}

Transaction::Transaction(const BankAccountPtr &sourceAcc, double amount) : sourceAcc(sourceAcc), amount(amount)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    this->transactionId = boost::uuids::random_generator()();
}

bool Transaction::moneyTransfer(const BankAccountPtr &sourceAcc, const BankAccountPtr &destinationAcc, double value)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(destinationAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    this->transactionType = "transfer";
    if (value <= 0)
        throw TransactionException(TransactionException::outOfRangeException);
    if (sourceAcc->getAccountBalance() < value)
        throw TransactionException(TransactionException::withdrawMoneyException);
    sourceAcc->setAccountBalance(sourceAcc->getAccountBalance() - value);
    destinationAcc->setAccountBalance(destinationAcc->getAccountBalance() + value);
    return true;
}

bool Transaction::depositMoney(const BankAccountPtr &account, double amount)
{
    if(account==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(amount<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "deposit";
    if (amount <= 0)
        throw TransactionException(TransactionException::outOfRangeException);
    account->setAccountBalance(account->getAccountBalance() + amount);
    return true;
}

bool Transaction::withdrawMoney(const BankAccountPtr &account, double amount)
{
    if(account==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(amount<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "withdraw";
    if (amount <= 0)
        throw TransactionException(TransactionException::outOfRangeException);
    if (account->getAccountBalance() < amount)
        throw TransactionException(TransactionException::withdrawMoneyException);
    account->setAccountBalance(account->getAccountBalance() - amount);
    return true;
}

bool Transaction::withdrawMoney(const StandardAccountPtr &account, double amount)
{
    if(account==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(amount<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "withdraw";
    if (amount <= 0)
        throw TransactionException(TransactionException::outOfRangeException);
    if (account->getAccountBalance() < amount)
    {
        account->setAccountBalance(account->getAccountBalance() - amount);
        account->setDebit(account->getAccountBalance());
        account->setAccountBalance(0);
        return true;
    }
    account->setAccountBalance(account->getAccountBalance() - amount);
    return true;
}

std::string Transaction::getTransactionInfo()
{
    if (this->getTransactionType() == "transfer")
        return "Transaction id: " + to_string(this->transactionId) + "\nTransaction type: " + this->getTransactionType() + "\nTransaction amount: " + to_string(this->amount) + "\nSource Account:\n" +
               this->sourceAcc->getAccountInfo() +
               "\n=====\nDestination Account:\n" +
               this->destinationAcc->getAccountInfo() + "\n";
    else
        return "Transaction id: " + to_string(this->transactionId) + "\nTransaction type: " + this->getTransactionType() + "\nTransaction amount: " + to_string(this->amount) + "\nSource Account:\n" +
               this->sourceAcc->getAccountInfo() + "\n";
}


bool Transaction::moneyTransferCurrencyAccount(const CurrencyAccountPtr &sourceAcc, const CurrencyAccountPtr &destinationAcc, double value)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(destinationAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(value<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "transfer";
    if (sourceAcc->getCurrency() != PLN || destinationAcc->getCurrency() != PLN)
    {
        CurrencyType previousCurrencySourceAcc = sourceAcc->getCurrency();
        sourceAcc->convertingCurrency(previousCurrencySourceAcc, PLN);
        CurrencyType previousCurrencyDestinationAcc = destinationAcc->getCurrency();
        destinationAcc->convertingCurrency(previousCurrencyDestinationAcc, PLN);
        this->moneyTransfer(sourceAcc, destinationAcc, value);
        sourceAcc->convertingCurrency(PLN, previousCurrencySourceAcc);
        destinationAcc->convertingCurrency(PLN, previousCurrencyDestinationAcc);
        return true;
    }
    return false;
}

bool Transaction::moneyTransferCurrencyAccount(const CurrencyAccountPtr &sourceAcc, const BankAccountPtr &destinationAcc,
                                               double value)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(destinationAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(value<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "transfer";
    if (sourceAcc->getCurrency() != PLN)
    {
        CurrencyType previousCurrencySourceAcc = sourceAcc->getCurrency();
        sourceAcc->convertingCurrency(previousCurrencySourceAcc, PLN);
        this->moneyTransfer(sourceAcc, destinationAcc, value);
        sourceAcc->convertingCurrency(PLN, previousCurrencySourceAcc);
        return true;
    }
    return false;
}

bool Transaction::moneyTransferCurrencyAccount(const BankAccountPtr &sourceAcc, const CurrencyAccountPtr &destinationAcc, double value)
{
    if(sourceAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(destinationAcc==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(value<=0) throw TransactionException(TransactionException::outOfRangeException);
    this->transactionType = "transfer";
    if (destinationAcc->getCurrency() != PLN)
    {
        CurrencyType previousCurrencyDestinationAcc = destinationAcc->getCurrency();
        destinationAcc->convertingCurrency(previousCurrencyDestinationAcc, PLN);
        this->moneyTransfer(sourceAcc, destinationAcc, value);
        destinationAcc->convertingCurrency(PLN, previousCurrencyDestinationAcc);
        return true;
    }
    return false;
}

bool Transaction::depositMoneyCurrencyAccount(const CurrencyAccountPtr &account, double amount)
{
    if(account==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(amount<=0) throw TransactionException(TransactionException::outOfRangeException);
    CurrencyType previousCurrency = account->getCurrency();
    this->transactionType = "deposit";
    if (account->getCurrency() == PLN)
        return this->depositMoney(account, amount);

        account->convertingCurrency(account->getCurrency(), PLN);
        this->depositMoney(account, amount);
        account->convertingCurrency(PLN, previousCurrency);
        return true;
}

bool Transaction::withdrawMoneyCurrencyAccount(const CurrencyAccountPtr &account, double amount)
{
    if(account==nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if(amount<=0) throw TransactionException(TransactionException::outOfRangeException);
    CurrencyType previousCurrency = account->getCurrency();
    this->transactionType = "withdraw";
    if (account->getCurrency() == PLN)
        return this->withdrawMoney(account, amount);

        account->convertingCurrency(account->getCurrency(), PLN);
        this->withdrawMoney(account, amount);
        account->convertingCurrency(PLN, previousCurrency);
        return true;
}

string Transaction::getTransactionType() const
{
    return transactionType;
}

BankAccountPtr Transaction::getSourceAccount()
{
    return this->sourceAcc;
}

double Transaction::getTransactionValue()
{
    return this->amount;
}
