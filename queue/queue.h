#pragma once
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Queue{
public:
    Queue(int capacity = 100);
    ~Queue();
    Queue(const Queue& other);

    int getSize() const;
    bool isEmpty() const;
    void push(T elem);
    int front();
    int pop();
    void print();

private:
    int size, frontElem, capacity;
    T* arr;
};

template <typename T>
Queue<T>::Queue(int capacity)
: size(0), frontElem(0), capacity(capacity), arr(new T[capacity]) {}

template <typename T>
Queue<T>::~Queue(){
    delete[] arr;
}

template <typename T>
Queue<T>::Queue(const Queue &other){
    arr =  new T[other.capacity];

    capacity = other.capacity;
    frontElem = other.frontElem;
    size = other.size;

    for (size_t i = 0; i < other.size; i++){
        arr[i] = other.arr[i];
    }    
}

template <typename T>
int Queue<T>::getSize() const{
    return size;
}

template <typename T>
bool Queue<T>::isEmpty() const{
    return size <= 0;
}

template <typename T>
void Queue<T>::push(T elem){
    arr[size] = elem;
    size++;
}

template <typename T>
void Queue<T>::print(){
    for (size_t i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;    
}
