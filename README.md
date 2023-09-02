#BankAccountProject
PL
Wprowadzenie

BankAccountProject to projekt, który powstał w ramach nauki programowania obiektowego w języku C++ na pierwszym roku studiów. Tworzyłem go wspólnie z kolegą ze studiów. Nasza aplikacja demonstruje podstawowe zasady programowania obiektowego, zarządzanie kontami bankowymi, historią transakcji oraz wykorzystanie podziału na serwisy, repozytoria i menadżerów. Projekt ten jest uruchamiany w środowisku konsolowym na systemie Linux, a jego repozytorium zdalne było rozwijane na platformie Atlassian Bitbucket.
Struktura projektu

Projekt BankAccountProject jest starannie podzielony na trzy główne części, aby zachować porządek i przejrzystość kodu:

    Serwisy: Odpowiadają za logikę biznesową i operacje na danych. Serwisy zarządzają kontami bankowymi i transakcjami.

    Repozytoria: Repozytoria są odpowiedzialne za przechowywanie i dostęp do danych. Przechowujemy w nich informacje o kontach bankowych i historii transakcji.

    Menadżery: Menadżery pełnią rolę mediatorów między serwisami a repozytoriami. Zarządzają komunikacją i dostarczają dane serwisom.

Uruchamianie projektu

Aby uruchomić projekt BankAccountProject na systemie Linux, wykonaj poniższe kroki:
 
    1. git clone <URL-repozytorium
    
    2. cd BankAccountProject

    3. Stwórz katalog build na poziomie /src /test, /library 

    4. zbuduj w nowo utworzonym katalogu za pomocą make. 
    
    5. Uruchom: ./Program




#BankAccountProject (EN)
Introduction

BankAccountProject is a project that was created as part of learning object-oriented programming in C++ during the first year of studies. I made it together with a friend from college. Our application demonstrates the basic principles of object-oriented programming, management of bank accounts, transaction history, and the use of a division into services, repositories, and managers. This project is run in a console environment on the Linux system, and its remote repository was developed on the Atlassian Bitbucket platform.
Project Structure

The BankAccountProject project is carefully divided into three main parts to maintain order and code clarity:

    Services: They are responsible for business logic and data operations. Services manage bank accounts and transactions.

    Repositories: Repositories are responsible for storing and accessing data. We store information about bank accounts and transaction history in them.

    Managers: Managers act as mediators between services and repositories. They manage communication and provide data to services.

Running the Project

To run the BankAccountProject project on a Linux system, follow these steps:

    1. Clone the remote repository from the Bitbucket platform to your local environment.
    2. cd BankAccountProject
    3. Stwórz new directory build on level /src /test, /library 
    4. build in new directory using make. 
    5../Program
