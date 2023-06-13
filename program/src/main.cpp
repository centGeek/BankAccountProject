//
// Created by student on 25.05.23.
//
#include <iostream>
#include "model/Client.h"
#include "model/Default.h"
#include "model/Bronze.h"
#include "model/BankAccount.h"
#include "managers/ClientManager.h"
#include "predicates/ClientPhoneNumberPredicate.h"
#include "model/CurrencyAccount.h"
#include "model/SavingAccount.h"
#include "repositories/Repository.h"
#include "managers/TransactionManager.h"
#include "managers/AccountManager.h"
#include "predicates/TypeOfTransactionPredicate.h"
#include "model/StandardAccount.h"


using namespace std;

namespace pt = boost::posix_time;

int main()
{
    AccountManager MenadzerKontBankowych;
    TransactionManager MenadzerTransakcji;
    ClientManager MenadzerKlientow;

    AddressPtr testAddress1 = make_shared<Address>("Warszawa", "Mazowiecka", "1");
    AddressPtr testAddress2 = make_shared<Address>("Lodz", "Pomorska", "2");
    AddressPtr testAddress3 = make_shared<Address>("Krakow", "Wodna", "3");
    AddressPtr testAddress4 = make_shared<Address>("Szczecin", "Lipowa", "4");

    ClientPtr testClient1 = MenadzerKlientow.registerClient("John", "White", "123456789", testAddress1,
                                                            std::make_shared<Default>());
    ClientPtr testClient2 = MenadzerKlientow.registerClient("Cassidy", "Nicholson", "987654321", testAddress2,
                                                            std::make_shared<Default>());
    ClientPtr testClient3 = MenadzerKlientow.registerClient("Daniel", "Schroeder", "321654987", testAddress3,
                                                            std::make_shared<Default>());
    ClientPtr testClient4 = MenadzerKlientow.registerClient("Frank", "Hess", "023789456", testAddress4,
                                                            std::make_shared<Default>());

    BankAccountPtr testAccount1 = MenadzerKontBankowych.createStandardAccount(testClient1, pt::not_a_date_time);
    BankAccountPtr testAccount2 = MenadzerKontBankowych.createCurrencyAccount(testClient2, pt::not_a_date_time, USD);
    BankAccountPtr testAccount3 = MenadzerKontBankowych.createSavingAccount(testClient3, pt::not_a_date_time, 0.2);
    BankAccountPtr testAccount4 = MenadzerKontBankowych.createJuniorAccount(testClient4, pt::not_a_date_time, testAccount3);
//==============================================
    cout << endl << "*****Prezentacja Wplaty*****" << endl;
    if (MenadzerTransakcji.depositMoney(testAccount1, 2500))
        cout << endl << "Wplacono 2500 na konto testAccount1";
    if (MenadzerTransakcji.depositMoney(testAccount2, 2500))
        cout << endl << "Wplacono 2500 na konto testAccount2";
    if (MenadzerTransakcji.depositMoney(testAccount3, 2500))
        cout << endl << "Wplacono 2500 na konto testAccount3";
    if (MenadzerTransakcji.depositMoney(testAccount4, 2500))
        cout << endl << "Wplacono 2500 na konto testAccount4" << endl;
//==============================================
    cout << endl << "*****Prezentacja wyplaty*****" << endl;
    if (MenadzerTransakcji.withdrawMoney(testAccount1, 500))
        cout << endl << "Wyplacono 500 z konta testAccount1";
    if (MenadzerTransakcji.withdrawMoney(testAccount2, 500))
        cout << endl << "Wyplacono 500 z konta testAccount2";
    if (MenadzerTransakcji.withdrawMoney(testAccount3, 500))
        cout << endl << "Wyplacono 500 z konta testAccount3";
    if (MenadzerTransakcji.withdrawMoney(testAccount4, 500))
        cout << endl << "Wyplacono 500 z konta testAccount4";
//==============================================
    cout << endl << "*****Spis Kont*****" << endl;
    cout << testAccount1->getAccountInfo() << endl;
    cout << "***************" << endl;
    cout << testAccount2->getAccountInfo() << endl;
    cout << "***************" << endl;
    cout << testAccount3->getAccountInfo() << endl;
    cout << "***************" << endl;
    cout << testAccount4->getAccountInfo() << endl;
//==============================================
    cout << endl << "*****Prezentacja Przelewow*****" << endl;
    cout << "Balans konta testAccount1 (Standard Account) przed przelewem: " << testAccount1->getAccountBalance()
         << endl;
    cout << "Balans konta testAccount2 (Currency Account) przed przelewem: " << testAccount2->getAccountBalance()
         << endl;
    if (MenadzerTransakcji.moneyTransfer(testAccount2, testAccount1, 500))
        cout << "Wykonano przelew z konta testAccout1 na konto testAccount2 na kwote 500 PLN" << endl;
    cout << "Balans konta testAccount1 (Standard Account) po przelewie: " << testAccount1->getAccountBalance() << endl;
    cout << "Balans konta testAccount2 (Currency Account) po przelewie: " << testAccount2->getAccountBalance() << endl;
    cout << "-----------" << endl;
    cout << "Balans konta testAccount3 (Saving Account) przed przelewem: " << testAccount3->getAccountBalance() << endl;
    cout << "Balans konta testAccount4 (JuniorAccount) przed przelewem: " << testAccount4->getAccountBalance() << endl;
    if (MenadzerTransakcji.moneyTransfer(testAccount4, testAccount3, 500))
        cout << "Wykonano przelew z konta testAccount1 na konto testAccount2 na kwote 500 PLN" << endl;
    cout << "Balans konta testAccount3 (Saving Account) po przelewie: " << testAccount3->getAccountBalance() << endl;
    cout << "Balans konta testAccount4 (JuniorAccount) po przelewie: " << testAccount4->getAccountBalance() << endl;
//==============================================
//Zapis repozytoriów do plików .txt
    MenadzerTransakcji.saveToFileTransactions();
    MenadzerKontBankowych.saveToFileAccounts();
    MenadzerKlientow.saveToFileClients();

}
