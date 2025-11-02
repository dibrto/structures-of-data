#pragma once

template <typename T>
class Deque {
public:
    Deque(int capacity = 100);
    ~Deque();
    Deque(const Deque<T> &other);
    Deque<T> operator=(const Deque<T>& other);

    int getSize();
    bool empty();
    // void insertFront(T elem);
    // void insertBack(T elem);
    // void eraseFront();
    // void eraseBack();
    // T front();
    // T back();

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

template <typename T>
Deque<T>::~Deque(){
    delete[] arr;
}

template <typename T>
Deque<T>::Deque(const Deque<T> &other){
    arr = new T[other.capacity];

    capacity = other.capacity;
    frontElem = other.frontElem;
    backElem = other.backElem;
    size = other.size;

    for (size_t i = 0; i < other.size; i++){
        arr[i] = other.arr[i];
    }    
}

template <typename T>
Deque<T> Deque<T>::operator=(const Deque<T> &other)
{
    if (this == &other){
        cout << "Can not assign to same Deque" << endl;
        return Deque<T>();
    }

    delete[] arr;
    capacity = other.capacity;
    size = other.size;
    frontElem = other.frontElem;
    backElem = other.backElem;

    arr = new T[capacity];
    for (int i = 0; i < size; ++i)
        arr[i] = other.arr[i];

    return *this;
}

template <typename T>
int Deque<T>::getSize(){
    return size;
}

template <typename T>
bool Deque<T>::empty(){
    return size <= 0;
}
