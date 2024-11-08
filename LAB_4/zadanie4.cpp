// Zadanie 4: Kolejka dwustronna (deque) - Przegląd zadań z priorytetami
// Napisz program, który zarządza listą zadań o różnym priorytecie, używając kolejki dwustronnej
// (deque). Zadania o wysokim priorytecie powinny być dodawane na początku, a zwykłe
// zadania na końcu kolejki. Program powinien umożliwiać obsłużenie zadania z obu końców
// kolejki.

#include <iostream>
#include "deque.h"

class TaskManager{
public:
    class Task{
    public:
        Task(){};
        Task(int id, bool priority){
            this->id = id;
            this->priority = priority;
        }
        int id;
        bool priority;

        friend std::ostream& operator<<(std::ostream &os, const Task &task);
    };

    Deque<Task> task_queue;
    void addTask(int id, bool priority);
    int handlePriorityTask();
    int handleTask();
    void printTasks();
    
    
};
std::ostream& operator<<(std::ostream &os, const TaskManager::Task &task) {
    std::cout<<"ads\n";
    os << "id: " << task.id << " priority: " << std::boolalpha << task.priority;
    return os;
}


void TaskManager::addTask(int id, bool priority){
    if(priority){
        this->task_queue.front_insert(Task(id, priority));
    }else{
        this->task_queue.rear_insert(Task(id, priority));
    }
};
int TaskManager::handlePriorityTask(){
    return this->task_queue.front_deletion().id;
};
int TaskManager::handleTask(){
    return this->task_queue.rear_deletion().id;
};

void TaskManager::printTasks(){
    this->task_queue.printDeque();
}


int main(int argc, char const *argv[])
{       
    TaskManager mt;

    mt.printTasks();

    mt.addTask(1,0);
    mt.addTask(2,1);
    mt.addTask(3,0);
    mt.addTask(4,1);
    mt.addTask(5,0);
    
    mt.printTasks();
    
    mt.handleTask();    
    mt.handleTask();    
    mt.handleTask();    
    mt.handlePriorityTask();    
    mt.handlePriorityTask();    
    
    mt.printTasks();



    return 0;
}
