//
// Created by Wiktor Stępniewski on 29/05/2023.
//

#include "model/BankAccount.h"
#include "exceptions/BankAccountException.h"
#include <string>

using namespace std;

BankAccount::BankAccount(const ClientPtr &ptrClient, pt::ptime creationTime = pt::not_a_date_time) : ptrClient(ptrClient), creationTime(creationTime)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if (creationTime == pt::not_a_date_time) this->creationTime = pt::second_clock::local_time();
    else this->creationTime = creationTime;
    this->setAccountBalance(0);
    this->isActived = true;
    this->endTime = pt::not_a_date_time;
    this->accountId = boost::uuids::random_generator()();
}

BankAccount::~BankAccount() = default;

//gettery
ClientPtr BankAccount::getPtrClient() const
{
    return ptrClient;
}

boost::uuids::uuid BankAccount::getAccountId() const
{
    return this->accountId;
}

double BankAccount::getAccountBalance() const
{
    return this->accountBalance;
}

bool BankAccount::isActive() const
{
    return this->isActived;
}

boost::posix_time::ptime BankAccount::getCreationTime() const
{
    return this->creationTime;
}

boost::posix_time::ptime BankAccount::getEndTime() const
{
    return this->endTime;
}


string BankAccount::getAccountInfo()
{
    return "Creation Time: " + pt::to_simple_string(this->getCreationTime()) + "\nAccount Id: " + boost::uuids::to_string(this->getAccountId()) + "\nAccount Balance: " +
           to_string(this->accountBalance) + "\nClient Info: " + this->getPtrClient()->getClientInfo();
}

void BankAccount::closeAccount()
{
    if (this->getAccountBalance() != 0) throw BankAccountException(BankAccountException::positiveAccountBalance);
    this->isActived = false;
    this->endTime = pt::second_clock::local_time();
}

void BankAccount::setAccountBalance(double accountBalance)
{
    if(accountBalance<0) throw BankAccountException(BankAccountException::negativeAmount);
    this->accountBalance = accountBalance;
}

void BankAccount::setIsActive(bool status)
{
    this->isActived = status;
}

void BankAccount::setEndTime(boost::posix_time::ptime endTime)
{
    this->endTime = endTime;
}

void BankAccount::setCreationTime(const boost::posix_time::ptime &creationTime)
{
    this->creationTime = creationTime;
}

std::string BankAccount::getAccountType()
{
    return "Standard";
}
