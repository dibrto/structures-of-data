#include <iostream>
#include<list>
#include<vector>
using namespace std;

template<typename T>
class LexCompare{
  public:
    int operator()(const T& a, const T& b){
      return a < b;
    }
};

template<typename E, template<class> class C>
class PriorityQueue{
  public:
    int size() const;
    bool empty() const;
    const E& min() const;
    void RemoveMin();
    void insert(const E& obj);
    void print();

  private:
    list<E> L;
    C<E> isLess;
};

template<typename E, template<class> class C>
int PriorityQueue<E, C>::size() const{
  return L.size();
}

template<typename E, template<class> class C>
bool PriorityQueue<E, C>::empty() const{
  return L.size() == 0;
}

template<typename E, template<class> class C>
const E& PriorityQueue<E, C>::min() const{
  return L.front();
}

template<typename E, template<class> class C>
void PriorityQueue<E, C>::RemoveMin(){
  L.pop_front();
}

template<typename E, template<class> class C>
void PriorityQueue<E, C>::insert(const E& obj){
  typename list<E>::iterator p;
  p = L.begin();

  while(p != L.end() && !isLess(obj, *p)){
    ++p;
  }

  L.insert(p, obj);

}

template<typename E, template<class> class C>
void PriorityQueue<E, C>::print(){
  typename list<E>::iterator p;
  for(p = L.begin(); p != L.end(); ++p)
    cout << *p <<'\t';
  cout << endl;
}

// alohrithm PriorityQueueSort
template<typename E, template<class> class C>
void PriorityQueueSort(vector<E>& seq, PriorityQueue<E, C> pQ){
  for(int element = 0; element < seq.size(); element++){
    pQ.insert(seq[element]);
    seq.pop_front();
  }


  while(!pQ.empty()){
    E val = pQ.min();
    seq.push_back(val);
    pQ.RemoveMin();
  }
}