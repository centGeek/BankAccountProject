//
// Created by student on 07.06.23.

#include <boost/test/unit_test.hpp>
#include <model/CurrencyAccount.h>
#include <model/StandardAccount.h>
#include "typedefs.h"
#include "model/Default.h"

namespace tt = boost::test_tools;
BOOST_AUTO_TEST_SUITE(CurrencyAccountTestSuite)
    AddressPtr testAddres1 = std::make_shared<Address>("Wroclaw", "Szkolna", "3");
    ClientTypePtr testClientType1 = std::make_shared<Default>();
    ClientPtr testClient1 = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", testAddres1,
                                                     testClientType1);

    CurrencyAccountPtr currencyAccount = std::make_shared<CurrencyAccount>(testClient1, pt::not_a_date_time, USD);

    BOOST_AUTO_TEST_CASE(convertingCurrencyTest)
    {
        currencyAccount->setAccountBalance(100);
        currencyAccount->convertingCurrency(currencyAccount->getCurrency(), CHF);
        BOOST_TEST(currencyAccount->getAccountBalance() == 100 * 0.91, tt::tolerance(0.00001));
        currencyAccount->convertingCurrency(currencyAccount->getCurrency(), USD);
        BOOST_TEST(currencyAccount->getAccountBalance() == 91 * 1.1, tt::tolerance(0.00001));
    }

BOOST_AUTO_TEST_SUITE_END()
