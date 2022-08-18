#include <iostream>
using namespace std;

void merge_sort(int a[], int n);
void process_(int a[], int L, int R);
void merge(int a[], int L, int M, int R);

void merge_sort(int a[], int n)
{
    if (a == NULL || n < 2)
        return;
    process_(a, 0, n - 1);
}

void process_(int a[], int L, int R)
{
    if (L == R)
        return;
    int mid = L + (R - L) / 2;
    process_(a, L, mid);
    process_(a, mid + 1, R);
    merge(a, L, mid, R);
}

void merge(int a[], int L, int M, int R)
{
    int *help = new int[R - L + 1];
    int i = 0;
    int p1 = L;
    int p2 = M + 1;
    /*    _____ ______
         |_____|______|
         |      |     |
         p1  p2(M+1)  R
        每次比较都是a[p1]与a[p2]进行比较，谁小就先塞入help数组中，然后指针向右移动
    */
    while (p1 <= M && p2 <= R)
    {
        help[i++] = a[p1] <= a[p2] ? a[p1++] : a[p2++];
    }
    /*
        p1与p2指针总有一个先越界，然后就可以将另外一个未越界的区域全部加入help数组中
    */
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
    delete[] help;
}

int main()
{
    int a[6] = {1, 5, 3, 6, 4, 2};
    merge_sort(a, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}