#pragma once

template <typename T>
class Deque {
public:
    Deque(int capacity = 100);
    // ~Deque();
    // Deque(const Deque &other);

    // void insertFront(T elem);
    // void insertBack(T elem);
    // void eraseFront();
    // void eraseBack();
    // T front();
    // T back();
    // int getSize();
    // bool empty();

private:
    int size, frontElem, backElem, capacity;
    T* arr;
};

template <typename T>
Deque<T>::Deque(int capacity)
: size(0)
, frontElem(0)
, backElem(0)
, capacity(capacity)
, arr(new T[capacity]) {}
