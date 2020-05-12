#include <iostream>
#include <vector>
using namespace std;

void Insert(vector<double> & bkt, double num) {
    for (vector<double>::iterator p = bkt.begin(); p != bkt.end(); ++p)
        if (*p > num) {
            bkt.insert(p, num);
            return ;
        }
    bkt.push_back(num); //û���ҵ����ͷ����
}

void BucketSort(double * const begin, double * const end) {  //�����������ݶ���С��[0,1)
    int n = end - begin;
    int i;
    vector<vector<double>*> bucket(n); //Ϊʲô��n��Ͱ��Ӧ�ú�hashһ��ԭ��

    for (i = 0; i < n; ++i)
        bucket[i] = new vector<double>;
    for (i = 0; i < n; ++i) { //��˳����뵽Ͱ��
        Insert(*bucket[static_cast<int>(*(begin + i) * n)], *(begin + i));
    }
    int j = 0, k = 0;
    for (i = 0; i < n; ++i) {
        while (k >= bucket[j]->size()) { //������������Ŀ�Ͱ
            ++j;
            k = 0;
        }
        *(begin + i) = (*bucket[j])[k++];
    }
    for (i = 0; i < n; ++i)
        delete bucket[i];
}

int main(void) {
    double a[100000] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n = 10;

//    cin >> n;
//    for (int i = 0; i < n; ++i)
//        cin >> a[i];

    BucketSort(a, a + n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    return 0;
}

