//
// Created by Wiktor Stępniewski on 08/06/2023.
//

#include "managers/TransactionManager.h"
#include "model/CurrencyAccount.h"
#include "model/StandardAccount.h"
#include <vector>
#include "predicates/TypeOfTransactionPredicate.h"
#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"
#include "exceptions/ClientException.h"
#include "exceptions/TransactionException.h"
#include "exceptions/BankAccountException.h"

using namespace std;

TransactionManager::TransactionManager() = default;

TransactionManager::~TransactionManager() = default;

std::vector<TransactionPtr> TransactionManager::findAllTransactions()
{
    vector<TransactionPtr> found = transactions.findAll();
    return found;
}

std::vector<TransactionPtr> TransactionManager::findTransactionsByPredicate(const TransactionPredicate &predicate)
{
    vector<TransactionPtr> found;
    for (auto &transaction: transactions.findAll())
    {
        if (predicate(transaction))
            found.push_back(transaction);
    }
    return found;
}

bool TransactionManager::moneyTransfer(const BankAccountPtr &destinationAcc, const BankAccountPtr &sourceAcc, const double &value)
{
    if (sourceAcc == nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if (destinationAcc == nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if (value <= 0) throw TransactionException(TransactionException::outOfRangeException);
    if (destinationAcc->getAccountType() == "Currency" || sourceAcc->getAccountType() == "Currency")
    {
        CurrencyAccountPtr givenDestinationAccount;
        CurrencyAccountPtr givenSourceAccount;
        if (destinationAcc->getAccountType() == "Currency")
            givenDestinationAccount = dynamic_pointer_cast<CurrencyAccount>(destinationAcc);

        if (sourceAcc->getAccountType() == "Currency")
            givenSourceAccount = dynamic_pointer_cast<CurrencyAccount>(sourceAcc);


        TransactionPtr transaction = std::make_shared<Transaction>(destinationAcc, sourceAcc, value);

        if (destinationAcc->getAccountType() == "Currency" && sourceAcc->getAccountType() == "Currency")
        {
            if (transaction->moneyTransferCurrencyAccount(givenSourceAccount, givenDestinationAccount, value))
            {
                transactions.add(transaction);
                return true;
            }
        }
        if (destinationAcc->getAccountType() == "Currency" && sourceAcc->getAccountType() != "Currency")
        {
            if (transaction->moneyTransferCurrencyAccount(sourceAcc, givenDestinationAccount, value))
            {
                transactions.add(transaction);
                return true;
            }
        }

        if (destinationAcc->getAccountType() != "Currency" && sourceAcc->getAccountType() == "Currency")
        {
            if (transaction->moneyTransferCurrencyAccount(givenSourceAccount, destinationAcc, value))
            {
                transactions.add(transaction);
                return true;
            }
        }

    } else
    {
        TransactionPtr transaction = std::make_shared<Transaction>(sourceAcc, destinationAcc, value);
        if (transaction->moneyTransfer(sourceAcc, destinationAcc, value))
        {
            transactions.add(transaction);
            return true;
        }
    }
    return false;
}

bool TransactionManager::depositMoney(const BankAccountPtr &account, double amount)
{
    if (account == nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if (amount <= 0) throw TransactionException(TransactionException::outOfRangeException);
    if (account->getAccountType() == "Currency")
    {
        CurrencyAccountPtr givenAccount = dynamic_pointer_cast<CurrencyAccount>(account);
        TransactionPtr transaction = std::make_shared<Transaction>(account, amount);
        if (transaction->depositMoneyCurrencyAccount(givenAccount, amount))
        {
            transactions.add(transaction);
            this->changeClientType(account->getPtrClient());
            return true;
        }
    } else
    {
        TransactionPtr transaction = std::make_shared<Transaction>(account, amount);
        if (transaction->depositMoney(account, amount))
        {
            transactions.add(transaction);
            this->changeClientType(account->getPtrClient());
            return true;
        }
    }
    return false;
}

bool TransactionManager::withdrawMoney(const BankAccountPtr &account, double amount)
{
    if (account == nullptr) throw TransactionException(TransactionException::nullBankAcountPointer);
    if (amount <= 0) throw TransactionException(TransactionException::outOfRangeException);
    if (account->getAccountType() == "Currency")
    {
        CurrencyAccountPtr givenAccount = dynamic_pointer_cast<CurrencyAccount>(account);
        TransactionPtr transaction = std::make_shared<Transaction>(account, amount);
        if (transaction->withdrawMoneyCurrencyAccount(givenAccount, amount))
        {
            transactions.add(transaction);
            return true;
        }
    } else if (account->getAccountType() == "Standard")
    {
        StandardAccountPtr givenAccount = dynamic_pointer_cast<StandardAccount>(account);
        TransactionPtr transaction = std::make_shared<Transaction>(account, amount);
        if (transaction->withdrawMoney(givenAccount, amount))
        {
            transactions.add(transaction);
            return true;
        }
    } else
    {
        TransactionPtr transaction = std::make_shared<Transaction>(account, amount);
        if (transaction->withdrawMoney(account, amount))
        {
            transactions.add(transaction);
            return true;
        }
    }
    return false;
}

double TransactionManager::countClientDeposit(const ClientPtr &ptrClient)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    TypeOfTransactionPredicate depositType("deposit");
    vector<TransactionPtr> found = this->findTransactionsByPredicate(depositType);
    double depositSum = 0;
    for (const auto &i: found)
    {
        if (i->getSourceAccount()->getPtrClient() == ptrClient)
            depositSum += i->getTransactionValue();
    }
    return depositSum;
}

void TransactionManager::changeClientType(const ClientPtr &ptrClient)
{
    if (ptrClient == nullptr) throw BankAccountException(BankAccountException::clientNotExistException);
    double depositSum = this->countClientDeposit(ptrClient);
    if (depositSum < 1000)
    {
        ptrClient->setClientTypePtr(make_shared<Default>());
        return;
    }
    if (depositSum < 2000)
    {
        ptrClient->setClientTypePtr(make_shared<Bronze>());
        return;
    }
    if (depositSum < 4000)
    {
        ptrClient->setClientTypePtr(make_shared<Silver>());
        return;
    }
    if (depositSum < 8000)
    {
        ptrClient->setClientTypePtr(make_shared<Gold>());
        return;
    }
    if (depositSum < 16000)
    {
        ptrClient->setClientTypePtr(make_shared<Platinum>());
        return;
    }
    if (depositSum > 16000)
    {
        ptrClient->setClientTypePtr(make_shared<Diamond>());
        return;
    }
}

void TransactionManager::saveToFileTransactions()
{
    std::string nazwaPliku = "TransactionsRepository.txt";
    std::ofstream plik(nazwaPliku);
    if (!plik)
    {
        std::cerr << "Błąd podczas otwierania pliku " << nazwaPliku << std::endl;
        return;
    }
    for (int i = 0; i < this->transactions.findAll().size(); i++)
    {
        plik << this->transactions.get(i)->getTransactionInfo() << std::endl;
        plik << "---------" << std::endl;
    }
    plik.close();
}


