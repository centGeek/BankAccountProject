//
// Created by Wiktor Stępniewski on 08/06/2023.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "managers/TransactionManager.h"
#include "model/Client.h"
#include "model/Platinum.h"
#include "managers/AccountManager.h"
#include "model/CurrencyAccount.h"
#include "predicates/ClientAccountsPredicate.h"
#include "exceptions/TransactionException.h"

using namespace std;
namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(TransactionManagerTestSuite)

    TransactionManager testTransactionManager;
    AccountManager testAccountManager;
    AddressPtr ptrAddress = std::make_shared<Address>("London", "Mazowiecka", "2137");
    ClientPtr ptrClient = std::make_shared<Client>("Jan", "Kowalski", "32131", ptrAddress, std::make_shared<Platinum>());
    ClientPtr ptrClient2 = std::make_shared<Client>("Krzysiek", "testLastName", "phoneNumber1", ptrAddress, std::make_shared<Platinum>());
    BankAccountPtr testAccount = testAccountManager.createStandardAccount(ptrClient, boost::posix_time::not_a_date_time);
    BankAccountPtr testAccount2 = testAccountManager.createStandardAccount(ptrClient2, pt::not_a_date_time);

    BankAccountPtr testCurrencyAccount = (testAccountManager.createCurrencyAccount(ptrClient,
                                                                                   boost::posix_time::not_a_date_time,
                                                                                   EUR));
    BankAccountPtr testCurrencyAccount2 = (testAccountManager.createCurrencyAccount(ptrClient2, pt::not_a_date_time,
                                                                                    USD));

    BankAccountPtr testCurrencyAccount3 = (testAccountManager.createCurrencyAccount(ptrClient2, pt::not_a_date_time,
                                                                                    USD));
    BankAccountPtr testCurrencyAccount4 = (testAccountManager.createCurrencyAccount(ptrClient2, pt::not_a_date_time,
                                                                                    USD));

    BOOST_AUTO_TEST_CASE(TransactionManagerDepositMoneyPositiveTest)
    {
        testTransactionManager.depositMoney(testAccount, 500);
        BOOST_TEST(testAccount->getAccountBalance() == 500);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerDepositMoneyNegativeTest)
    {
        BOOST_REQUIRE_THROW(testTransactionManager.depositMoney(testAccount, -500), TransactionException);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerWithdrawMoneyPositiveTest)
    {
        testTransactionManager.withdrawMoney(testAccount, 500);
        BOOST_TEST(testAccount->getAccountBalance() == 0);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerWithdrawMoneyOutOfRangeTest)
    {
        testCurrencyAccount4->setAccountBalance(0);
        BOOST_TEST(testCurrencyAccount4->getAccountBalance() == 0);
        BOOST_REQUIRE_THROW(testTransactionManager.withdrawMoney(testCurrencyAccount4, 500), TransactionException);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerWithdrawNegativeTest)
    {
        BOOST_REQUIRE_THROW(testTransactionManager.withdrawMoney(testAccount, -500), TransactionException);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferPositiveTest)
    {
        testAccount->setAccountBalance(1000);
        testAccount2->setAccountBalance(1000);
        BOOST_TEST(testAccount->getAccountBalance() == 1000);
        BOOST_TEST(testAccount2->getAccountBalance() == 1000);
        BOOST_TEST(testTransactionManager.moneyTransfer(testAccount2, testAccount, 100.5));
        BOOST_TEST(testAccount->getAccountBalance() == 899.5);
        BOOST_TEST(testAccount2->getAccountBalance() == 1100.5);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferNegativeNumberTest)
    {
        BOOST_REQUIRE_THROW(testTransactionManager.moneyTransfer(testAccount2, testAccount, -500), TransactionException);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferOutOfRangeTest)
    {
        testAccount->setAccountBalance(1000);
        testAccount2->setAccountBalance(1000);
        BOOST_TEST(testAccount->getAccountBalance() == 1000);
        BOOST_TEST(testAccount2->getAccountBalance() == 1000);
        BOOST_REQUIRE_THROW(testTransactionManager.moneyTransfer(testAccount2, testAccount, 1500), TransactionException);
    }

    BOOST_AUTO_TEST_CASE(depositMoneyTest)
    {
        testCurrencyAccount->setAccountBalance(100.0);
        testTransactionManager.depositMoney(testCurrencyAccount, 320.0);
        float convertToPLN = 320.0 / 4.17; //kurs PLN to USD
        BOOST_TEST(testCurrencyAccount->getAccountBalance() == (100.0 + convertToPLN), tt::tolerance(0.6));
    }

    BOOST_AUTO_TEST_CASE(WithdrawMoneyTest)
    {
        testCurrencyAccount->setAccountBalance(100);
        testTransactionManager.withdrawMoney(testCurrencyAccount, 50);
        float withdrewMoney = 50.0 / 4.17;
        BOOST_TEST(testCurrencyAccount->getAccountBalance() == (100.0 - withdrewMoney), tt::tolerance(0.6));
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferCurrencyDiferentCurrencyAccountPositiveTest)
    {
        testCurrencyAccount->setAccountBalance(500);
        testCurrencyAccount2->setAccountBalance(500);
        testTransactionManager.moneyTransfer(testCurrencyAccount, testCurrencyAccount2, 500);
        float convertedValue = (500 * 0.24);
        BOOST_TEST(testCurrencyAccount->getAccountBalance() == (500.0 + convertedValue), tt::tolerance(0.6));
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferCurrencySameCurrencyAccountPositiveTest)
    {
        testCurrencyAccount2->setAccountBalance(500);
        testCurrencyAccount3->setAccountBalance(500);
        testTransactionManager.moneyTransfer(testCurrencyAccount3, testCurrencyAccount2, 500);
        float convertedValue = (500 * 0.24);
        BOOST_TEST(testCurrencyAccount3->getAccountBalance() == (500.0 + convertedValue), tt::tolerance(0.6));
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferCurrencyCurrencyAndStandarAccountPositiveTest)
    {
        testCurrencyAccount2->setAccountBalance(500);
        testAccount->setAccountBalance(0);
        testTransactionManager.moneyTransfer(testAccount, testCurrencyAccount2, 500);
        BOOST_TEST(testAccount->getAccountBalance() == 500);
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerMoneyTransferCurrencyStandardAndCurrencyAccountPositiveTest)
    {
        testCurrencyAccount2->setAccountBalance(500);
        testAccount->setAccountBalance(500);
        testTransactionManager.moneyTransfer(testCurrencyAccount2, testAccount, 500);
        float convertedValue = (500 * 0.24);
        BOOST_TEST(testCurrencyAccount2->getAccountBalance() == (500.0 + convertedValue), tt::tolerance(0.6));
    }

    BOOST_AUTO_TEST_CASE(TransactionManagerChangeClientTypeAccordingToDepositTest)
    {
        testAccount->setAccountBalance(0);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Default");
        testTransactionManager.depositMoney(testAccount, 1000);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Bronze");
        testTransactionManager.depositMoney(testAccount, 1000);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Silver");
        testTransactionManager.depositMoney(testAccount, 2000);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Gold");
        testTransactionManager.depositMoney(testAccount, 4000);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Platinum");
        testTransactionManager.depositMoney(testAccount, 8000);
        BOOST_TEST(testAccount->getPtrClient()->getClientType() == "Diamond");
    }


BOOST_AUTO_TEST_SUITE_END()