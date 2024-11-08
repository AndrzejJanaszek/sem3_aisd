#include<iostream>

template <class T, const int MAX_SIZE>
class Stack{

private:
    T arr[MAX_SIZE] = {0};
    int head = -1;
public:
    Stack(){
    };

    void push(T element);
    T pop();
    T top();
    bool isEmpty();
    // bool isFull();   do implementacji tablicowej
};

template <class T, const int MAX_SIZE>
void Stack<T,MAX_SIZE>::push(T element){
    head++;
    if(head >= MAX_SIZE){
        std::cout << "Push, przepełnienie stosu." << std::endl;
        throw;
    }
    arr[head] = element;
};

template <class T, const int MAX_SIZE>
T Stack<T,MAX_SIZE>::pop(){
    head--;
    if (this->isEmpty()){
        std::cout << "Pop z pustego stosu" << std::endl;
        throw;
    }
    return arr[head+1];
};


template <class T, const int MAX_SIZE>
T Stack<T,MAX_SIZE>::top(){
    return arr[head];
};


template <class T, const int MAX_SIZE>
bool Stack<T,MAX_SIZE>::isEmpty(){
    if(head < 0) return true;
    return false;
};

int main(int argc, char const *argv[])
{
    Stack<int, 100> s;
    
    return 0;
}


// push() wstawianie od heada