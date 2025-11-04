#pragma once

template <typename T>
class Stack{
public:
    Stack(int capacity = 100);
    ~Stack();
    Stack(const Stack<T> &other);
    Stack<T> operator=(const Stack<T>& other);

    int getSize() const;
    bool isEmpty() const;
    void push(T elem);
    T top();
    // T pop();
    void print();
    

private:
    int size, frontIndex, capacity;
    T* arr;
};

template <typename T>
Stack<T>::Stack(int capacity)
    : capacity(capacity)
    , size(0)
    , frontIndex(-1)
    , arr(new T[capacity]){}

template <typename T>
Stack<T>::~Stack(){
    delete[] arr;
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other){
    arr = new T[other.capacity];

    capacity = other.capacity;
    frontIndex = other.frontIndex;
    size = other.size;

    for (size_t i = 0; i < other.size; i++){
        arr[i] = other.arr[i];
    }
}

template <typename T>
Stack<T> Stack<T>::operator=(const Stack<T> &other){
    if (this == &other){
        cout << "Can not copy to same reference" << endl;
        return Stack<T>();
    }

    delete[] arr;
    capacity = other.capacity;
    size = other.size;
    frontIndex = other.frontIndex;

    arr = new T[capacity];
    for (int i = 0; i < size; ++i)
        arr[i] = other.arr[i];

    return *this;
}

template <typename T>
int Stack<T>::getSize() const{
    return size;
}

template <typename T>
bool Stack<T>::isEmpty() const{
    return size <= 0;
}

template <typename T>
void Stack<T>::push(T elem){
    if (size == capacity){
        cout << "Stack is full" << endl;
        return;
    }

    frontIndex++;
    arr[frontIndex] = elem;
    size++;
}

template <typename T>
T Stack<T>::top(){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
        return T();
    }

    return arr[frontIndex];
}

template <typename T>
void Stack<T>::print(){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
        return;
    }

    for (size_t i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;    
}
