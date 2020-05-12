#include <iostream>
using namespace std;

class RBT {
private :
    enum {RED = 0, BLACK};
    struct Node {
        int key;
        bool color;
        Node * left;
        Node * right;
        Node * parent;
        Node(int k = 0, bool c = BLACK, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr)
            : key(k), color(c), left(l), right(r), parent(p) {}
    };
private :
    Node * nil;
    Node * root;
private :
    void leftRotate(Node * x);
    void rightRotate(Node * x);
    void fixup_insert(Node * p);
    void fixup_remove(Node * p);
    void transplant(Node * old_t, Node * new_t);
    void insert(Node * p);
    void remove(Node * p);
    Node * search(Node * p, const int k);
    Node * minimum(Node * p);
    Node * maximum(Node * p);
    void inorderWalk(Node * p) const;
public :
    RBT() : nil(new Node), root(nil) {}
    ~RBT() {delete nil;}
    void insert(const int key) {insert(new Node(key, RED, nil, nil, nil));}
    void remove(const int key) {remove(search(root, key));}
    bool search(const int key) {return (search(root, key) == nil ? false : true);}
    int minimum() {return minimum(root)->key;}
    int maximum() {return maximum(root)->key;}
    int predecessor(const int key);
    int successor(const int key);

friend ostream &operator<<(ostream &os, const RBT &t);
};

void RBT::inorderWalk(Node * p) const {
    if (p != nil) {
        inorderWalk(p->left);
        cout << p->key << ' ';
        inorderWalk(p->right);
    }
}

RBT::Node * RBT::search(Node * p, const int k) {
    if (p == nil || k == p->key)
        return p;
    if (k < p->key)
        return search(p->left, k);
    else
        return search(p->right, k);
}

RBT::Node * RBT::minimum(Node * p) {
    if (p == nil)
        return p;
    while (p->left != nil)
        p = p->left;
    return p;
}

RBT::Node * RBT::maximum(Node * p) {
    if (p == nil)
        return p;
    while (p->right != nil)
        p = p->right;
    return p;
}

int RBT::predecessor(const int k) {
    Node * p = search(root, k);
    if (p == nil)
        return 0;
    if (p->left != nil)
        return maximum(p->left)->key;
    Node * y = p->parent;
    while (y != nil && y->left == p) {
        p = y;
        y = y->parent;
    }
    return y->key;
}

int RBT::successor(const int k) {
    Node * p = search(root, k);
    if (p == nil)
        return 0;
    if (p->right != nil)
        return minimum(p->right)->key;
    Node * y = p->parent;
    while (y != nil && y->right == p) {
        p = y;
        y = y->parent;
    }
    return y->key;
}

