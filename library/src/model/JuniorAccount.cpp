//
// Created by student on 06.06.23.
//

#include "model/JuniorAccount.h"
#include "exceptions/BankAccountException.h"

using namespace std;

JuniorAccount::JuniorAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, const BankAccountPtr &parentAccountPtr) :
        BankAccount(ptrClient, creationTime), parentAccountPtr(parentAccountPtr)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if (parentAccountPtr == nullptr) throw BankAccountException(BankAccountException::bankAccountNotExistException);
    this->setEndTime(pt::not_a_date_time);
    if (creationTime == pt::not_a_date_time) this->setCreationTime(pt::second_clock::local_time());
    else this->setCreationTime(creationTime);
}

std::string JuniorAccount::getAccountInfo()
{
    return this->getBankAccountInfo() + "\nCreation Time: " + pt::to_simple_string(this->getCreationTime()) + "\nAccount Id: " + boost::uuids::to_string(this->getAccountId()) + "\nAccount Balance: " +
           to_string(this->getAccountBalance()) + "\nClient Info: " + this->getPtrClient()->getClientInfo() + "\n=====\nParent Account:\n" + this->parentAccountPtr->getAccountInfo();
}

std::string JuniorAccount::getBankAccountInfo()
{
    return "Junior Account:";
}

std::string JuniorAccount::getAccountType()
{
    return "Junior";
}
