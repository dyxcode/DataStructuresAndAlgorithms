#include <iostream>
#include <algorithm>
using namespace std;

void InsertionSort(int * const begin, int * const end) {
    int i, j, key;
    for (i = 1; i < begin - end; ++i) {
        key = *(begin + i);
        for (j = i - 1; j >= 0 && (*(begin + j) > key); --j) {
            *(begin + j + 1) = *(begin + j);
        }
        *(begin + j + 1) = key;
    }
}
int Partition(int * const begin, int * const end, int x) {
    int i = -1;
    for (int j = 0; j < (end - begin); ++j) {
        if (*(begin + j) < x) {
            ++i;
            swap(*(begin + i), *(begin + j));
        }
        else if (*(begin + j) == x && j != (end - begin - 1)) {
            swap(*(begin + j), *(end - 1));
            --j;
        }
    }
    ++i;
    swap(*(begin + i), *(end - 1));
    return i;
}

//���ص�iС��Ԫ��,Ҫ������Ԫ�ػ��죬������ʱ�临�Ӷ�Ϊ����
int Select(int * const begin, int * const end, int k) {
    if (end - begin == 1)
        return *begin;
    int n = end - begin;
    int groupnum = n / 5; //groupnum���飬ÿ�������
    int medium[10000]; //��С��50000����

    int i, j, t = groupnum;
    for (i = 0, j = 0; t--; i += 5) {
        InsertionSort(begin + i, begin + i + 5);
        medium[j++] = *(begin + i + 2);
    }
    if (n > (groupnum * 5)) {
        InsertionSort(begin + i, end);
        medium[j++] = *(begin + i + (end - begin - i) / 2);
    }

    int x = Select(medium, medium + j, (j + 1) / 2);
    int m = Partition(begin, end, x) + 1;
    if (m == k)
        return x;
    else if (m > k)
        return Select(begin, begin + m - 1, k);
    else
        return Select(begin + m, end, k - m);
}

int main(void) {
    int a[100000] = {5, 4, 3, 2, 1, 6 ,7, 8};
    int n = 8;

    cout << Select(a, a + n, 6);

    return 0;
}

