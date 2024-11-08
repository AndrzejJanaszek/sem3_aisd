#include <iostream>
#include "priority_queue.h"
#include "queue.h"

enum Directions{
    IDLE,
    UPWARDS,
    DOWNWARDS
};

class Request{
public:
    Request(){};
    Request(int from, int destination, Directions direction){
        this->from = from;
        this->destination = destination;
        this->direction = direction;
    };
    int from;
    int destination;
    Directions direction;
};

class LiftManager{
private:    
    int currentLevel = 0;
    const int maxLevel = 10;
    const int minLevel = -1;
    Directions state = Directions::IDLE;
    PriorityQueue<int, Order::DESCENDING> upwards;
    PriorityQueue<int, Order::ASCENDING> downwards;
    Queue<Request> pendingRequests;

    bool isReachable(int level);
    void queuePendingRequests();
    void goIdle();
public:
    void runLift();
    void move();
    void printState(bool stop);
    void request(int from, int destination, Directions direction);
};

void LiftManager::goIdle(){
    //todo
    this->state = Directions::IDLE;
}

void LiftManager::queuePendingRequests(){
    Queue<Request> tmpPending;  
    // rozpatrz pending requests
    while (!this->pendingRequests.isEmpty())
    {
        tmpPending.enqueue(pendingRequests.dequeue());
    }
    while (!tmpPending.isEmpty())
    {
        Request r = tmpPending.dequeue();

        this->request(r.from, r.destination, r.direction);
    } 
}

void LiftManager::runLift(){
    while (!upwards.isEmpty() | !downwards.isEmpty())
    {
        move();
    }
    
}

void LiftManager::move(){
    if(this->state == Directions::IDLE){
        return; // do nothing
    }

    if(this->state == Directions::UPWARDS){
        //jedz jedno pietro
        this->currentLevel += 1;
        bool stop = false;
        while(currentLevel == upwards.peek()){
            // zatrzymaj się
            stop = true;
            // zdejmij z kolejki pietro
            upwards.dequeue();
            if(upwards.isEmpty()) break;
        }
        this->printState(stop);

        if(this->upwards.isEmpty()){
            if(this->downwards.isEmpty()){
                // Wszystkie zadania wykonane koniec
                this->goIdle();
                return;
            }

            // zmiana kierunku jazdy
            this->state = Directions::DOWNWARDS;

            this->queuePendingRequests();

            // jedź do pierwszego zlecenia
            while(this->currentLevel < downwards.peek()){
                this->currentLevel += 1;
                bool stop = false;
                while(this->currentLevel == downwards.peek()){
                    stop = true;
                    downwards.dequeue();
                    if(downwards.isEmpty()) break;
                }
                
                this->printState(stop);
            }
        }
        
    }else{
        //jedz jedno pietro
        this->currentLevel -= 1;
        bool stop = false;

        while(currentLevel == downwards.peek()){
            // zatrzymaj się
            stop = true;
            // zdejmij z kolejki pietro
            downwards.dequeue();
            if(downwards.isEmpty()) break;
        }
        this->printState(stop);

        if(this->downwards.isEmpty()){
            if(this->upwards.isEmpty()){
                // Wszystkie zadania wykonane koniec
                this->goIdle();
                return;
            }
            // zmiana kierunku jazdy
            this->state = Directions::UPWARDS;

            this->queuePendingRequests();

            // jedź do pierwszego zlecenia
            while(this->currentLevel > upwards.peek()){
                this->currentLevel -= 1;

                bool stop = false;
                while(this->currentLevel == upwards.peek()){
                    stop = true;

                    upwards.dequeue();
                    if(upwards.isEmpty()) break;
                }
                
                this->printState(stop);
            }
        }
    }
}


bool LiftManager::isReachable(int level){
    if(this->state == Directions::UPWARDS){
        if (level >= this->currentLevel)
            return true;
        return false;
    }
    else if(this->state == Directions::DOWNWARDS){
        if (level <= this->currentLevel)
            return true;
        return false;
    }
    
    // IDLE
    return true;
}

void LiftManager::printState(bool stop = false){
    std::cout << "Szyb Windy:\n" << std::endl;
    for(int i = this->maxLevel; i >= this->minLevel; i--){
        std::cout<<"["<< i <<"]\t|";
        if(this->currentLevel == i){
            if(stop)
                std::cout << " [S] |";
            else
                std::cout << " [X] |";   
        }
        else{
            std::cout << "     |";   
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void LiftManager::request(int from, int destination, Directions direction){
    if(this->state == Directions::IDLE){
        // pierwszy request
        // winda ustawia kierunek jazdy i kolejkuje zadanie

// todo request na tym samym pietrze co winda

        // ustal kierunek
        this->state = direction;

        // kolejkuj zadanie
        if(direction == Directions::UPWARDS){
            this->upwards.enqueue(from, from);
            
            // uproszczenie (człowiek magicznie klika przycisk - piętro - w windzie zdalnie)
            this->upwards.enqueue(destination, destination);
        }
        else{
            this->downwards.enqueue(from, from);
            
            // uproszczenie (człowiek magicznie klika przycisk - piętro - w windzie zdalnie)
            this->downwards.enqueue(destination, destination);
        }

        return;
    }

    if(this->state != direction){
        // koljekuj na inny kierunek
        if(direction == Directions::UPWARDS){
            this->upwards.enqueue(from,from);
            this->upwards.enqueue(destination,destination);
        }else{
            this->downwards.enqueue(from,from);
            this->downwards.enqueue(destination,destination);
        }

        return;
    }

    if(this->state == direction & this->isReachable(from)){
        //  kolejkuj kirunek do wykonania (aktualny windy)
        if(direction == Directions::UPWARDS){
            this->upwards.enqueue(from, from);
            
            // uproszczenie (człowiek magicznie klika przycisk - piętro - w windzie zdalnie)
            this->upwards.enqueue(destination, destination);
        }
        else{
            this->downwards.enqueue(from, from);
            
            // uproszczenie (człowiek magicznie klika przycisk - piętro - w windzie zdalnie)
            this->downwards.enqueue(destination, destination);
        }
    }else{
        //  dodaj do oczekujacych
        this->pendingRequests.enqueue( Request(from,destination,direction) );
    }
}

int main(int argc, char const *argv[])
{
    LiftManager lf;
    lf.printState();
    lf.request(2,3,Directions::UPWARDS);
    lf.request(9,0,Directions::DOWNWARDS);
    lf.request(3,8,Directions::UPWARDS);
    lf.request(1,-1,Directions::DOWNWARDS);
    lf.runLift();
    return 0;
}
