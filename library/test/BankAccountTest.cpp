//
// Created by Wiktor Stępniewski on 02/06/2023.
//
#include <boost/test/unit_test.hpp>
#include "model/BankAccount.h"
#include "model/Client.h"
#include "model/Default.h"
#include "exceptions/BankAccountException.h"
#include "typedefs.h"

namespace pt = boost::posix_time;

BOOST_AUTO_TEST_SUITE(BankAccountTestSuite)

    AddressPtr testAddres1 = std::make_shared<Address>("Wroclaw", "Szkolna", "3");
    ClientTypePtr testClientType1 = std::make_shared<Default>();
    ClientPtr testClient1 = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", testAddres1, testClientType1);

    BOOST_AUTO_TEST_CASE(BankAccountConstructorPositiveTest)
    {
        BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
        BOOST_TEST(testAccount1->getAccountBalance() == 0);
        BOOST_TEST(testAccount1->isActive());
        BOOST_TEST(testAccount1->getPtrClient() == testClient1);
    }

    BOOST_AUTO_TEST_CASE(BankAccountConstructorNegativeTest)
    {
        BOOST_REQUIRE_THROW(BankAccountPtr testAccount1 = std::make_shared<BankAccount>(nullptr, pt::not_a_date_time), BankAccountException);
    }

    BOOST_AUTO_TEST_CASE(BankAccountSettersTest)
    {
        BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
        testAccount1->setAccountBalance(1500);
        BOOST_TEST(testAccount1->getAccountBalance() == 1500);

    }

BOOST_AUTO_TEST_SUITE_END()
