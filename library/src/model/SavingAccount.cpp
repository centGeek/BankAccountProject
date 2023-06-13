//
// Created by student on 06.06.23.
//

#include "model/SavingAccount.h"
#include "exceptions/BankAccountException.h"

namespace pt = boost::posix_time;
using namespace std;

SavingAccount::SavingAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime,
                             float interestRate) : BankAccount(ptrClient, creationTime), interestRate(interestRate)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    this->setEndTime(pt::not_a_date_time);
    this->setAccountBalance(0);
    if (creationTime == pt::not_a_date_time) this->setCreationTime(pt::second_clock::local_time());
    else this->setCreationTime(creationTime);
}

double SavingAccount::monthEvaluation()
{
    boost::posix_time::time_duration diff = pt::second_clock::local_time() - getCreationTime();
    int amountOfInterests = diff.hours() / 720;
    for (int i = 0; i < amountOfInterests; i++)
    {
        setAccountBalance(getAccountBalance() * 2.3 * 0.81 / 12 / 100 + getAccountBalance());
    }
    return this->getAccountBalance();

}
std::string SavingAccount::getAccountInfo(){
    return  this->getBankAccountInfo()+"\nCreation Time: " + pt::to_simple_string(this->getCreationTime()) + "\nAccount Id: " + boost::uuids::to_string(this->getAccountId()) + "\nAccount Balance: " +
            to_string(this->getAccountBalance()) + "\nClient Info: " + this->getPtrClient()->getClientInfo();
}
std::string SavingAccount::getBankAccountInfo()
{
    return "Saving account:\ninterest rate: " + std::to_string(this->interestRate);
}

void SavingAccount::setInterestRate(float interestRate)
{
    if(interestRate<0) throw BankAccountException(BankAccountException::negativeAmount);
    this->interestRate = interestRate;
}

float SavingAccount::getInterestRate() const
{
    return interestRate;
}

std::string SavingAccount::getAccountType()
{
    return "Saving";
}
