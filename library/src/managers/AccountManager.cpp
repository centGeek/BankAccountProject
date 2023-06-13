//
// Created by Wiktor Stępniewski on 05/06/2023.
//

#include "managers/AccountManager.h"
#include "model/SavingAccount.h"
#include "model/JuniorAccount.h"
#include "model/StandardAccount.h"
#include "model/CurrencyAccount.h"
#include "exceptions/ClientException.h"
#include "exceptions/BankAccountException.h"

using namespace std;

AccountManager::AccountManager() = default;

AccountManager::~AccountManager() = default;

vector<BankAccountPtr> AccountManager::findAccountsByPredicate(const BankAccountPredicate &predicate) const
{
    vector<BankAccountPtr> found;
    for (auto &account: activeAccounts.findAll())
    {
        if (predicate(account))
            found.push_back(account);
    }
    for (auto &account: inActiveAccounts.findAll())
    {
        if (predicate(account))
            found.push_back(account);
    }
    return found;
}

std::vector<BankAccountPtr> AccountManager::findAllAccounts() const
{
    vector<BankAccountPtr> found = activeAccounts.findAll();
    vector<BankAccountPtr> found2 = inActiveAccounts.findAll();
    found.insert(found.end(), found2.begin(), found2.end());
    return found;
}

BankAccountPtr AccountManager::createCurrencyAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, CurrencyType currency)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if (ptrClient->getMaxActiveAccounts() > ptrClient->getActiveAccounts())
    {
        BankAccountPtr newBankAccount = dynamic_pointer_cast<CurrencyAccount>(make_shared<CurrencyAccount>(ptrClient, creationTime, currency));
        activeAccounts.add(newBankAccount);
        return newBankAccount;
    }
    throw ClientException(ClientException::tooManyActiveAccounts);
}

BankAccountPtr AccountManager::createStandardAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if (ptrClient->getMaxActiveAccounts() > ptrClient->getActiveAccounts())
    {
        BankAccountPtr newBankAccount = make_shared<StandardAccount>(ptrClient, creationTime);
        activeAccounts.add(newBankAccount);
        return newBankAccount;
    }
    throw ClientException(ClientException::tooManyActiveAccounts);
}

BankAccountPtr AccountManager::createJuniorAccount(const ClientPtr &ptrChild, const boost::posix_time::ptime &creationTime, const BankAccountPtr &ptrParentAccount)
{
    if (ptrChild == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if (ptrParentAccount == nullptr) throw BankAccountException(BankAccountException::bankAccountNotExistException);
    if (ptrChild->getMaxActiveAccounts() > ptrChild->getActiveAccounts())
    {
        BankAccountPtr newBankAccount = make_shared<JuniorAccount>(ptrChild, creationTime, ptrParentAccount);
        activeAccounts.add(newBankAccount);
        return newBankAccount;
    }
    throw ClientException(ClientException::tooManyActiveAccounts);
}

BankAccountPtr AccountManager::createSavingAccount(const ClientPtr &ptrClient, const boost::posix_time::ptime &creationTime, const float &interestRate)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    if(interestRate<0) throw BankAccountException(BankAccountException::negativeAmount);
    if (ptrClient->getMaxActiveAccounts() > ptrClient->getActiveAccounts())
    {
        BankAccountPtr newBankAccount = make_shared<SavingAccount>(ptrClient, creationTime, interestRate);
        activeAccounts.add(newBankAccount);
        return newBankAccount;
    }
    throw ClientException(ClientException::tooManyActiveAccounts);
}

void AccountManager::closeAccount(const BankAccountPtr &ptrBankAccount)
{
    if (ptrBankAccount == nullptr) throw BankAccountException(BankAccountException::bankAccountNotExistException);
    ptrBankAccount->closeAccount();
    inActiveAccounts.add(ptrBankAccount);
    activeAccounts.eraseObjectFromRepository(ptrBankAccount);
}

void AccountManager::saveToFileAccounts()
{
    std::string nazwaPliku = "ClientsAccountsRepository.txt";
    std::ofstream plik(nazwaPliku);
    if (!plik)
    {
        std::cerr << "Błąd podczas otwierania pliku " << nazwaPliku << std::endl;
        return;
    }
    for (int i = 0; i < this->activeAccounts.findAll().size(); i++)
    {
        plik << this->activeAccounts.get(i)->getAccountInfo() << std::endl;
        plik << "---------" << std::endl;
    }
    plik.close();
}
