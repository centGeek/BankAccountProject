//
// Created by student on 25.05.23.
//
#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Default.h"
#include "model/Default.h"
#include "model/Diamond.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"

class Address;

BOOST_AUTO_TEST_SUITE(ClientTestSuite)

    BOOST_AUTO_TEST_CASE(ClientGetterSetterTest)
    {
        const std::string testFirstName = "Jon";
        const std::string testLastName = "Arbuckle";
        const std::string phoneNumber = "0123456789";
        AddressPtr testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        AddressPtr testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        ClientTypePtr testClientType = std::make_shared<Default>();
        Client c(testFirstName, testLastName, phoneNumber, testaddress1, testClientType);
        BOOST_TEST(testFirstName == c.getName());
        BOOST_TEST(testLastName == c.getSurname());
        BOOST_TEST(phoneNumber == c.getPhoneNumber());
        BOOST_TEST(c.isArchiveStatus() == false);
    }

    BOOST_AUTO_TEST_CASE(getMaxActiveAccountsTestForAll)
    {
        AddressPtr address = std::make_shared<Address>("Wroclaw", "Szkolna", "3");
        ClientTypePtr clientTypePtr = std::make_shared<Default>();
        ClientPtr clientPtr = std::make_shared<Client>("Jan", "testLastName", "phoneNumber", address, clientTypePtr);
        BOOST_TEST("Jan" == clientPtr->getName());
        BOOST_TEST(clientTypePtr->getMaxActiveAccounts() == 1);
        clientPtr->setClientTypePtr(std::make_shared<Bronze>());
        BOOST_TEST(clientPtr->getMaxActiveAccounts() == 2);
        clientPtr->setClientTypePtr(std::make_shared<Silver>());
        BOOST_TEST(clientPtr->getMaxActiveAccounts() == 3);
        clientPtr->setClientTypePtr(std::make_shared<Gold>());
        BOOST_TEST(clientPtr->getMaxActiveAccounts() == 4);
        clientPtr->setClientTypePtr(std::make_shared<Diamond>());
        BOOST_TEST(clientPtr->getMaxActiveAccounts() == 5);
        clientPtr->setClientTypePtr(std::make_shared<Platinum>());
        BOOST_TEST(clientPtr->getMaxActiveAccounts() == 6);
    }

BOOST_AUTO_TEST_SUITE_END()