void RBT::leftRotate(Node * x) { //assume:x->right != nil
    Node * y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBT::rightRotate(Node * x) { //assume:x->left != nil
    Node * y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBT::insert(Node * p) {
    if (p == nullptr)
        return ;
    Node * x = root;
    Node * y = nil;
    while (x != nil) {
        y = x;
        if (x->key < p->key)
            x = x->right;
        else
            x = x->left;
    }
    p->parent = y;
    if (y == nil)
        root = p;
    else if (y->key < p->key)
        y->right = p;
    else
        y->left = p;
    fixup_insert(p);
}

void RBT::fixup_insert(Node * p) {
    while (p->parent->color == RED) {
        if (p->parent == p->parent->parent->left) {
            Node * y = p->parent->parent->right;
            if (y->color == RED) { //case 1
                p->parent->color = BLACK;
                y->color = BLACK;
                p->parent->parent->color = RED;
                p = p->parent->parent;
            }
            else {
                if (p == p->parent->right) { //case 2
                    p = p->parent;
                    leftRotate(p);
                }
                p->parent->color = BLACK; //case 3
                p->parent->parent->color = RED;
                rightRotate(p->parent->parent);
            }
        }
        else { //with "right" and "left" exchanged
            Node * y = p->parent->parent->left;
            if (y->color == RED) { //case 1
                p->parent->color = BLACK;
                y->color = BLACK;
                p->parent->parent->color = RED;
                p = p->parent->parent;
            }
            else {
                if (p == p->parent->left) { //case 2
                    p = p->parent;
                    rightRotate(p);
                }
                p->parent->color = BLACK; //case 3
                p->parent->parent->color = RED;
                leftRotate(p->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBT::transplant(Node * old_t, Node * new_t) {
    if (old_t->parent == nil)
        root = new_t;
    else if (old_t == old_t->parent->left)
        old_t->parent->left = new_t;
    else
        old_t->parent->right = new_t;
    new_t->parent = old_t->parent;
}

void RBT::fixup_remove(Node * x) {
    Node * z = nil;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            z = x->parent->right;
/*case 1*/  if (z->color == RED) {
                z->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                z = x->parent->right; //new z
            }
/*case 2*/  if (z->left->color == BLACK && z->right->color == BLACK) {
                z->color = RED;
                x = x->parent;
            }
            else {
/*case 3*/      if (z->right->color == BLACK) {
                    z->left->color = BLACK;
                    z->color = RED;
                    rightRotate(z);
                    z = x->parent->right;
                }
/*case 4*/      z->color = x->parent->color;
                x->parent->color = BLACK;
                z->right->color = BLACK;
                leftRotate(x->parent);
                x = root; //exit while
            }
        }
        else {
            z = x->parent->left;
/*case 1*/  if (z->color == RED) {
                z->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                z = x->parent->left; //new z
            }
/*case 2*/  if (z->right->color == BLACK && z->left->color == BLACK) {
                z->color = RED;
                x = x->parent;
            }
            else {
/*case 3*/      if (z->left->color == BLACK) {
                    z->right->color = BLACK;
                    z->color = RED;
                    leftRotate(z);
                    z = x->parent->left;
                }
/*case 4*/      z->color = x->parent->color;
                x->parent->color = BLACK;
                z->left->color = BLACK;
                rightRotate(x->parent);
                x = root; //exit while
            }
        }
    }
    x->color = BLACK;
}

void RBT::remove(Node * p) {
    if (p == nil)
        return ;
    Node * y = p;
    Node * x = nil;
    bool y_originalColor = y->color;
    if (p->left == nil) {
        x = p->right;
        transplant(p, p->right);
    }
    else if (p->right == nil) {
        x = p->left;
        transplant(p, p->left);
    }
    else {
        y = minimum(p->right);
        y_originalColor = y->color;
        x = y->right;
        if (y->parent == p)
            x->parent = y;   //maybe x == nil
        else {
            transplant(y, y->right);
            y->right = p->right;
            y->right->parent = y;
        }
        transplant(p, y);
        y->left = p->left;
        y->left->parent = y;
        y->color = p->color;
    }
    delete p;
    if (y_originalColor == BLACK)
        fixup_remove(x);
}

ostream &operator<<(ostream &os, const RBT &t) {
    t.inorderWalk(t.root);
    return os;
}

int main(void) {
    RBT myRBT;
    int array[6] = {41, 38, 31, 12, 19, 8};
    for (int i = 0; i < 6; ++i)
        myRBT.insert(array[i]);
    cout << myRBT << endl;
    cout << "The max is " << myRBT.maximum() << endl;
    cout << "The min is " << myRBT.minimum() << endl;
    cout << "Is " << 12 << " in this RBT ? " << (myRBT.search(12) ? "true" : "false") << endl;
    cout << "The predecessor of " << 12 << " is " << myRBT.predecessor(12) << endl;
    cout << "The successor of " << 12 << " is " << myRBT.successor(12) << endl;
    cout << "Now remove the number less than 20" << endl;
    for (int i = 0; i < 20; ++i)
        myRBT.remove(i);
    cout << myRBT << endl;
    cout << "Is " << 12 << " in this RBT ? " << (myRBT.search(12) ? "true" : "false") << endl;
    cout << "The max is " << myRBT.maximum() << endl;
    cout << "The min is " << myRBT.minimum() << endl;
    cout << "The predecessor of " << 31 << " is " << myRBT.predecessor(31) << endl;
    cout << "The successor of " << 31 << " is " << myRBT.successor(31) << endl;
    for (int i = 0; i < 200; ++i)
        myRBT.insert(i);
    for (int i = 0; i < 200; ++i)
        myRBT.insert(i);
    cout << myRBT << endl;
    cout << "Now remove the odd number" << endl;
    for (int i = 1; i < 200; i += 2)
        myRBT.remove(i);
    cout << myRBT << endl;
    return 0;
}
