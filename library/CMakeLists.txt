cmake_minimum_required(VERSION 3.2)
project(Library)

set(SOURCE_FILES
        src/model/Client.cpp
        src/model/ClientType.cpp
        src/model/Address.cpp
        src/model/Default.cpp
        src/model/Gold.cpp
        src/model/Platinum.cpp
        src/model/Silver.cpp
        src/model/Diamond.cpp
        src/model/Bronze.cpp
        src/model/BankAccount.cpp
        src/exceptions/BankAccountException.cpp
        include/exceptions/BankAccountException.h
        src/model/Transaction.cpp
        src/model/Transaction.cpp
        src/exceptions/TransactionException.cpp
        include/predicates/ClientFirstNamePredicate.h
        include/predicates/ClientSurnamePredicate.h
        include/predicates/ClientAccountsPredicate.h
        src/managers/ClientManager.cpp
        include/managers/ClientManager.h
        src/managers/AccountManager.cpp
        include/managers/AccountManager.h
        include/predicates/ClientIdPredicate.h
        include/predicates/ClientPhoneNumberPredicate.h
        src/exceptions/ClientException.cpp
        include/exceptions/ClientException.h
        src/model/CurrencyAccount.cpp
        src/model/JuniorAccount.cpp
        src/model/SavingAccount.cpp
        src/model/StandardAccount.cpp src/managers/TransactionManager.cpp include/managers/TransactionManager.h src/managers/TransactionManager.cpp include/predicates/TypeOfTransactionPredicate.h src/exceptions/AddressException.cpp include/exceptions/AddressException.h)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

#Włacz testy
enable_testing()
#konfiguracja testow
find_package(Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)
# tu w przyszłości będą dodawane pliki źródłowe testów
set(SOURCE_TEST_FILES
        test/master.cpp
        test/ClientTest.cpp
        test/AddressTest.cpp
        test/BankAccountTest.cpp
        test/TransactionTest.cpp
        test/ClientManagerTest.cpp
        test/CurrencyAccountTest.cpp
        test/SavingAccountTest.cpp
        test/RepositoryTest.cpp test/StandardAccountTest.cpp test/AccountManagerTest.cpp test/TransactionManagerTest.cpp)
add_executable (LibraryTest ${SOURCE_TEST_FILES})
#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )
#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})