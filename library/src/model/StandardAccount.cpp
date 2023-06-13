//
// Created by student on 06.06.23.
//

#include "model/StandardAccount.h"
#include "exceptions/BankAccountException.h"

using namespace std;

StandardAccount::StandardAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime)
        : BankAccount(ptrClient, creationTime)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    this->setEndTime(pt::not_a_date_time);
    this->setAccountBalance(0);
    this->debit = 0;
    if (creationTime == pt::not_a_date_time) this->setCreationTime(pt::second_clock::local_time());
    else this->setCreationTime(creationTime);
}

void StandardAccount::payOffDebit(double value)
{
    if(value<0)throw BankAccountException(BankAccountException::negativeAmount);
    if (-value >= this->debit)
        this->debit = debit + value;
    else
    {
        this->setAccountBalance(value + debit);
        this->debit = 0;
    }
}

std::string StandardAccount::getAccountInfo()
{
    return this->getBankAccountInfo() + "\nCreation Time: " + pt::to_simple_string(this->getCreationTime()) + "\nAccount Id: " + boost::uuids::to_string(this->getAccountId()) + "\nAccount Balance: " +
           to_string(this->getAccountBalance()) + "\nClient Info: " + this->getPtrClient()->getClientInfo();
}

std::string StandardAccount::getBankAccountInfo() const
{
    return "Standard Account: \nDebit: " + to_string(this->getDebit());
}

double StandardAccount::getDebit() const
{
    return debit;
}

void StandardAccount::setDebit(double debit)
{
    if(debit>0) throw BankAccountException(BankAccountException::positiveDebit);
    this->debit = debit;
}

std::string StandardAccount::getAccountType()
{
    return "Standard";
}