#include <iostream>
#include "queue.h"

class Shop{
private:
    int newClientID = 0;
    Queue<int> clients;
public:
    void addClient();
    void handleClient();
    void printQueue();
};

void Shop::addClient(){
    clients.enqueue(newClientID++);
}

void Shop::handleClient(){
    std::cout << "Obsluga klienta\n";
    clients.dequeue();
    std::cout << "Klient obsluzony\n";
}

void Shop::printQueue(){
    clients.printQueue();
}

void zadanie1(){
// Zadanie 1: Symulacja kolejki w sklepie (FIFO)
    Shop shop;

    shop.printQueue();

    shop.addClient();
    shop.addClient();
    shop.addClient();
    shop.addClient();

    shop.printQueue();

    shop.handleClient();
    shop.handleClient();
    
    shop.printQueue();
    
    shop.addClient();

    shop.printQueue();

    shop.handleClient();
    shop.handleClient();
    shop.handleClient();
    // shop.handleClient();
}

int main()
{
    // Queue<int> clients;
    // std::cout << "IsEmpty(): " << clients.isEmpty() << std::endl;
    // clients.enqueue(1);
    // std::cout << "IsEmpty(): " << clients.isEmpty() << std::endl;
    
    zadanie1();

    return 0;
}
