#include <iostream>
#include "queue.h"

class Process{
public:
    Process(int id, int timeNeeded);
    Process(Process &pr);
    Process();
    int id;
    int timeNeeded;
};

Process::Process(){
}
Process::Process(Process &pr){
    this->id = pr.id;
    this->timeNeeded = pr.timeNeeded;
}
Process::Process(int id, int timeNeeded){
    this->id = id;
    this->timeNeeded = timeNeeded;
}

class ProcessQueue{
private:
    Queue<Process> processQueue;
    const int timeQuantum = 200;
public:
    void addProcess(int id, int timeNeeded);
    void runProgram(int maxTime);
};

void ProcessQueue::addProcess(int id, int timeNeeded){
    processQueue.enqueue(Process(id, timeNeeded));
}

void ProcessQueue::runProgram(int maxTime = INT32_MAX){
    std::cout << "Start programu." << std::endl;
    for(int i = 0; i < maxTime; i++){
        if(processQueue.isEmpty()) break;

        Process workingProcess = this->processQueue.dequeue();
        std::cout << "Przełączono na proces: " << workingProcess.id << " o wymaganym czasie: " << workingProcess.timeNeeded << std::endl;
        
        //proces pracuje przez this.timeQuantum
        std::cout << "Proces pracuje."<<std::endl;
        if(workingProcess.timeNeeded > timeQuantum){
            workingProcess.timeNeeded -= timeQuantum;
            this->processQueue.enqueue(workingProcess);
            std::cout << "Za mało czasu. Ponowne zakolejkowanie. Wywłaszczenie. Przełączenie procesu."<<std::endl;
        }
        else{
            std::cout << "Proces ukończony."<<std::endl;
        }

        i+=this->timeQuantum;
        std::cout << "\n";
    }
}

int main(int argc, char const *argv[])
{
    ProcessQueue pq;
    pq.addProcess(0,100);
    pq.addProcess(1,900);
    pq.addProcess(2,300);
    pq.addProcess(3,150);
    pq.addProcess(4,150);
    pq.addProcess(5,1300);

    pq.runProgram(5000);

    return 0;
}
