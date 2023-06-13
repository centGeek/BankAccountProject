//
// Created by student on 03.06.23.
//

#include <boost/test/unit_test.hpp>
#include "model/BankAccount.h"
#include "model/Client.h"
#include "model/Default.h"
#include "model/Transaction.h"

namespace pt = boost::posix_time;

BOOST_AUTO_TEST_SUITE(TransactionSuiteTest)

    AddressPtr testAddres1 = std::make_shared<Address>("Wroclaw", "Szkolna", "3");
    ClientTypePtr testClientType1 = std::make_shared<Default>();
    ClientPtr testClient1 = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", testAddres1, testClientType1);
    ClientPtr testClient2 = std::make_shared<Client>("Krzysiek", "testLastName", "phoneNumber1", testAddres1, testClientType1);
    BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
    BankAccountPtr testAccount2 = std::make_shared<BankAccount>(testClient2, pt::not_a_date_time);


    BOOST_AUTO_TEST_CASE(MoneyTransferTest)
    {
        BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
        BankAccountPtr testAccount2 = std::make_shared<BankAccount>(testClient2, pt::not_a_date_time);
        testAccount1->setAccountBalance(1000);
        testAccount2->setAccountBalance(1001);
        TransactionPtr testTransaction1 = std::make_shared<Transaction>(testAccount1, testAccount2, 1000);
        BOOST_TEST(testTransaction1->moneyTransfer(testAccount1, testAccount2, 1000));
        BOOST_TEST(testAccount1->getAccountBalance() == 0);
        BOOST_TEST(testAccount2->getAccountBalance() == 2001);
        try
        {
            testTransaction1->moneyTransfer(testAccount1, testAccount2, 1);
        } catch (const std::exception &e)
        {
            BOOST_CHECK_EQUAL(e.what(), "You cannot withdraw this amount of money, because your account balance has insufficient funds");
        }

    }

    BOOST_AUTO_TEST_CASE(DepositMoneyTest)
    {
        BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
        TransactionPtr testTransaction1 = std::make_shared<Transaction>(testAccount1, 0);
        try
        {
            testTransaction1->depositMoney(testAccount1, -1);
        } catch (const std::exception &e)
        {
            BOOST_CHECK_EQUAL(e.what(), "Transfer funds cannot be lower or equal 0");
        }
    }

    BOOST_AUTO_TEST_CASE(WithdrawMoneyTest)
    {
        BankAccountPtr testAccount1 = std::make_shared<BankAccount>(testClient1, pt::not_a_date_time);
        TransactionPtr testTransaction1 = std::make_shared<Transaction>(testAccount1, 0);
        testAccount1->setAccountBalance(2123);
        testTransaction1->withdrawMoney(testAccount1, 2100);
        BOOST_TEST(testAccount1->getAccountBalance() == 23);
        try
        {
            testTransaction1->withdrawMoney(testAccount1, 23);
        } catch (const std::exception &e)
        {
            BOOST_CHECK_EQUAL(e.what(), "You cannot withdraw this amount of money, because your account balance has insufficient funds");
        }
        try
        {
            testTransaction1->withdrawMoney(testAccount1, -1);
        } catch (const std::exception &e)
        {
            BOOST_CHECK_EQUAL(e.what(), "Transfer funds cannot be lower or equal 0");
        }
    }

BOOST_AUTO_TEST_SUITE_END()

