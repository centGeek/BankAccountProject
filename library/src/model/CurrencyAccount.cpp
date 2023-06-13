//
// Created by student on 06.06.23.
//

#include "model/CurrencyAccount.h"
#include "exceptions/BankAccountException.h"

using namespace std;

CurrencyAccount::CurrencyAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, CurrencyType currency) :
        BankAccount(ptrClient, creationTime), currency(currency)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    this->setEndTime(pt::not_a_date_time);
    this->setAccountBalance(0);
    if (creationTime == pt::not_a_date_time) this->setCreationTime(pt::second_clock::local_time());
    else this->setCreationTime(creationTime);
}

std::string MyEnumToString(CurrencyType value)
{
    switch (value)
    {
        case USD:
            return "USD";
        case EUR:
            return "EUR";
        case CHF:
            return "CHF";
        case PLN:
            return "PLN";
        default:
            return "Unknown";
    }
}

std::string CurrencyAccount::getAccountInfo()
{
    return this->getBankAccountInfo() + "\nCreation Time: " + pt::to_simple_string(this->getCreationTime()) + "\nAccount Id: " + boost::uuids::to_string(this->getAccountId()) + "\nAccount Balance: " +
           to_string(this->getAccountBalance()) + "\nClient Info: " + this->getPtrClient()->getClientInfo();
}

std::string CurrencyAccount::getBankAccountInfo()
{
    return "Currency Account:\nCurrency: " + MyEnumToString(currency);

}

void CurrencyAccount::convertingCurrency(CurrencyType possessedCurr, CurrencyType expectedCurr)
{
    //na podstawie dnia 8 czerwca
    if (possessedCurr == EUR)
    {
        switch (expectedCurr)
        {
            case CHF:
                this->setAccountBalance(0.98 * getAccountBalance());
                break;
            case EUR:
                throw BankAccountException(BankAccountException::incompleteCurrencyConverting);
            case USD:
                this->setAccountBalance(0.931 * getAccountBalance());
                break;
            case PLN:
                this->setAccountBalance(4.48 * getAccountBalance());
                break;
        }
    } else if (possessedCurr == CHF)
    {
        switch (expectedCurr)
        {
            case CHF:
                throw BankAccountException(BankAccountException::incompleteCurrencyConverting);
            case EUR:
                this->setAccountBalance(1.02 * getAccountBalance());
                break;
            case USD:
                this->setAccountBalance(1.1 * getAccountBalance());
                break;
            case PLN:
                this->setAccountBalance(4.59 * getAccountBalance());
                break;
        }
    } else if (possessedCurr == USD)
    {
        switch (expectedCurr)
        {
            case CHF:
                this->setAccountBalance(0.91 * getAccountBalance());
                break;
            case EUR:
                this->setAccountBalance(0.93 * getAccountBalance());
                break;
            case PLN:
                this->setAccountBalance(4.17 * getAccountBalance());
                break;
            case USD:
                throw BankAccountException(BankAccountException::incompleteCurrencyConverting);
        }
    } else if (possessedCurr == PLN)
    {
        switch (expectedCurr)
        {
            case CHF:
                this->setAccountBalance(0.22 * getAccountBalance());
                break;
            case EUR:
                this->setAccountBalance(0.22 * getAccountBalance());
                break;
            case USD:
                this->setAccountBalance(0.24 * getAccountBalance());
                break;
            case PLN:
                throw BankAccountException(BankAccountException::incompleteCurrencyConverting);
        }
    }
    setCurrency(expectedCurr);
}

void CurrencyAccount::setCurrency(CurrencyType currency)
{
    this->currency = currency;
}

CurrencyType CurrencyAccount::getCurrency() const
{
    return currency;
}

std::string CurrencyAccount::getAccountType()
{
    return "Currency";
}
