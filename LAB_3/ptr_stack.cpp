#include<iostream>

template <class T>
class Node{
public:
    T* value;
    Node* next;

    Node(T *value){
        this->value = value;
    }
};

template <class T>
class Stack{
public:
    Stack(){
        head == nullptr;
    };

    void push(T *element);
    T pop();
    T top();
    bool isEmpty();
    // bool isFull();   do implementacji tablicowej

private:
    Node<T> *head = nullptr;
};

template <class T>
void Stack<T>::push(T *element){
    Node newNode = Node(element);
    newNode.next = this->head;
    this->head = &newNode;
};

template <class T>
T Stack<T>::pop(){
    if(this->head == nullptr){
        std::cout << "Pop, Pusty stos" << std::endl;
        throw;
    }

    T ret = *(this->head->value);
    this->head->next = this->head->next->next;
    return ret;
};

template <class T>
T Stack<T>::top(){
    if (this->head == nullptr){
        std::cout << "Top, Pusty stos" << std::endl;
        throw;
    }
    return *(this->head->value);
};

template <class T>
bool Stack<T>::isEmpty(){
    if (this->head == nullptr) return true;
    return false;
};

bool zad2SprawdzeniePoprawnosciNawiasow(std::string expresion){
    Stack<bool> brackets;

    for(int i = 0; i < expresion.length(); i++){
        if (expresion[i] == '('){
            brackets.push();
        }
    }
}

int main(int argc, char const *argv[])
{
    Stack<int> stosik;
    // std::cout << stosik.isEmpty() << std::endl;
    stosik.top();    
    
    return 0;
}


// push() wstawianie od heada