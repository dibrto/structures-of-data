#include <iostream>
#include <vector>
 
using namespace std;
 
template <typename E>
class VectorCompleteTree {
    public:
        typedef typename vector<E>::iterator Position;
        Position pos(int i);
        int index(const Position& p) const;
 
    public:
        VectorCompleteTree();
        int size() const;
 
        Position left(const Position& p);
        Position right(const Position& p);
        Position parent(const Position& p);
 
        bool hasLeft(const Position& p) const;
        bool hasRight(const Position& p) const;
        bool isRoot(const Position& p) const;
 
        Position root();
        Position last();
 
        void addLast(const E elem);
        void removeLast();
        void swap(const Position &p, const Position& q);
 
 
    private:
        vector<E> vec;
};
 
template <typename T>
class LexCompare {
public:
    int operator()(const T &p1, const T& p2) {
        return p1 < p2;
    }
};
 
template <typename E, template <typename> typename C>
class HeapPriorityQueue {
    public:
        int size() const;
        bool empty() const;
 
        const E& min();
        void insert(const E& e);
        void removeMin();
        void print();
 
    private:
        VectorCompleteTree<E> tree;
        C<E> isLess;
        typedef typename VectorCompleteTree<E>::Position Position;
 
};
 
 
// vector complete tree
template<typename E>
VectorCompleteTree<E>::VectorCompleteTree()
    : vec(1) {}
 
template<typename E>
int VectorCompleteTree<E>::size() const{
    return vec.size() - 1;
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::left(const Position& p){
    return pos(2 * index());
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::right(const Position& p) {
    return pos(2 * index() + 1);
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::parent(const Position& p) {
    return pos(2 * index(p) / 2);
}
 
template<typename E>
bool VectorCompleteTree<E>::hasLeft(const Position& p) const{
    return 2 * index(p) <= size();
}
 
template<typename E>
bool VectorCompleteTree<E>::hasRight(const Position& p) const{
    return 2 * index(p) + 1 <= size();
}
 
template<typename E>
bool VectorCompleteTree<E>::isRoot(const Position& p) const{
    return index(p) == 1;
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::root(){
    return pos(1);
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::last(){
    return pos(size());
}
 
template<typename E>
void VectorCompleteTree<E>::addLast(const E elem){
    vec.push_back(elem);
}
 
template<typename E>
void VectorCompleteTree<E>::removeLast(){
    vec.pop_back();
}
 
template<typename E>
void VectorCompleteTree<E>::swap(const Position& p, const Position& q){
    E e = *q;
    *q = *p;
    *p = e;
}
 
template<typename E>
typename VectorCompleteTree<E>::Position VectorCompleteTree<E>::pos(int i){
    return vec.begin() + i;
}
 
template<typename E>
int VectorCompleteTree<E>::index(const Position& p) const{
    return p - vec.begin();
}
 
 
// heap queue
template <typename E, template <typename> typename C>
int HeapPriorityQueue<E, C>::size() const {
    return tree.size();
}
 
template <typename E, template <typename> typename C>
bool HeapPriorityQueue<E, C>::empty() const
{
    return size() == 0;
}
 
template <typename E, template <typename> typename C>
const E& HeapPriorityQueue<E, C>::min() {
    return *(tree.root());
}
 
template <typename E, template <typename> typename C>
void HeapPriorityQueue<E, C>::insert(const E& e) {
    tree.addLast(e);
    Position pos = tree.last();
 
    while (!tree.isRoot(pos)) {
        Position u = tree.parent(pos);
 
        if (!isLess(*pos, *u)) {
            break;
        }
 
        tree.swap(pos, u);
 
        pos = u;
    }
}
 
template <typename E, template <typename> typename C>
void HeapPriorityQueue<E, C>::removeMin(){
    if (size() == 1) {
        tree.removeLast();
        return;
    }
 
    Position pos = tree.root();
    tree.swap(pos, tree.last());
    tree.removeLast();
 
    while (tree.hasLeft(pos)) {
        Position left = pos.left();
        if (tree.hasRight(pos) && isLess(*(tree.right()), *pos)) {
            left = tree.right();
        }
 
        if (isLess(*left, *pos)) {
            tree.swap(pos, left);
            pos = left;
        }
        else {
            break;
        }
    }
 
}
 
template <typename E, template <typename> typename C>
void HeapPriorityQueue<E, C>::print() {
    // todo
}