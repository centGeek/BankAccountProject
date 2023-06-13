//
// Created by Wiktor Stępniewski on 04/06/2023.
//

#include "managers/ClientManager.h"
#include "predicates/ClientPhoneNumberPredicate.h"
#include "exceptions/ClientException.h"


using namespace std;

ClientManager::ClientManager() = default;

ClientManager::~ClientManager() = default;

vector<ClientPtr> ClientManager::findAllClients() const
{
    ClientPredicate predicate = [](const ClientPtr &ptrClient) -> bool {
        return true;
    };
    return findClientByPredicate(predicate);
}

ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &surname, const std::string &phoneNumber,
                                        const AddressPtr &adres, const ClientTypePtr &clientType)
{
    if (firstName.empty()) throw ClientException(ClientException::firstNameException);
    if(phoneNumber.empty()) throw ClientException(ClientException::phoneNumberException);
    if (surname.empty()) throw ClientException(ClientException::lastNameException);
    if (adres == nullptr) throw ClientException(ClientException::addressException);
    if (clientType == nullptr) throw ClientException(ClientException::clientTypeException);
    ClientPhoneNumberPredicate numberPredicate(phoneNumber);
    if (clients.findIndividualByPredicate(numberPredicate) == nullptr)
    {
        ClientPtr newClient = make_shared<Client>(firstName, surname, phoneNumber, adres, clientType);
        clients.add(newClient);
        return newClient;
    } else
        return clients.findIndividualByPredicate(numberPredicate);
}

ClientPtr ClientManager::findClientByPhoneNumber(const string &phoneNumber)
{
    if(phoneNumber.empty()) throw ClientException(ClientException::phoneNumberException);
    if (phoneNumber.empty()) return nullptr;
    ClientPhoneNumberPredicate clientsPhoneNumber(phoneNumber);
    return clients.findIndividualByPredicate(clientsPhoneNumber);

}

vector<ClientPtr> ClientManager::findClientByPredicate(const ClientPredicate &predicate) const
{
    return clients.findBy(predicate);
}

void ClientManager::unRegisterClient(const ClientPtr &ptrClient)
{
    if (ptrClient == nullptr)
        throw ClientException(ClientException::clientWrongPtr);
    ClientPhoneNumberPredicate numberPredicate(ptrClient->getPhoneNumber());
    if (clients.findIndividualByPredicate(numberPredicate) != nullptr)
        ptrClient->setArchiveStatus(true);
}

int ClientManager::countRegisteredClients()
{
    return clients.size();
}

void ClientManager::saveToFileClients()
{
    std::string nazwaPliku = "ClientsRepository.txt";
    std::ofstream plik(nazwaPliku);
    if (!plik)
    {
        std::cerr << "Błąd podczas otwierania pliku " << nazwaPliku << std::endl;
        return;
    }
    for (int i = 0; i < clients.findAll().size(); i++)
    {
        plik << clients.get(i)->getClientInfo() << std::endl;
        plik << "---------" << std::endl;
    }
    plik.close();
}
