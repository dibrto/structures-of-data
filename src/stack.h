#pragma once

template <typename T>
class Stack{
public:
    // Stack();
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
