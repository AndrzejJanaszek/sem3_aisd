#include <iostream>
#include "priority_queue.h"

class Hospital{
private:
    PriorityQueue<int> queue;
    int lastPatientID = 0;
public:
    void addPatient(int8_t priority);
    void handlePatient();
    void printQueue();
};

void Hospital::addPatient(int8_t priority){
    this->queue.enqueue(lastPatientID++, priority);
}

void Hospital::handlePatient(){
    this->queue.dequeue();
}

void Hospital::printQueue(){
    this->queue.printQueue();
}

void zadanie2(){
    //Zadanie 2: Kolejka priorytetowa dla pacjentów w szpitalu
    
    //print
    // dodaj 4 pacjentów
    //print
    //obsluz jednego
    //print
    //obsluz pozostalych
    //print
    
    Hospital h;
    h.printQueue();

    h.addPatient(2);
    h.addPatient(1);
    h.addPatient(3);
    h.addPatient(7);

    h.printQueue();

    h.handlePatient();
    
    h.printQueue();
    
    h.handlePatient();
    h.handlePatient();
    h.handlePatient();
    
    h.printQueue();

}

int main(int argc, char const *argv[])
{
    zadanie2();
    return 0;
}
