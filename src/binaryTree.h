#include<iostream>
using namespace std;

template<typename T>
class BinaryTree {
protected:
	struct Node 
	{
		T elt;
		Node* par;
		Node* left;
		Node* right;

		Node() : elt(),par(NULL), left(NULL), right(NULL) { }
	};
public:
	class Position {
        private:
            Node* v;
            Position(Node* v = NULL) : v(v) {};
        public:
            T& operator*() { return v->elt; }
            Position left() const { return Position(v->left); }
            Position right() const { return Position(v->right); }
            Position parent() const { return Position(v->par); }

            bool isRoot() const { return v->par == NULL; }
            bool isExternal() const { return v->left == NULL; }

            friend class BinaryTree;
    };

	typedef vector<Position> PositionList;

public:
	BinaryTree() { }
	int size() const { return n; }
	bool empty() const { return size() == 0; }
	Position root() const { return Position(_root); }
	void addRoot() { _root = new Node; n++; }
	void expandExternal(const Position& p) {
		Node* v = p.v;

		v->left = new Node;
		v->left->par = v;

		v->right = new Node;
		v->right->par = v;

		n+= 2;
	}
	Position removeAboveExternal(const Position& p){
		Node* w = p.v;
		Node* v = w->par;
		Node* z = (w == v->left) ? v->right : v->left;
		if (v == _root)
		{
			_root = z;
			z->par = NULL;
		}
		else
		{
			Node* u = v->par;
			if (v == u->left)
			{
				u->left = z->left;
			}
			else
			{
				u->right = z;
			}
			z->par = u;
		}
		delete w;
		delete v;

		n -= 2;
		return Position(z);
	}
	PositionList positions() const {
        PositionList pl;
        preorder(_root, pl);
        return pl;
    };

    void preorder(Node* v, PositionList& pl) const;
	

private:
	Node* _root;
	int n;
};

template<typename T>
void BinaryTree<T>::preorder(Node* v, PositionList& pl) const {
	pl.push_back(Position(v));
	if (v->left != NULL)
	{
		preorder(v->left, pl);
	}
	else if (v->right != NULL)
	{
		preorder(v->right, pl);
	}
}