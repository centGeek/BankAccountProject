//
// Created by student on 08.06.23.
//

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/StandardAccount.h"
#include "model/Default.h"

namespace tt = boost::test_tools;
namespace pt = boost::posix_time;
BOOST_AUTO_TEST_SUITE(StandardAccountTestSuite)
    AddressPtr address = std::make_shared<Address>("Wroclaw", "Szkolna", "3");
    ClientTypePtr clientTypePtr = std::make_shared<Default>();
    ClientPtr clientPtr = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", address, clientTypePtr);
    StandardAccountPtr standardAccount = std::make_shared<StandardAccount>(clientPtr, pt::second_clock::local_time());

    BOOST_AUTO_TEST_CASE(payOffDebitTest)
    {
        standardAccount->setDebit(-4000);
        standardAccount->payOffDebit(2000);
        BOOST_TEST(standardAccount->getDebit(), -2000);

        standardAccount->payOffDebit(3500);
        BOOST_TEST(standardAccount->getDebit() == 0);
        BOOST_TEST(standardAccount->getAccountBalance(), 1500);
    }


BOOST_AUTO_TEST_SUITE_END()
