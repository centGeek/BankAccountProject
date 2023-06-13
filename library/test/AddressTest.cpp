//
// Created by student on 25.05.23.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Address.h"

BOOST_AUTO_TEST_SUITE(AddressTestSuite)

    BOOST_AUTO_TEST_CASE(AddressGetInfoPositiveTest)
    {
        const std::string testFirstName = "Jon";
        const std::string testLastName = "Arbuckle";
        const std::string phoneNumber = "0123456789";
        AddressPtr testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        AddressPtr testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        BOOST_TEST("Street: Accacia Avenue | Street's number: 22 | City: London" == testaddress1->getAddressInfo());
    }

BOOST_AUTO_TEST_SUITE_END()
