#include<iostream>

using namespace std;

template<typename T>
class NodeList {
private:
    struct Node{
        T elem;
        Node* next;
        Node* prev;
    };
public:
  class Iterator{
    public:
        Node* v;
        Iterator(Node* u){
            v = u;
        }
    public:
        T& operator* () {return v-> elem;}
        Iterator& operator++ (){
          v = v->next;
          return *this;
        }
        Iterator& operator-- (){
          v = v->prev;
          return *this;
        }

        bool operator==(const Iterator& p) const{
          return v == p.v;
        }

        bool operator!=(const Iterator& p) const{
          return v != p.v;
        }
  };
private:
    int n;
    Node* header;
    Node* trailer;

public:
    NodeList();
    NodeList(const NodeList& other);
    ~NodeList();
    NodeList& operator=(const NodeList& other);

    int size() const { return n; }
    bool empty() const{ return n == 0; }
    Iterator begin() const { return Iterator(header->next); }
    Iterator end() const { return Iterator(trailer); }

    void insert(const Iterator& p, const T& newVal);
    void insertFront(const T& newVal) { insert(begin(), newVal); }
    void insertBack(const T& newVal) { insert(end(), newVal); }

    void erase(const Iterator& p);
    void eraseFront() {erase(begin()); }
    void eraseBack() {erase(--end()); }

    // void print();
};

template<typename T>
NodeList<T>::NodeList(){
    n = 0;

    header = new Node;
    trailer = new Node;

    header->next = trailer;
    trailer->prev = header;
}
template<typename T>
NodeList<T>::~NodeList(){

    int index = 0;
    Iterator itTemp = Iterator(begin());
    while(index < size()){
        Node* nd = itTemp.v;
        delete nd;
        index++;
        ++itTemp;
    }

    delete header;
    delete trailer;
}
template<typename T>
NodeList<T>::NodeList(const NodeList& other){
    n = other.n;

    header = new Node;
    trailer = new Node;

    header->next = trailer;
    trailer->prev = header;

    int index = 0;
    Iterator itTemp = Iterator(other.begin());
    while(index < other.size()){
        Node* nd = itTemp.v;
        insertBack(nd->elem);
        index++;
        ++itTemp;
    }
}
template<typename T>
NodeList<T>& NodeList<T>::operator=(const NodeList& other){
    if(this != &other){
        n = other.size();
        Iterator itTemp = Iterator(other.begin());

        --itTemp;
        header = itTemp.v;

        itTemp = Iterator(other.end());
        trailer = itTemp;

    }
    return *this;
}

template<typename T>
void NodeList<T>::insert(const Iterator& p, const T& newVal){
    Node* w = p.v;
    Node* u = w->prev;

    Node* newNode = new Node;
    newNode->elem = newVal;
    newNode->next = w; w->prev = newNode;
    newNode->prev = u; u->next = newNode;
    n++;
}

template<typename T>
void NodeList<T>::erase(const Iterator& p){
    Node* v = p.v;
    Node* w = v->next;
    Node* u = v->prev;

    u->next = w; w->prev = u;
    delete v;
    n--;
}