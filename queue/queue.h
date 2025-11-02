#pragma once
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Queue{
public:
    Queue(int capacity = 100);
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T> operator=(const Queue<T>& other);

    int getSize() const;
    bool isEmpty() const;
    void push(T elem);
    T front();
    T pop();
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
Queue<T>::Queue(const Queue<T> &other){
    arr =  new T[other.capacity];

    capacity = other.capacity;
    frontElem = other.frontElem;
    size = other.size;

    for (size_t i = 0; i < other.size; i++){
        arr[i] = other.arr[i];
    }    
}

template <typename T>
Queue<T> Queue<T>::operator=(const Queue<T> &other)
{
    if (this == &other){
        cout << "Can not assign to same Queue" << endl;
        return Queue<T>();
    }

    delete[] arr;
    capacity = other.capacity;
    size = other.size;
    frontElem = other.frontElem;

    arr = new T[capacity];
    for (int i = 0; i < size; ++i)
        arr[i] = other.arr[i];

    return *this;
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
    if (size == capacity){
        cout << "Queue is full" << endl;
        return;
    }

    arr[size] = elem;
    size++;
}

template <typename T>
T Queue<T>::front(){
    if (isEmpty()){
        cout << "Queue is empty!" << endl;
        return T();
    }

    return arr[frontElem];
}

template <typename T>
T Queue<T>::pop(){
    if (isEmpty()){
        cout << "Queue is empty!" << endl;
        return T();
    }

    const T front = this->front();
    frontElem++;
    size--;
    return front;
}

template <typename T>
void Queue<T>::print(){
    for (size_t i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;    
}
