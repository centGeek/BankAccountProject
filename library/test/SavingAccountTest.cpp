//
// Created by student on 07.06.23.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/SavingAccount.h"
#include "model/Default.h"
namespace tt = boost::test_tools;
namespace pt = boost::posix_time;
BOOST_AUTO_TEST_SUITE(SavingAccountTestSuite)
    AddressPtr address = std::make_shared<Address>("Wroclaw", "Szkolna","3");
    ClientTypePtr clientTypePtr = std::make_shared<Default>();
    ClientPtr clientPtr = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", address, clientTypePtr);
    pt::ptime creatingTime;


    BOOST_AUTO_TEST_CASE(monthEvaulation) {
        SavingAccountPtr savingAccountPtr1 = std::make_shared<SavingAccount> (clientPtr,pt::second_clock::local_time(), 2.3);
        savingAccountPtr1->setCreationTime(savingAccountPtr1->getCreationTime()- pt::hours(1440) + pt::minutes(0));
        pt::ptime localTime  = savingAccountPtr1->getCreationTime()+pt::hours(720);
        savingAccountPtr1->setAccountBalance(30);
        savingAccountPtr1->monthEvaluation();
        double firstCapitalization = 30 + 30*2.3*0.81/12.0/100;
        double secondCapitalization = firstCapitalization + 2.3 * 0.81 /12.0/100 * firstCapitalization;
        BOOST_TEST(savingAccountPtr1->getAccountBalance() == secondCapitalization, tt::tolerance(0.0000001));

        SavingAccountPtr savingAccountPtr2 = std::make_shared<SavingAccount> (clientPtr,pt::second_clock::local_time(), 2.3);
        savingAccountPtr2->setCreationTime(savingAccountPtr2->getCreationTime() - pt::hours(1000) + pt::minutes(32));
        savingAccountPtr2->setAccountBalance(30);
        savingAccountPtr2->monthEvaluation();
        BOOST_TEST(savingAccountPtr2->getAccountBalance() == firstCapitalization, tt::tolerance(0.0000001));
    }


BOOST_AUTO_TEST_SUITE_END()
