#pragma once

template <typename T>
class Deque {
public:
    Deque(int capacity = 100);
    ~Deque();
    Deque(const Deque<T> &other);
    Deque<T> operator=(const Deque<T>& other);

    int getSize();
    bool isEmpty();
    void insertFront(T elem);
    void insertBack(T elem);
    T front();
    T back();
    T eraseFront();
    // T eraseBack();
    void print();

private:
    int size, frontIndex, rearIndex, capacity;
    T* arr;
};

template <typename T>
Deque<T>::Deque(int capacity)
: size(0)
, frontIndex(0)
, rearIndex(-1)
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
    frontIndex = other.frontIndex;
    rearIndex = other.rearIndex;
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
    frontIndex = other.frontIndex;
    rearIndex = other.rearIndex;

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
bool Deque<T>::isEmpty(){
    return size <= 0;
}

template <typename T>
void Deque<T>::insertFront(T elem){
    if (size == capacity){
        cout << "Deque is full" << endl;
        return;
    }

    frontIndex != 0 ? frontIndex-- : frontIndex = capacity - 1;
    arr[frontIndex] = elem;
    size++;
}

template <typename T>
void Deque<T>::insertBack(T elem){
    if (size == capacity){
        cout << "Queue is full" << endl;
        return;
    }

    rearIndex != size ? rearIndex++ : rearIndex = 0;
    arr[rearIndex] = elem;
    size++;
}

template <typename T>
T Deque<T>::front(){
    if (isEmpty()){
        cout << "Queue is empty!" << endl;
        return T();
    }
    
    return arr[frontIndex];
}

template <typename T>
T Deque<T>::back(){
    if (isEmpty()){
        cout << "Queue is empty!" << endl;
        return T();
    }

    return arr[rearIndex];
}

template <typename T>
T Deque<T>::eraseFront(){
    if (isEmpty()){
        cout << "Queue is empty!" << endl;
        return T();
    }

    const T front = arr[frontIndex];
    frontIndex != size ? frontIndex++ : frontIndex = 0;
    size--;

    return front;
}

template <typename T>
void Deque<T>::print(){
    if (isEmpty()){
        cout << "Deque is empty!" << endl;
        return;
    }

    for (int i = 0; i < size; i++){
        cout << arr[(frontIndex + i) % capacity] << " ";
    }

    cout << endl;    
}
