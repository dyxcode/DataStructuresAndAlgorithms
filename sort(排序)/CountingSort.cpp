#include <iostream>
#include <vector>
using namespace std;
//计数排序期望输入数据都是小区间内的整数
void CountingSort(int * const begin, int * const end) {
    vector<int> temp(10000); //假设输入值小于10000
    vector<int> out(end - begin);

    for (int i = 0; i < end - begin; ++i)
        ++temp[*(begin + i)];
    for (int i = 1; i < 10000; ++i)
        temp[i] += temp[i-1];
    for (int i = end - begin - 1; i >= 0; --i) {
        out[temp[*(begin + i)] - 1] = *(begin + i);
        --temp[*(begin + i)];
    }
    for (int i = 0; i < end - begin; ++i)
        *(begin + i) = out[i];
}

int main(void) {
    int a[100000] = {1, 4, 2, 3, 5};
    int n = 5;

    CountingSort(a, a + n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}

