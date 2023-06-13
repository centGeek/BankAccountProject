//
// Created by Wiktor Stępniewski on 08/06/2023.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Client.h"
#include "model/Default.h"
#include "managers/AccountManager.h"
#include "exceptions/BankAccountException.h"
#include "predicates/ClientAccountsPredicate.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(AccountManagerTestSuite)
    AccountManager testAccountManager;
    AddressPtr ptrAddress = std::make_shared<Address>("London", "Mazowiecka", "2137");
    ClientPtr ptrClient = std::make_shared<Client>("Jan", "Kowalski", "32131", ptrAddress, std::make_shared<Default>());
    ClientPtr ptrJuniorClient = std::make_shared<Client>("Jas", "Kowalski", "2137", ptrAddress,
                                                         std::make_shared<Default>());


    BOOST_AUTO_TEST_CASE(AccountManagerCreatingStandardAccountTest)
    {
        testAccountManager.createStandardAccount(ptrClient, boost::posix_time::not_a_date_time);
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BOOST_TEST(found.size() == 1);
    }

    BOOST_AUTO_TEST_CASE(AccountManagerCreatingSavingAccountTest)
    {
        testAccountManager.createSavingAccount(ptrClient, boost::posix_time::not_a_date_time, 0.2);
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BOOST_TEST(found.size() == 2);
    }

    BOOST_AUTO_TEST_CASE(AccountManagerCreatingCurrencyAccountTest)
    {
        testAccountManager.createCurrencyAccount(ptrClient, boost::posix_time::not_a_date_time, USD);
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BOOST_TEST(found.size() == 3);
    }

    BOOST_AUTO_TEST_CASE(AccountManagerCreatingJuniorAccountTest)
    {
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BankAccountPtr ptrParentAccount = found[0];
        testAccountManager.createJuniorAccount(ptrJuniorClient, boost::posix_time::not_a_date_time, ptrParentAccount);
        found = testAccountManager.findAllAccounts();
        BOOST_TEST(found.size() == 4);
    }

    BOOST_AUTO_TEST_CASE(AccountManagerClosingAccountPositiveAccountBalanceTest)
    {
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BankAccountPtr testAccount = found[0];
        testAccount->setAccountBalance(250.52532);
        BOOST_REQUIRE_THROW(testAccountManager.closeAccount(testAccount), BankAccountException);
    }

    BOOST_AUTO_TEST_CASE(AccountManagerClosingAccountPositiveTest)
    {
        vector<BankAccountPtr> found = testAccountManager.findAllAccounts();
        BankAccountPtr testAccount = found[1];
        testAccountManager.closeAccount(testAccount);
        BOOST_TEST(!testAccount->isActive());
    }

    BOOST_AUTO_TEST_CASE(AccountManagerFindAccountsByPredicateTest)
    {
        ClientAccountPredicate accountPredicate("32131");
        vector<BankAccountPtr> found = testAccountManager.findAccountsByPredicate(accountPredicate);
        BOOST_TEST(found.size() == 3);
    }

BOOST_AUTO_TEST_SUITE_END()