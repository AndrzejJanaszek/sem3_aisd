#ifndef QUEUE
#define QUEUE

#include <iostream>

template <class T>
class Queue{
    class Node{
    public:
        Node(T element);
        T value;
        Node* next;
    };
private:
    Node* front;
    Node* tail;
public:
    Queue();
    void enqueue(T element);
    T dequeue();
    T peek();
    bool isEmpty();
    void printQueue();
};

// ------------------------------------

template <class T>
Queue<T>::Queue(){
    this->front = nullptr;
    this->tail = nullptr;
}

template <class T>
Queue<T>::Node::Node(T element){
    this->value = element;
}

template <class T>
void Queue<T>::enqueue(T element){
    Node* newNode = new Node(element);
    newNode->next = nullptr;
    // pusta kolejka
    if(this->front == nullptr){
        this->front = newNode;          // front i tail wskazuja na nowy element
        this->tail = newNode;
    }else{
        this->tail->next = newNode;     // ostatni element wskazuje na nowy element
        this->tail = newNode;           // update taila na nowy element
    }
}

template <class T>
T Queue<T>::dequeue(){
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

template <class T>
T Queue<T>::peek(){
    return this->front->value;
}

template <class T>
bool Queue<T>::isEmpty(){
    if(this->front == nullptr) return true;
    return false;
}

template <class T>
void Queue<T>::printQueue(){
    if(this->front == nullptr) return;

    Node* ptr = this->front;

    std::cout << "FRONT" << std::endl;
    while(ptr != nullptr){
        std::cout << ptr->value << std::endl;

        ptr = ptr->next;
    }
    std::cout << "TAIL" << std::endl;
}


#endif  /* QUEUE */