#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

class Skiplist {
private :
    struct Node {
        int key;
        Node * prev;
        Node * next;
        Node * down;
        Node * top;
        Node() : key(0), prev(nullptr), next(nullptr), down(nullptr), top(nullptr) {}
    };
private :
    Node * head;
    int level;
    int size;
private :
    void bindNewNode(Node * x, Node * p);
    void delNode(Node * x);
    Node * searchNode(int key);
public :
    Skiplist() : head(new Node), level(1),size(0)
        {head->key = INT_MIN; srand(static_cast<int>(time(0)));}
    ~Skiplist() {delete head;}
    void insert(int key);
    void remove(int key);
    bool search(int key) {return (searchNode(key) != nullptr);}
    void showSkiplist();
    int getLevel() {return level;}
    int getSize() {return size;}
};

void Skiplist::bindNewNode(Node * x, Node * p) {
    if (!x->next) {
        x->next = p;
        p->prev = x;
    }
    else {
        p->next = x->next;
        x->next->prev = p;
        p->prev = x;
        x->next = p;
    }
}

void Skiplist::insert(int key) {
    Node * p = new Node;
    p->key = key;

    Node * x = head;
    while (1) { //find the prev node of p, which represents the right insert place
        if (x->key <= key) {
            if (x->next)
                x = x->next;
            else if (x->down)
                x = x->down;
            else break;
        }
        else if (x->prev->down)
            x = x->prev->down;
        else {
            x = x->prev;
            break;
        }
    }
    bindNewNode(x, p);
    while (rand() % 2) {  //throw the coin, then judge whether it needs to be higher according to the results
        Node * highp = new Node;
        highp->key = key;
        while (!x->top && x->prev)
            x = x->prev;
        if (x->top) {
            x = x->top;
            bindNewNode(x, highp);
            highp->down = p;
            p->top = highp;
        }
        else { //already the top, add a sentry
            Node * top = new Node;
            x = top;
            top->key = INT_MIN;
            top->down = head;
            head->top = top;
            head = top;
            bindNewNode(top, highp);
            highp->down = p;
            p->top = highp;
            ++level;
        }
        p = highp;
    }
    ++size;
}

void Skiplist::delNode(Node * x) {
    if (!x->next) { //node x is the last one
        if (x->prev == head && head->down) { //x is not at the bottom and x is the last one of this level
            head = head->down;
            head->top = nullptr;
            delete x->prev;
            --level;
        }
        else
            x->prev->next = nullptr;
    }
    else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    delete x;
}

void Skiplist::remove(int key) {
    Node * x = searchNode(key);
    if (x) {
        while (x->down) {
            Node * y = x->down;
            delNode(x);
            x = y;
        }
        delNode(x);
        --size;
    }
}

Skiplist::Node * Skiplist::searchNode(int key) {
    Node * x = head;
    while (1) { //find the prev node of p, which represents the right insert place
        if (x->key == key)
            return x;
        else if (x->key < key) {
            if (x->next)
                x = x->next;
            else if (x->down)
                x = x->down;
            else
                return nullptr;
        }
        else if (x->prev->down)
            x = x->prev->down;
        else {
            return nullptr;
        }
    }
}

void Skiplist::showSkiplist() {
    Node * x = head, * y = head;
    while (y) {
        x = y;
        while (x) {
            if (x->prev != nullptr)
                cout << x->key << ' ';
            x = x->next;
        }
        cout << endl;
        y = y->down;
    }
}

int main(void) {
    Skiplist mySkiplist;

    for (int i = 1; i < 15; i += 2)
        mySkiplist.insert(i);
    mySkiplist.showSkiplist();
    cout << "the size is " << mySkiplist.getSize() << endl;
    cout << "the level is " << mySkiplist.getLevel() << endl;
    cout << "is 5 in the skiplist ? " << (mySkiplist.search(5) ? "true" : "false") << endl;
    cout << "now delete the node that key is less or equal than 5" << endl;
    for (int i = 1; i <= 5; ++i)
        mySkiplist.remove(i);
    mySkiplist.showSkiplist();
    cout << "the size is " << mySkiplist.getSize() << endl;
    cout << "the level is " << mySkiplist.getLevel() << endl;
    cout << "is 5 in the skiplist ? " << (mySkiplist.search(5) ? "true" : "false") << endl;
    cout << "now delete all the node" << endl;
    for (int i = 1; i < 15; ++i)
        mySkiplist.remove(i);
    mySkiplist.showSkiplist();
    cout << "the size is " << mySkiplist.getSize() << endl;
    cout << "the level is " << mySkiplist.getLevel() << endl;
    mySkiplist.insert(2);
    mySkiplist.showSkiplist();
    cout << "the size is " << mySkiplist.getSize() << endl;
    cout << "the level is " << mySkiplist.getLevel() << endl;
    cout << "now delete the node that key is 2" << endl;
    mySkiplist.remove(2);
    for (int i = 1; i < 15; i += 2)
        mySkiplist.insert(i);
    mySkiplist.showSkiplist();
    cout << "the size is " << mySkiplist.getSize() << endl;
    cout << "the level is " << mySkiplist.getLevel() << endl;
    cout << "now delete all the node" << endl;
    for (int i = 1; i < 15; ++i)
        mySkiplist.remove(i);
    return 0;
}
