#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Node {
public :
    int value;
public :
    Node(int v = 0) : value(v) {}
};

class Heap {
    vector<Node> heap;
    int heap_size;

    int Left(int i) {return (i << 1) + 1;}  //�±��0��ʼ
    int Right(int i) {return Left(i) + 1;}
    int Parent(int i) {return (i - 1) >> 1;}
    void MaxHeapify(int i);  //ʹ���iά����������(����ά��)
    void MinHeapify(int i);  //ʹ���iά����С������(����ά��)
    void IncreaseKey(int i, int k);  //�����i��value������k(����ά��)
public :
    Heap() : heap_size(0) {}
    Heap(vector<Node> &t) : heap(t), heap_size(t.size()) {}
    void BuildMaxHeap();     //�������ѣ�ʱ�临�Ӷ�O(n);
    void BuildMinHeap();     //������С�ѣ�ʱ�临�Ӷ�O(n);
    void MinHeapSort();     //��С��������ʱ�临�Ӷ�O(nlgn);
    void MaxHeapSort();     //�Ӵ�С����ʱ�临�Ӷ�O(nlgn);
    //���º������������½���
    void Insert(int k); //����һ��Ԫ�أ����ѣ�
    void Delete(int i);    //ɾ��һ��Ԫ�أ����ѣ�
    Node Maximum();         //����value����Ԫ��
    Node ExtractMax();     //ȥ��������value����Ԫ��
    //union two heap:union the vector of the two heaps, and call BuildMaxHeap()
    int Size() {return heap.size();} //����vector��Ԫ�ظ���
    void PrintAll() {
        for (auto i : heap)
            cout << i.value << ends;
        cout << endl;
    }
};

void Heap::MaxHeapify(const int i) {
    int largest;
    if (Left(i) < heap_size && heap[Left(i)].value > heap[i].value)
        largest = Left(i);
    else
        largest = i;
    if (Right(i) < heap_size && heap[Right(i)].value > heap[largest].value)
        largest = Right(i);
    if (largest != i) {
        swap(heap[i], heap[largest]);
        MaxHeapify(largest);
    }
}

void Heap::MinHeapify(const int i) {
    int least;
    if (Left(i) < heap_size && heap[Left(i)].value < heap[i].value)
        least = Left(i);
    else
        least = i;
    if (Right(i) < heap_size && heap[Right(i)].value < heap[least].value)
        least = Right(i);
    if (least != i) {
        swap(heap[i], heap[least]);
        MinHeapify(least);
    }
}

void Heap::BuildMaxHeap() {
    heap_size = heap.size();
    for (int i = Parent(heap_size - 1); i >= 0; --i)
        MaxHeapify(i);
}

void Heap::BuildMinHeap() {
    heap_size = heap.size();
    for (int i = Parent(heap_size - 1); i >= 0; --i)
        MinHeapify(i);
}

void Heap::MinHeapSort() {
    BuildMaxHeap();
    for (int i = heap.size() - 1; i > 0; --i) {
        swap(heap[i], heap[0]);
        --heap_size;
        MaxHeapify(0);
    }
}

void Heap::MaxHeapSort() {
    BuildMinHeap();
    for (int i = heap.size() - 1; i > 0; --i) {
        swap(heap[i], heap[0]);
        --heap_size;
        MinHeapify(0);
    }
}

void Heap::Insert(int k) {
    heap.push_back(INT_MIN);
    IncreaseKey(heap.size() - 1, k);
}

void Heap::Delete(int i) {
    if (heap[heap.size() - 1].value > heap[i].value) {
        IncreaseKey(i, heap[heap.size() - 1].value);
        heap.pop_back();
    } else {
        heap[i] = heap[heap.size() - 1];
        heap.pop_back();
        heap_size = heap.size();
        MaxHeapify(i);
    }
}

Node Heap::Maximum() {
    return heap[0];
}

Node Heap::ExtractMax() {
    Node max = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    MaxHeapify(0);
    return max;
}

void Heap::IncreaseKey(int i, int k) {
    if (k <= heap[i].value)
        return ;
    while (i > 0 && heap[Parent(i)].value < k) {
        heap[i] = heap[Parent(i)];
        i = Parent(i);
    }
    heap[i].value = k;
}

int main() {
    vector<Node> t{1,9,2,8,3,7,4,6,5};
    Heap i(t);
    i.MinHeapSort();
    i.PrintAll();
    i.BuildMaxHeap();
    i.PrintAll();
    i.MaxHeapSort();
    i.PrintAll();
    i.BuildMinHeap();
    i.PrintAll();

    cout << endl << "test ExtractMax :" << endl;
    i.BuildMaxHeap();
    i.PrintAll();
    cout << "max is " << i.ExtractMax().value << endl;
    i.PrintAll();
    i.BuildMinHeap();
    i.PrintAll();

    cout << endl << "test Delete :" << endl;
    i.BuildMaxHeap();
    i.PrintAll();
    i.Delete(2);
    i.PrintAll();
    i.Delete(5);
    i.PrintAll();
    i.BuildMinHeap();
    i.PrintAll();

    cout << endl << "test Insert :" << endl;
    i.BuildMaxHeap();
    i.PrintAll();
    i.Insert(10);
    i.Insert(11);
    i.Insert(12);
    i.PrintAll();
    i.MaxHeapSort();
    i.PrintAll();

    cout << "size is " << i.Size();

    cout << endl << endl;
    vector<Node> test{100,
                    5,  99,
                4,    3,  98, 97,
            2,    1,  0,  -1,  96, 95, 94, 93,
        -2, -3, -4, -5, -6, -7, -8, -9, 92};

    Heap j(test);

    j.PrintAll();
    j.Delete(7);
    j.PrintAll();

    return 0;
}
