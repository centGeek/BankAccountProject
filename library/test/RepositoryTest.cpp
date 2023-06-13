//
// Created by Wiktor Stępniewski on 08/06/2023.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "repositories/Repository.h"
#include "model/Gold.h"
#include "model/Client.h"
#include "predicates/ClientPhoneNumberPredicate.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ClientRepositoryTestSuite)
    Repository<Client> testRepository1;
    AddressPtr testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
    AddressPtr testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
    ClientPtr testclient1 = std::make_shared<Client>("John", "Blow", "1", testaddress1, make_shared<Gold>());
    ClientPtr testclient2 = std::make_shared<Client>("Patric", "Jones", "2", testaddress2, make_shared<Gold>());

    BOOST_AUTO_TEST_CASE(ClientRepositoryAddPositiveTest)
    {
        testRepository1.add(testclient1);
        testRepository1.add(testclient2);
        BOOST_TEST(testRepository1.size() == 2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryAddNegativeTest)
    {
        testRepository1.add(nullptr);
        BOOST_TEST(testRepository1.size() == 2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryEraseNegativeTest)
    {
        testRepository1.eraseObjectFromRepository(nullptr);
        BOOST_TEST(testRepository1.size() == 2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryErasePositiveTest)
    {
        testRepository1.eraseObjectFromRepository(testclient1);
        BOOST_TEST(testRepository1.size() == 1);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryFindAllTest)
    {
        vector<ClientPtr> FoundClients = testRepository1.findAll();
        testRepository1.eraseObjectFromRepository(testclient1);
        BOOST_TEST(FoundClients.size() == 1);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryGetTest)
    {
        BOOST_TEST(testRepository1.get(0) == testclient2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryFindyByTest)
    {
        ClientPhoneNumberPredicate numberPredicate("2");
        vector<ClientPtr> found = testRepository1.findBy(numberPredicate);
        BOOST_TEST(found[0] == testclient2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryFindIndividualByPredicateTest)
    {
        ClientPhoneNumberPredicate numberPredicate("2");
        ClientPtr found = testRepository1.findIndividualByPredicate(numberPredicate);
        BOOST_TEST(found == testclient2);
    }


BOOST_AUTO_TEST_SUITE_END()