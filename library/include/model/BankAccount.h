//
// Created by Wiktor Stępniewski on 29/05/2023.
//

#ifndef CARRENTAL_BANKACCOUNT_H
#define CARRENTAL_BANKACCOUNT_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include "Client.h"
#include "typedefs.h"
#include "Transaction.h"

namespace pt = boost::posix_time;

class BankAccount
{
    boost::uuids::uuid accountId;
    double accountBalance;
    ClientPtr ptrClient;
    bool isActived;
    boost::posix_time::ptime creationTime;
    boost::posix_time::ptime endTime;

public:
    BankAccount(const ClientPtr &ptrClient, boost::posix_time::ptime creationTime);

    virtual ~BankAccount();

    virtual std::string getAccountInfo();

    ClientPtr getPtrClient() const;

    boost::uuids::uuid getAccountId() const;

    double getAccountBalance() const;

    bool isActive() const;

    boost::posix_time::ptime getCreationTime() const;

    boost::posix_time::ptime getEndTime() const;

    void closeAccount();

    void setCreationTime(const boost::posix_time::ptime &creationTime);

    void setAccountBalance(double accountBalance);

    void setEndTime(boost::posix_time::ptime endTime);

    void setIsActive(bool);

    virtual std::string getAccountType();

};

#endif // CARRENTAL_BANKACCOUNT_H
