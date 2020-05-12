#include <iostream>
using namespace std;

struct Node {
    Node * prev;
    Node * next;
    int key;
    Node() : prev(nullptr), next(nullptr), key(0) {}
};

class List {
    Node * head;
    int size;
public :
    List() : head(new Node), size(0) {head->next = head; head->prev = head;}
    void insert(int x); //ͷ�巨
    void remove(int x);
    void remove(Node *p);
    Node * search(int x);
    void showlist();
    int getSize() {return size;}
};

void List::insert(int x) {
    Node *p = new Node;
    p->key = x;

    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;

    ++size;
}

void List::remove(Node* p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --size;
}

void List::remove(int x) {
    Node *p = search(x);
    if (p != head)
        remove(p);
}

Node * List::search(int x) {
    Node *p = head->next;
    while (p != head && p->key != x)
        p = p->next;
    return p;
}

void List::showlist() {
    Node *p = head->next;
    while (p != head) {
        cout << p->key << ' ';
        p = p->next;
    }
    cout << endl;
}

int main(void) {
    char n;
    int i = 0;
    int j = 0;
    List t;
    cout << "1.void insert(int x);" << endl;
    cout << "2.void remove(int x);" << endl;
    cout << "3.void showlist();" << endl;
    cout << "4.int getSize();" << endl;
    cout << "0.exit" << endl;

    do {
        cin >> n;
        switch (n) {
            case '1' : t.insert(i++); break;
            case '2' : t.remove(j++); break;
            case '3' : t.showlist(); break;
            case '4' : cout << t.getSize() << endl; break;
        }
    } while (n - '0');

    return 0;
}
