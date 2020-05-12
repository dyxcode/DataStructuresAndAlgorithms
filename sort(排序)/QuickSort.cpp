#include <iostream>
#include <algorithm>
using namespace std;

int Partition(int * const begin, int * const end) { //lomuto����
    int i = -1;
    for (int j = 0; j < (end - begin); ++j) {
        if (*(begin + j) <= *(end - 1)) {       //�����һ��ֵΪ�ؼ�ֵ����
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
//    QuickSort(begin, begin + mid);    //���õ���lomute���֣���Ϊlomuto���ֽ����Ժ�
//    QuickSort(begin + mid + 1, end);  //midһ������Ӧ���ڵ�λ��
//}

void QuickSort(int * begin, int * const end) {  //β�ݹ�
    while (begin < end - 1) {
        int mid = Partition(begin, end);
        QuickSort(begin, begin + mid);    //���õ���lomute����
        begin = begin + mid + 1;
    }
}

//int Partition(int * const begin, int * const end) { //hoare����
//    int key = *begin;         //�Ե�һ��ֵΪ�ؼ�ֵ����
//    int i = -1, j = end - begin;  //i, j��������Խ��
//    while (1) {
//        for (++i; *(begin + i) < key; ++i); //�ɿ���do{}while��
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
//    QuickSort(begin, begin + mid + 1);   //����hoare���֣���Ϊhoare����ֻ�ܱ�֤
//    QuickSort(begin + mid + 1, end);     //mid(����mid����ǰ��Ԫ��С�ڵ���mid�Ժ��Ԫ��
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
