//
// Created by Wiktor Stępniewski on 04/06/2023.
//

#ifndef CARRENTAL_CLIENTMANAGER_H
#define CARRENTAL_CLIENTMANAGER_H

#include "model/Client.h"
#include "repositories/Repository.h"
#include "typedefs.h"

class ClientManager
{
    Repository<Client> clients;
public:
    ClientManager();

    ~ClientManager();

    std::vector<ClientPtr> findClientByPredicate(const ClientPredicate &predicate) const;

    std::vector<ClientPtr> findAllClients() const;

    ClientPtr findClientByPhoneNumber(const std::string &phoneNumber);

    ClientPtr registerClient(const std::string &firstName, const std::string &surname, const std::string &phoneNumber, const AddressPtr &adres, const ClientTypePtr &clientType);

    void unRegisterClient(const ClientPtr &);

    int countRegisteredClients();

    void saveToFileClients();


};


#endif //CARRENTAL_CLIENTMANAGER_H
