#ifndef DEQUE
#define DEQUE

#include <iostream>

template <class T>
class Deque{
private:
    class Node{
        public:
        Node(T value);
        Node* prev;
        Node* next;
        T value;
    }; 
public:
    Deque();
    Node* front;
    Node* tail;

    void front_insert(T element);
    void rear_insert(T element);
    T front_deletion();
    T rear_deletion();
    bool isEmpty();

    void printDeque();
};

template<class T>
Deque<T>::Node::Node(T value){
    this->value = value;
};

template<class T>
Deque<T>::Deque(){
    this->front = nullptr;
    this->tail = nullptr;
};

template<class T>
void Deque<T>::front_insert(T element){
    Node* newNode = new Node(element);
    if(this->front == nullptr){
        this->front = newNode;
        this->tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return;
    }

    newNode->prev = nullptr;
    newNode->next = this->front;
    this->front->prev = newNode;
    this->front = newNode;

    //   f
    // # 1 2 3
};

template<class T>
void Deque<T>::rear_insert(T element){
    Node* newNode = new Node(element);
    if(this->front == nullptr){
        this->front = newNode;
        this->tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return;
    }

    newNode->next = nullptr;
    newNode->prev = this->tail;
    this->tail->next = newNode;
    this->tail = newNode;
};

template<class T>
T Deque<T>::front_deletion(){
    if (this->front == nullptr){
        throw std::runtime_error("Proba usuniecia z pustej deque");
    }

    Node* tmp = this->front;
    T ret = tmp->value;
    this->front = this->front->next;
    delete tmp;

    // if isEmpty
    if (this->front == nullptr)
        this->tail = nullptr;

    return ret;
};

template<class T>
T Deque<T>::rear_deletion(){
    if (this->front == nullptr){
        throw std::runtime_error("Proba usuniecia z pustej deque");
    }

    Node* tmp = this->tail;
    T ret = tmp->value;
    this->tail = this->tail->prev;
    this->tail->next = nullptr;
    delete tmp;

    //if isEmpty
    if (this->tail == nullptr)
        this->front = nullptr;

    return ret;
};

template<class T>
bool Deque<T>::isEmpty(){
    if (this->front == nullptr) return true;
    return false;
};

template <class T>
void Deque<T>::printDeque(){
    std::cout << "Print"<<std::endl;
    Node* ptr = this->front;
    while(ptr != nullptr){
        std::cout << ptr->value << std::endl;

        ptr = ptr->next;
    }
    std::cout << "\n";
};

#endif // DEQUE