#include <iostream>
#include <vector>
using namespace std;

int PickDigitOn_i(int n, const int i) {
    for (int k = 1; k <= i; ++k)
        n /= 10;
    return n % 10;
}

void stablesort_onDigit_i(int * const begin, int * const end, int d) { //使用计数排序作为稳定排序
    int temp[10] = {0}; //十进制数
    vector<int> out(end - begin);

    for (int i = 0; i < end - begin; ++i)
        ++temp[PickDigitOn_i(*(begin + i), d)];
    for (int i = 1; i < 10; ++i)
        temp[i] += temp[i-1];
    for (int i = end - begin - 1; i >= 0; --i) {
        out[temp[PickDigitOn_i(*(begin + i), d)] - 1] = *(begin + i);
        --temp[PickDigitOn_i(*(begin + i), d)];
    }
    for (int i = 0; i < end - begin; ++i)
        *(begin + i) = out[i];
}

void RadixSort(int * const begin, int * const end) { //假设三位数的排序
    for (int i = 0; i < 3; ++i) {
        stablesort_onDigit_i(begin, end, i);
    }
}

int main(void) {
    int a[100000];
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    RadixSort(a, a + n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}
