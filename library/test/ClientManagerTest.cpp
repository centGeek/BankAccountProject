//
// Created by student on 06.06.23.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Client.h"
#include "model/Default.h"
#include "managers/ClientManager.h"
#include "predicates/ClientPhoneNumberPredicate.h"

BOOST_AUTO_TEST_SUITE(ClientManagerTestSuite)
    AddressPtr addressPtr = std::make_shared<Address>("London", "Mazowiecka", "2137");
    ClientManager testClientManager;

    BOOST_AUTO_TEST_CASE(registerClientsTest)
    {
        testClientManager.registerClient("Jan", "Kowalski", "32131", addressPtr, std::make_shared<Default>());
        BOOST_TEST(testClientManager.countRegisteredClients() == 1);
    }

    BOOST_AUTO_TEST_CASE(findAllClientsTest)
    {
        std::vector<ClientPtr> found = testClientManager.findAllClients();
        BOOST_TEST(found[0]->getPhoneNumber() == "32131");
    }

    BOOST_AUTO_TEST_CASE(findClientByPredicateTest)
    {
        ClientPhoneNumberPredicate numberPredicate("32131");
        std::vector<ClientPtr> found = testClientManager.findClientByPredicate(numberPredicate);
        BOOST_TEST(found[0]->getPhoneNumber() == "32131");
    }

    BOOST_AUTO_TEST_CASE(unregisterClientsTest)
    {
        testClientManager.unRegisterClient(testClientManager.findClientByPhoneNumber("32131"));
        BOOST_TEST(testClientManager.countRegisteredClients() == 1);
        BOOST_TEST(testClientManager.findClientByPhoneNumber("32131")->isArchiveStatus());
    }

BOOST_AUTO_TEST_SUITE_END()