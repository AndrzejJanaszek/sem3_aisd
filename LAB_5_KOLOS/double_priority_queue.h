#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream>

enum Order{
    ASCENDING,
    DESCENDING
};

template <class T, Order order = Order::ASCENDING>
class PriorityQueue{
    class Node{
    public:
        Node(T element, int8_t priority = 255, int8_t secondPriority = 255);
        T value;
        Node* next;
        int8_t priority;    // 0 - max 255 - min
        int8_t secondPriority;    // 0 - max 255 - min
    };
private:
    Node* front;
    Node* tail;
    bool compareOrder(int8_t value, int8_t reference);
public:
    PriorityQueue();
    void enqueue(T element, int8_t priority, int8_t second_priority);
    T dequeue();
    T peek();
    bool isEmpty();
    void printQueue();
};

// ------------------------------------

template <class T, Order order>
bool PriorityQueue<T, order>::compareOrder(int8_t value, int8_t reference) {
    if constexpr (order == Order::ASCENDING) {
        return value < reference;
    } else {
        return value > reference;
    }
}

template <class T, Order order>
PriorityQueue<T, order>::PriorityQueue(){
    this->front = nullptr;
    this->tail = nullptr;
}

template <class T, Order order>
PriorityQueue<T, order>::Node::Node(T element, int8_t priority, int8_t secondPriority){
    this->value = element;
    this->priority = priority;
    this->secondPriority = secondPriority;
}

template <class T, Order order>
void PriorityQueue<T, order>::enqueue(T element, int8_t priority, int8_t second_priority){
    Node* newNode = new Node(element, priority, second_priority);
    Node* ptr = this->front;
    
    if(this->front == nullptr){
        // dodaj pierwszy
        this->tail = newNode;
        this->front = newNode;
        newNode->next = nullptr;

        return;
    }

    while(ptr != nullptr){
        if(this->compareOrder(ptr->priority, priority)){
            // wstaw przed czyli
            // dodaj za ptr i zamien wartosci i priorytet
            newNode->next = ptr->next;
            ptr->next = newNode;

            T tmp_value = ptr->value;
            int tmp_priority = ptr->priority;

            ptr->value = newNode->value;
            ptr->priority = newNode->priority;

            newNode->value = tmp_value;
            newNode->priority = tmp_priority;

            if(this->tail == ptr){
                this->tail = newNode;
            }

            return;
        }
        else if(ptr->priority == priority){
            // jezeli ten sam priorytet głowny
            // porównaj priorytet drugi
            if(!this->compareOrder(ptr->secondPriority, second_priority)){
                // TO SAMO CO WYZEJ

                // wstaw przed czyli
                // dodaj za ptr i zamien wartosci i priorytet
                newNode->next = ptr->next;
                ptr->next = newNode;

                T tmp_value = ptr->value;
                int tmp_priority = ptr->priority;

                ptr->value = newNode->value;
                ptr->priority = newNode->priority;

                newNode->value = tmp_value;
                newNode->priority = tmp_priority;

                if(this->tail == ptr){
                    this->tail = newNode;
                }

                return;
            }
        }

        ptr = ptr->next;
    }

    //dodaj ostatni
    newNode->next = nullptr;
    this->tail->next = newNode;
    this->tail = newNode;
    return;
}

template <class T, Order order>
T PriorityQueue<T, order>::dequeue(){
    if(this->front == nullptr){
        // brak elementow nien mozna usunąc
        throw std::runtime_error("Pusta kolejka, nie mozna usunac elementu.");
    }
    Node* oldNode = this->front;
    this->front = this->front->next;    // przesuniecie frontu na kolejny element
    T tmp = oldNode->value;
    delete oldNode;                    // czyszczenie pamieci
    return tmp;
}

template <class T, Order order>
T PriorityQueue<T, order>::peek(){
    return this->front->value;
}

template <class T, Order order>
bool PriorityQueue<T, order>::isEmpty(){
    if(this->front == nullptr) return true;
    return false;
}

template <class T, Order order>
void PriorityQueue<T, order>::printQueue(){
    std::cout << "Print Queue" << std::endl;

    if(this->front == nullptr) return;

    Node* ptr = this->front;

    std::cout << "FRONT" << std::endl;
    while(ptr != nullptr){
        std::cout <<"value: "<< ptr->value << "\tpriority: "<< (int)(ptr->priority) << "\tsecondPriority: "<< (int)(ptr->secondPriority) << std::endl;

        ptr = ptr->next;
    }
    std::cout << "TAIL\n" << std::endl;
}


#endif  /* PRIORITY_QUEUE */