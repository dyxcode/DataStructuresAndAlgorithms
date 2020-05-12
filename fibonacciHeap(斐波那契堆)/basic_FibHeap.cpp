#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class FibHeap {
private :
    struct Node {
        Node * parent;
        Node * child;
        Node * left;
        Node * right;
        int key;
        int degree; //degree of children
        bool mark; //whether lose any child
        Node() : parent(nullptr), child(nullptr), left(this), right(this),
                 key(0), degree(0), mark(false) {}
    };
private :
    Node * min; //pointer to the minimum node of heap
    int n;
private :
    void listAdd(Node * &r, Node * p);//add p to r
    void listdelete(Node * p);
    void listUnion(Node * x, Node * y);//add x and y
    int Dn() {return (log2(n) + 1);} //当所有根都合并到一棵树上时，dn最大，为log2(n), 参考二项树
    void consolidate();
    void heapLink(Node * y, Node * x);
    void cut(Node * x, Node * y);
    void cascadingCut(Node * y);
    Node * search(Node * r, int k);//search is not good in heap
public :
    FibHeap() : min(nullptr), n(0) {}
    void insert(int k);
    int extractMin(); //get minimum node and delete it
    int minimum() {return min->key;}
    void decreaseKey(Node * x, int k);
    void remove(int k);
    void heapUnion(FibHeap &b);
    bool search(int k) {return (search(min, k) == nullptr ? false : true);}
    bool empty() {return n == 0;}
};

void FibHeap::listAdd(Node * &r, Node * p) {
    if (r == nullptr) {
        r = p;
        r->left = r;
        r->right = r;
    }
    else {
        Node * x = r; //去引用
        p->right = x->right;
        p->left = x;
        x->right->left = p;
        x->right = p;
    }
}

void FibHeap::listdelete(Node * p) {
    p->left->right = p->right;
    p->right->left = p->left;
}

void FibHeap::listUnion(Node * x, Node * y) {
    if (x == nullptr)
        x = y;
    else {
        Node * tail = x->left;
        x->left->right = y;
        y->left->right = x;
        x->left = y->left;
        y->left = tail;
    }
}

void FibHeap::insert(int k) {
    Node * p = new Node;
    p->key = k;
    listAdd(min, p);
    if (min->key > k) {
        min = p;
    }
    ++n;
}

void FibHeap::heapLink(Node * y, Node * x) {
    listdelete(y);
    listAdd(x->child, y);
    ++x->degree;
    y->mark = false;
}

void FibHeap::consolidate() {
    vector<Node*> a(Dn(), nullptr);
    Node *x, *y, *z;
    int d;
    Node * sentry = new Node;
    listAdd(min->left, sentry); //add a sentry
    for (x = min; x != sentry; x = z) {
        z = x->right; //防止x被link到y上，导致x-right无法指向正确的位置，所以先保存
        d = x->degree;
        while (a[d] != nullptr) {
            y = a[d];
            if (x->key > y->key)
                swap(x, y);
            heapLink(y, x);
            a[d] = nullptr;
            ++d;
        }
        a[d] = x;
    }
    min = nullptr;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != nullptr) {
            listAdd(min, a[i]);
            if (a[i]->key < min->key)
                min = a[i];
        }
    }
    delete sentry;
}

int FibHeap::extractMin() {
    int ret = 0;
    Node * p = min;
    if (p) {
        ret = p->key;
        if (p->child) {
            Node * x = p->child;
            Node * y = x->right;
            for (int i = 0; i < p->degree; ++i) {
                listAdd(min, x);
                x->parent = nullptr;
                x = y;
                y = y->right;
            }
        }
        if (p->right == p) //the child of p is empty, and p is the only one in root list
            min = nullptr;
        else {
            min = p->right;
            listdelete(p);
            consolidate();
        }
        delete p;
        --n;
    }
    return ret;
}

void FibHeap::cut(Node * x, Node * y) {
    listdelete(x);
    --y->degree;
    listAdd(min, x);
    x->parent = nullptr;
    x->mark = false;
}

void FibHeap::cascadingCut(Node * y) {
    Node * z = y->parent;
    if (z) {
        if (y->mark == false)
            y->mark = true;
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

void FibHeap::decreaseKey(Node * x, int k) {
    if (k >= x->key)
        return ;
    x->key = k;
    Node * y = x->parent;
    if (y && y->key > x->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key)
        min = x;
}

void FibHeap::remove(int k) {
    Node * p = search(min, k);
    if (p == nullptr)
        return ;
    decreaseKey(p, INT_MIN);
    extractMin();
}

void FibHeap::heapUnion(FibHeap &b) { //can't use b any more
    if (b.min == nullptr)
        return ;
    listUnion(min, b.min);
    if (min->key > b.min->key)
        min = b.min;
    n += b.n;
}

FibHeap::Node * FibHeap::search(Node * r, int k) {
    if (r == nullptr)
        return r;
    Node * x = r, *y;
    do {
        if (x->key == k)
            return x;
        else if (x->key < k) {
            y = search(x->child, k);
            if (y)
                return y;
        }
        x = x->right;
    } while (x != r);

    return nullptr;
}

int main(void) {
    FibHeap myFibHeap;
    FibHeap second;
    for (int i = 0; i < 100; ++i)
        myFibHeap.insert(i);
    cout << "min is " << myFibHeap.minimum() << endl;
    cout << "is 0 in the heap ? " << myFibHeap.search(0) << endl;
    cout << "is 10 in the heap ? " << myFibHeap.search(10) << endl;
    for (int i = 0; i < 50; ++i)
        myFibHeap.remove(i);
    cout << "min is " << myFibHeap.minimum() << endl;
    cout << "is 0 in the heap ? " << myFibHeap.search(0) << endl;
    cout << "is 10 in the heap ? " << myFibHeap.search(10) << endl;
    for (int i = 0; i < 50; ++i)
        second.insert(i);
    myFibHeap.heapUnion(second);
    cout << "min is " << myFibHeap.minimum() << endl;
    cout << "is 0 in the heap ? " << myFibHeap.search(0) << endl;
    cout << "is 10 in the heap ? " << myFibHeap.search(10) << endl;
    for (int i = 0; i < 100; ++i)
        myFibHeap.remove(i);
    cout << "is heap empty ? " << myFibHeap.empty() << endl;
    cout << "now add below 500" << endl;
    for (int i = 1; i < 500; i += 3)
        myFibHeap.insert(i);
    cout << "min is " << myFibHeap.minimum() << endl;
    for (int i = 0; i < 500; ++i)
        myFibHeap.remove(i);
    cout << "is heap empty ? " << myFibHeap.empty() << endl;
    return 0;
}
