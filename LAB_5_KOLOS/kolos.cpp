#include <iostream>
#include "double_priority_queue.h"

struct Patient
{
    Patient(){};
    Patient(int id, int priority, int waitingTime) : id(id), priority(priority), waitingTime(waitingTime){};
    int id;
    int priority;
    int waitingTime;

    friend std::ostream& operator<<(std::ostream &os, const Patient &patient);
};

std::ostream& operator<<(std::ostream &os, const Patient &patient) {
    os << "id: " << patient.id << " priority: " << std::boolalpha << patient.priority << " waitingTime: " << std::boolalpha << patient.waitingTime;
    return os;
}

class PatientQueueSystem{
public:
    PriorityQueue<Patient,Order::DESCENDING> patientQueue;

    void addPatient(Patient patient);
    Patient handlePatient();

    void printPatientQueue();
};

void PatientQueueSystem::addPatient(Patient patient){
    this->patientQueue.enqueue(patient, patient.priority, patient.waitingTime);
}
Patient PatientQueueSystem::handlePatient(){
    return this->patientQueue.dequeue();
}
void PatientQueueSystem::printPatientQueue(){
    this->patientQueue.printQueue();
}

int main(int argc, char const *argv[])
{
    PatientQueueSystem PQS;
// Przykład wejścia:
// • Dodaj pacjentów: (1, 30), (2, 20), (2, 40), (1, 50)
// Przykład wyjścia:
// • Kolejność obsługi: (1, 50), (1, 30), (2, 40), (2, 20)

    PQS.addPatient(Patient(1,1,30));
    PQS.addPatient(Patient(2,2,20));
    PQS.addPatient(Patient(3,2,40));
    PQS.addPatient(Patient(4,1,50));

    PQS.printPatientQueue();
    


    return 0;
}
