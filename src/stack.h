#pragma once

template <typename T>
class Stack{
public:
    Stack(int capacity = 100);
    // ~Stack();
    // Stack(const Stack<T> &other);
    // Stack<T> operator=(const Stack<T>& other);

    // int getSize() const;
    // bool isEmpty() const;
    // void push(T elem);
    // T top();
    // T pop();
    

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
