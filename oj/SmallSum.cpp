#include <iostream>
using namespace std;

/*
小数问题：
在一个数组中，每一个数的左边比当前数小的数累加起来，
叫做这个数组的小和，求一个数组的小和
smaple input:
1 3 4 2 5
output 16
*/
int SmallSum(int a[], int n);
int process_(int a[], int L, int R);
int merge(int a[], int L, int M, int R);

int SmallSum(int a[], int n)
{
    if (a == NULL || n < 2)
        return 0;
    return process_(a, 0, n - 1);
}

//在a[L...R]既要排好序，也要求小和
int process_(int a[], int L, int R)
{
    if (L == R)
        return 0;

    int mid = L + (R - L) / 2;

    return process_(a, L, mid) + process_(a, mid + 1, R) + merge(a, L, mid, R);
}

int merge(int a[], int L, int M, int R)
{
    int *help = new int[R - L + 1];
    int i = 0;
    int p1 = L;
    int p2 = M + 1;
    int res = 0;
    while (p1 <= M && p2 <= R)
    {
        res += a[p1] < a[p2] ? (R - p2 + 1) * a[p1] : 0; //求小和问题的关键
        help[i++] = a[p1] < a[p2] ? a[p1++] : a[p2++];   //排序
    }
    while (p1 <= M)
    {
        help[i++] = a[p1++];
    }
    while (p2 <= R)
    {
        help[i++] = a[p2++];
    }
    for (int i = 0; i < R - L + 1; i++)
    {
        a[L + i] = help[i];
    }

    return res;
}

int main()
{
    int a[5] = {1, 3, 4, 2, 5};
    int sum = SmallSum(a, 5);
    cout << sum << endl;
    cout << "hello world!" << endl;
    return 0;
}