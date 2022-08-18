#include <iostream>
using namespace std;

int process_(int a[], int L, int R)
{
    if (L == R)
    {
        return a[L];
    }

    int mid = L + ((R - L) / 2); //中点
    int LeftMax = process_(a, L, mid);
    int RightMax = process_(a, mid + 1, R);
    int max_num = LeftMax > RightMax ? LeftMax : RightMax;
    return max_num;
}

int getMax(int a[], int n)
{
    return process_(a, 0, n - 1);
}

int main()
{
    int a[5] = {1, 3, 4, 5, 2};
    int num = getMax(a, 5);
    cout << num << endl;
    return 0;
}