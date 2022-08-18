#include <iostream>
using namespace std;
#include <time.h>
//快排、荷兰国旗

void swap(int a[], int n1, int n2)
{
    int temp = a[n1];
    a[n1] = a[n2];
    a[n2] = temp;
}

/*
    这是一个处理a[L...R]的函数
    默认以a做划分，a[R] -> p          <p   || ==p || >p
    返回等于区域（左边界，右边界），所以返回一个长度为2的数组res, res[0],res[1]
*/
/*
    < | 3 5 6 3 4 5 2 6 9 0 | >
    |   num                 |
    less|                 more
        i
    一般的，num = L;
1)  a[i] < num, a[i]和<区的下一个数做交换, <区右扩, i++
2)  a[i] == num[i], i++
3)  a[i] > num, a[i]和>区的前一个交换, >区左扩，i原地不动
*/
void partition(int a[], int L, int R, int ret[])
{
    int less = L - 1; // <区右边界
    int more = R;     // >区左边界
    while (L < more)  // L表示当前数的位置 a[R]  -> 划分值
    {
        if (a[L] < a[R]) // 当前数 < 划分值
        {
            swap(a, ++less, L++);
        }
        else if (a[L] > a[R]) //当前数 > 划分值
        {
            swap(a, --more, L);
        }
        else
        {
            L++;
        }
    }
    swap(a, more, R);
    ret[0] = less + 1;
    ret[1] = more;

    return;
}

void quick_sort(int a[], int L, int R)
{
    if (L < R)
    {
        srand((unsigned)time(NULL));
        int random_num = L + (int)rand() % (R - L + 1);
        cout << "random_num: " << random_num << endl;
        swap(a, random_num, R); //每次将随机数与数组最后一个数交换
        int p[2] = {0};         // 划分等于区的左指针与右指针
        partition(a, L, R, p);
        quick_sort(a, L, p[0] - 1); // < 区
        quick_sort(a, p[1] + 1, R); // > 区
    }
}

void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "QuickSort, O(n*log2n)" << endl;
    int a2[10] = {5, 4, 2, 1, 6, 7, 9, 8, 10, 3};
    quick_sort(a2, 0, 9);
    display(a2, 10);
}