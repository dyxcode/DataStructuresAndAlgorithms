#include <iostream>
using namespace std;

void InsertionSort(int * const begin, int * const end) {
    int i, j;
    int key;
    for (i = 1; i < end - begin; ++i) {
        key = *(begin + i);
        for (j = i - 1; j >= 0 && (*(begin + j) > key); --j) {
            *(begin + j + 1) = *(begin + j);
        }
        *(begin + j + 1) = key;
    }
}

int main(void) {
    int a[100000];
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    InsertionSort(a, a + n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}
