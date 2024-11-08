#include <iostream>
#include "deque.h"

class TaskManager{
public:
    class Task{
    public:
        Task(){
        }
        Task(int id, bool priority){
            this->id = id;
            this->priority = priority;
        }
        int id;
        bool priority;

        friend std::ostream& operator<<(std::ostream &os, const Task &task);
    };

    Deque<Task> task_queue;

public:
    void addTask(int id, bool priority);
    int handlePriorityTask();
    int handleTask();
    void printTasks();
};

std::ostream& operator<<(std::ostream &os, const TaskManager::Task &task) {
    os << "id: " << task.id << " priority: " << std::boolalpha << task.priority;
    return os;
}

void TaskManager::addTask(int id, bool priority){
    if(priority){
        this->task_queue.front_insert(Task(id, priority));
    }else{
        this->task_queue.rear_insert(Task(id, priority));
    }
}

int TaskManager::handlePriorityTask(){
    return this->task_queue.front_deletion().id;
}

int TaskManager::handleTask(){
    return this->task_queue.rear_deletion().id;
}

void TaskManager::printTasks(){
    this->task_queue.printDeque();
}

int main(int argc, char const *argv[])
{       
    TaskManager mt;

    mt.addTask(1, true);
    mt.printTasks();
    
    mt.addTask(2, true);
    mt.printTasks();
    
    mt.addTask(3, false);
    mt.printTasks();
    
    mt.addTask(4, true);
    mt.printTasks();
    
    mt.addTask(5, false);
    mt.printTasks();
    
    mt.addTask(6, false);
    mt.printTasks();

    return 0;
}
