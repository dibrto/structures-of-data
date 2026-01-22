#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
/*------Hide--------*/
class Pair
{
public:
    typedef int Key;   // Key
    typedef int Value; // Value
public:
    Pair(const Key &k = Key(), const Value &v = Value())
        : _key(k), _value(v) {}
    const Key &getKey() const { return _key; }       // Get key (read only)
    void setKey(const Key &k) { _key = k; }          // Set key
    const Value &getValue() const { return _value; } // Get value (read only)
    void setValue(const Value &v) { _value = v; }    // Set value
private:
    Key _key;     // Key
    Value _value; // Value
};
/*------Hide--------*/
template <typename E>
class BinaryTree
{
protected:
    struct Node
    {
        E elt;       // Element value
        Node *par;   // Parent
        Node *left;  // Left child
        Node *right; // Right child
        Node() : elt(), par(NULL), left(NULL), right(NULL) {}
        Node sibling() const // get our sibling
        {
            return (this == par->left ? par->right : par->left);
        }
    };

public:
    class Position
    {
    private:
        Node *v; // Pointer to the node

    public:
        Position(Node *v = NULL) : v(v) {}
        E &element() const { return v->elt; }                 // Get element
        Position left() const { return Position(v->left); }   // Get left child
        Position right() const { return Position(v->right); } // Get right child
        Position parent() const { return Position(v->par); }  // Get parent
        bool isRoot() const { return v->par == NULL; }
        bool isExternal() const { return v->left == NULL && v->right == NULL; }
        bool isInternal() const { return v->left != NULL && v->right != NULL; }
        friend class BinaryTree;
    };
    typedef vector<Position> PositionList;

public:
    BinaryTree() : _root(NULL), n(0) {}
    int size() const { return n; }
    bool empty() const { return size() == 0; }
    Position root() const { return Position(_root); } // Get the root
    // Add root to empty tree
    void addRoot()
    {
        _root = new Node;
        n = 1;
    }

    // Expand external node
    void expandExternal(const Position &p)
    {
        Node *v = p.v;       // p's node
        v->left = new Node;  // Add a new left child
        v->left->par = v;    // v is its parent
        v->right = new Node; // Add a new right child
        v->right->par = v;   // v is its parent
        n += 2;
    }

    // Remove p and parent
    Position removeAboveExternal(const Position &p)
    {
        Node *w = p.v; // Get p's node and parent
        Node *v = w->par;
        Node *sib = (w == v->left ? v->right : v->left);
        if (v == _root)
        {
            _root = sib; // Make sibling root
            sib->par = NULL;
        }
        else
        {
            Node *gpar = v->par; // w's grandparent
            // Replace parent by sib
            if (v == gpar->left)
                gpar->left = sib;
            else
                gpar->right = sib;
            sib->par = gpar;
        }
        delete w;
        delete v;
        n -= 2;
        return Position(sib);
    }
    // void createBTree(queue<E> numbers);
    PositionList positions() const
    {
        PositionList pl;
        preorder(_root, pl);     // Preorder traversal
        return PositionList(pl); // Return resulting list
    }

protected:
    void preorder(Node *v, PositionList &pl) const
    {
        pl.push_back(Position(v)); // Add node to list
        if (v->left != NULL)
            preorder(v->left, pl); // Traverse left subtree
        if (v->right != NULL)
            preorder(v->right, pl); // Traverse right subtree
    }

private:
    Node *_root; // Pointer to the root
    int n;       // Number of nodes
};

/*------------NEW------------*/
template <typename E>
class SearchTree
{
public:
    typedef typename E::Key K;
    typedef typename E::Value V;

    class Iterator;

public:
    SearchTree() : T(), n(0)
    {
        T.addRoot();
        T.expandExternal(T.root());
    }

    int size() const { return n; }
    bool empty() const { return size() == 0; }
    void erase(const Iterator &p) { eraser(p.v); }
    void erase(const K &k)
    {
        TPos v = finder(k, root());
        if (v.isExternal())
        {
            cout << "Erase of nonexistent";
            return;
        }
        eraser(v);
    }
    Iterator find(const K &k)
    {
        TPos v = finder(k, root());

        if (v.isInternal()){ 
            return Iterator(v);
        } 
        else { 
            return end();
        }
    }
    Iterator insert(const K &k, const V &v)
    {
        TPos x = inserter(k, v);
        return Iterator(x);
    }
    Iterator begin();
    Iterator end();

protected:
    typedef BinaryTree<E> _BinaryTree;
    typedef typename _BinaryTree::Position TPos;
    TPos root() const { return T.root().left(); }
    TPos finder(const K &k, const TPos &v)
    {
        if (v.isExternal())
            return v;
        if (k < v.element().getKey())
            return finder(k, v.left());
        else if (v.element().getKey() < k)
            return finder(k, v.right());
        else
            return v;
    }
    TPos inserter(const K &k, const V &x)
    {
        TPos v = finder(k, root());
        if (v.isInternal())
            v.element().setValue(x);
        else
        {
            T.expandExternal(v);
            v.element().setKey(k);
            v.element().setValue(x);
        }
        return v;
    }
    TPos eraser(TPos &v)
    {
        TPos w;
        if (v.left().isExternal())
            w = v.left();
        else if (v.right().isExternal())
            w = v.right();
        else
        {
            w = v.right();
            do
            {
                w = w.left();
            } while (w.isInternal());
            TPos u = w.parent();
            v.element().setKey(u.element().getKey());
            v.element().setValue(u.element().getValue());
        }
        n--;
        return T.removeAboveExternal(w);
    }

private:
    _BinaryTree T;
    int n;

public:
    class Iterator
    {
    private:
        TPos v;

    public:
        Iterator(const TPos &vv) : v(vv) {}
        const E &operator*() const { return v.element(); }
        E &operator*() { return v.element(); }
        bool operator==(const Iterator &p) const {
            return v == p.v;
        } 
        Iterator &operator++()
        {
            TPos w = v.right();

            if (w.isInternal())
            {
                do
                {
                    v = w;
                    w = w.left();
                } while (w.isInternal());
            }
            else
            {
                w = v.parent();
                while (v == w.right())
                {
                    v = w;
                    w = w.parent();
                }
                v = w;
            }
            return *this;
        }
    };
};

int main()
{
    SearchTree<Pair> ST1;
    for (int i = 1; i <= 10; i++){
        ST1.insert(i * 10, i);
    }

    ST1.erase(30);

    typename SearchTree<Pair>::Iterator itr = ST1.find(10);
    Pair p = *itr;
    cout << "The entry with key " << p.getKey() << ":" << "(" << p.getKey() << " " << p.getValue() << ")" << endl;

    itr = ST1.find(30);
    p = *itr;
    cout << "The entry with key " << p.getKey() << ":" << "(" << p.getKey() << " " << p.getValue() << ")" << endl;

    itr = ST1.find(40);
    p = *itr;
    cout << "The entry with key " << p.getKey() << ":" << "(" << p.getKey() << " " << p.getValue() << ")" << endl;

    itr = ST1.find(90);
    p = *itr;
    cout << "The entry with key " << p.getKey() << ":" << "(" << p.getKey() << " " << p.getValue() << ")" << endl;

    return 0;
}
