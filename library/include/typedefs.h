//
// Created by student on 25.05.23.
//

#ifndef PROJECT_TYPEDEFS_H
#define PROJECT_TYPEDEFS_H

#include <memory>
#include <functional>

class Client;

class ClientType;

class Address;

class BankAccount;

class Transaction;

class JuniorAccount;

class CurrencyAccount;

class SavingAccount;

class StandardAccount;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<BankAccount> BankAccountPtr;
typedef std::shared_ptr<JuniorAccount> JuniorAccountPtr;
typedef std::shared_ptr<CurrencyAccount> CurrencyAccountPtr;
typedef std::shared_ptr<SavingAccount> SavingAccountPtr;
typedef std::shared_ptr<StandardAccount> StandardAccountPtr;
typedef std::shared_ptr<Transaction> TransactionPtr;

typedef std::function<bool(BankAccountPtr)> BankAccountPredicate;
typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(TransactionPtr)> TransactionPredicate;

#endif //PROJECT_TYPEDEFS_H
