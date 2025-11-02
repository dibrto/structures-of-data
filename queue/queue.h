#pragma once

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