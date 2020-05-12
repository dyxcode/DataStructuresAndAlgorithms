#include <iostream>
#include <algorithm>
using namespace std;

int Partition(int * const begin, int * const end) { //lomuto划分
    int i = -1;
    for (int j = 0; j < (end - begin); ++j) {
        if (*(begin + j) <= *(end - 1)) {       //以最后一个值为关键值划分
            ++i;
            swap(*(begin + i), *(begin + j));
        }
    }
    return i;
}
//
//void QuickSort(int * const begin, int * const end) {
//    if (begin >= end - 1)
//        return ;
//    int mid = Partition(begin, end);
//    QuickSort(begin, begin + mid);    //调用的是lomute划分，因为lomuto划分结束以后
//    QuickSort(begin + mid + 1, end);  //mid一定在它应该在的位置
//}

void QuickSort(int * begin, int * const end) {  //尾递归
    while (begin < end - 1) {
        int mid = Partition(begin, end);
        QuickSort(begin, begin + mid);    //调用的是lomute划分
        begin = begin + mid + 1;
    }
}

//int Partition(int * const begin, int * const end) { //hoare划分
//    int key = *begin;         //以第一个值为关键值划分
//    int i = -1, j = end - begin;  //i, j根本不会越界
//    while (1) {
//        for (++i; *(begin + i) < key; ++i); //可看做do{}while；
//        for (--j; *(begin + j) > key; --j);
//        if (i < j)
//            swap(*(begin + i), *(begin + j));
//        else
//            return j;
//    }
//}
//
//void QuickSort(int * const begin, int * const end) {
//    if (begin >= end - 1)
//        return ;
//    int mid = Partition(begin, end);
//
//    QuickSort(begin, begin + mid + 1);   //调用hoare划分，因为hoare划分只能保证
//    QuickSort(begin + mid + 1, end);     //mid(包括mid）以前的元素小于等于mid以后的元素
//}

int main(void) {
    int a[1000];
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    QuickSort(a, a + n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}
