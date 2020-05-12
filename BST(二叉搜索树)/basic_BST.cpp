#include <iostream>
using namespace std;

struct Node {
    int key;
    Node * left;
    Node * right;
    Node * parent;
    Node() : key(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
    Node * root;
private :
    Node * minimum(Node * p);
    Node * maximum(Node * p);
    //用新结点代替旧结点，只修改结点与其父节点的指向，允许新结点为空
    void transplant(Node * old_t, Node * new_t);
public :
    BST() : root(nullptr) {}
    Node * search(const int k) {return search(root, k);}
    Node * search(Node * p, const int k);
    const Node * minimum() {return minimum(root);}
    const Node * maximum() {return maximum(root);}
    const Node * successor(Node * p);
    const Node * predecessor(Node * p);
    void insert(const int k);
    void remove(const int k) {remove(search(k));}
    void remove(Node * p);
    void inorderWalk() {inorderWalk(root);}
    void inorderWalk(Node * p);
};

Node * BST::search(Node * p, const int k) {
    if (p == nullptr || k == p->key)
        return p;
    if (k < p->key)
        return search(p->left, k);
    else
        return search(p->right, k);
}

Node * BST::minimum(Node * p) {
    if (p == nullptr)
        return p;
    while (p->left)
        p = p->left;
    return p;
}

Node * BST::maximum(Node * p) {
    if (p == nullptr)
        return p;
    while (p->right)
        p = p->right;
    return p;
}

const Node * BST::successor(Node * p) {
    if (p->right)
        return minimum(p->right);
    Node * y = p->parent;
    while (y != nullptr && y->right == p) {
        p = y;
        y = y->parent;
    }
    return y;
}

const Node * BST::predecessor(Node * p) {
    if (p->left)
        return maximum(p->left);
    Node * y = p->parent;
    while (y != nullptr && y->left == p) {
        p = y;
        y = y->parent;
    }
    return y;
}

void BST::insert(const int k) {
    Node * p = new Node;
    p->key = k;

    Node *x = root, *y = nullptr;
    while (x != nullptr) {
        y = x;
        if (x->key < k)
            x = x->right;
        else
            x = x->left;
    }
    p->parent = y;
    if (y == nullptr)
        root = p;
    else if (y->key < k)
        y->right = p;
    else
        y->left = p;
}

void BST::transplant(Node * old_t, Node * new_t) {
    if (old_t->parent == nullptr)
        root = new_t;
    else if (old_t == old_t->parent->left)
        old_t->parent->left = new_t;
    else
        old_t->parent->right = new_t;
    if (new_t != nullptr)
        new_t->parent = old_t->parent;
}

void BST::remove(Node * p) {
    if (p->left == nullptr)
        transplant(p, p->right);
    else if (p->right == nullptr)
        transplant(p, p->left);
    else {
        Node * t = minimum(p->right);
        if (t->parent != p) {
            transplant(t, t->right);
            t->right = p->right;
            t->right->parent = t;
        }
        transplant(p, t);
        t->left = p->left;
        t->left->parent = t;
    }
    delete p;
}

void BST::inorderWalk(Node * p) {
    if (p) {
        inorderWalk(p->left);
        cout << p->key << ends;
        inorderWalk(p->right);
    }
}

int main(void) {
    BST myBST;

    for (int i = 0; i < 10; ++i)
        myBST.insert(i);
    myBST.inorderWalk();
    cout << endl;
    cout << "max = " << myBST.maximum()->key << endl;
    cout << "min = " << myBST.minimum()->key << endl;
    for (int i = 1; i < 10; i += 2)
        myBST.remove(i);
    myBST.inorderWalk();
    cout << endl;
    cout << "max = " << myBST.maximum()->key << endl;
    cout << "min = " << myBST.minimum()->key << endl;
    Node * p;
    p = myBST.search(6);
    cout << "6 predecessor is " << myBST.predecessor(p)->key << endl;
    cout << "6 successor is " << myBST.successor(p)->key << endl;
    for (int i = 10; i < 20; i += 2)
        myBST.insert(i);
    myBST.inorderWalk();
    cout << endl;
    cout << "max = " << myBST.maximum()->key << endl;
    cout << "min = " << myBST.minimum()->key << endl;
    cout << "6 predecessor is " << myBST.predecessor(p)->key << endl;
    cout << "6 successor is " << myBST.successor(p)->key << endl;
    p = myBST.search(10);
    cout << "10 predecessor is " << myBST.predecessor(p)->key << endl;
    cout << "10 successor is " << myBST.successor(p)->key << endl;
    for (int i = 0; i < 20; i += 2)
        myBST.remove(i);
    myBST.inorderWalk();
    return 0;
}
