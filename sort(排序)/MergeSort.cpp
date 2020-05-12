#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//void Merge(int * const first, int * const mid, int * const last) {
//    vector<int> left(first, mid);
//    vector<int> right(mid, last);
//    left.push_back(INT_MAX);       //哨兵INT_MAX必须总是比较中的较大者
//    right.push_back(INT_MAX);      //即待排序的值必须比INT_MAX小
//
//    int i = 0, j = 0;
//    for (int k = 0; k < last - first; ++k) {
//        if (left[i] <= right[j]) {
//            *(first + k) = left[i++];
//        } else {
//            *(first + k) = right[j++];
//        }
//    }
//}

void Merge(int * const first, int * const mid, int * const last) {
    vector<int> left(first, mid);
    vector<int> right(mid, last);

    int i = 0, j = 0, k = 0;
    while (i != left.size() && j != right.size()) {
        if (left[i] <= right[j]) {
            *(first + k) = left[i++];
        } else {
            *(first + k) = right[j++];
        }
        ++k;
    }
    while (i != left.size()) {
        *(first + k) = left[i++];
        ++k;
    }
    while (j != right.size()) {
        *(first + k) = right[j++];
        ++k;
    }
}

void MergeSort(int * const begin, int * const end) {
    if (begin + 1 >= end)
        return ;
    int m = (end - begin) / 2;
    MergeSort(begin, begin + m);
    MergeSort(begin + m, end);
    Merge(begin, begin + m, end);
}

int main(void) {
    int a[9];
    int n = 0;

    while (cin >> a[n++]);
    MergeSort(a, a + 9);

    for (int i = 0; i < 9; ++i) {
        cout << a[i] << ends;
    }
    return 0;
}

