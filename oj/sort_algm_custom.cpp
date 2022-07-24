#include<iostream>
using namespace std;
void display(int a[],int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
//常用的算法
//1.冒泡算法
void BubbleSort(int a[],int n)
{
    for (int i=0;i<n-1;i++)
    {
        for (int j=n-1;j>i;j--)
        {
            if (a[j] < a[j-1])
            {
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
    return ;
}
//2.快速排序
int partition(int a[],int s,int t)
{
    int i=s, j =t;
    int temp = a[i];  //每次都拿a[]数组第一个数作为基准
    while (i<j)
    {
        while (j>i&&a[j]>=temp) //以temp为基准，找到一个temp右边小于temp的数
            j--;
        a[i] = a[j];
        while (j>i&&a[i]<=temp) //以temp为基准，找到一个temp左边大于temp的数
            i++;
        a[j] = a[i];
    }
    a[i] = temp;
    return i;
}
void QuickSort(int a[],int s,int t)
{
    int i;
    if (s<t)
    {
        i = partition(a,s,t);
        QuickSort(a,s,i-1);
        QuickSort(a,i+1,t);
    }
}
//3.选择排序
void SelectSort(int a[],int n)
{
 
    for (int i=0;i<n-1;i++)
    {
        int k = i;
        for (int j=i+1;j<n;j++)
        {
            if (a[j]<a[k])
                k = j;
        }
        if (k!=i)
        {
            int temp = a[k];
            a[k] = a[i];
            a[i] = temp;
        }
    }
    return ;
}
//4.归并排序

//5.1 直接插入排序
void InsertSort(int a[],int n)
{
    for (int i=1;i<n;i++)
    {
        if (a[i] <a[i-1])
        {
            int temp = a[i];
            int j = i-1;
            do 
            {
                a[j+1] = a[j];
                j--;
            }while (j>=0&&a[j]>temp);
            a[j+1] = temp;

        }
    }
}
//5.2 折半插入排序


int main()
{
    int n=10;
    int a[n] = {5,4,2,1,6,7,9,8,10,3};
    cout<<"init data"<<endl;
    display(a,n);

    //直接插入排序
    cout<<"insertSort, O(n^2)"<<endl;
    int a5_1[n] = {5,4,2,1,6,7,9,8,10,3};
    InsertSort(a5_1,n);
    display(a5_1,n);

    //冒泡排序
    cout<<"BubbleSort, O(n^2)"<<endl;
    int a1[n] = {5,4,2,1,6,7,9,8,10,3};
    BubbleSort(a1,n);
    display(a1,n);

    //快速排序
    cout<<"QuickSort, O(n*log2n)"<<endl;
    int a2[n] = {5,4,2,1,6,7,9,8,10,3};
    QuickSort(a2,0,n-1);
    display(a2,n);

    //选择排序
    cout<<"SelectSort, O(n^2)"<<endl;
    int a3[n] = {5,4,2,1,6,7,9,8,10,3};
    SelectSort(a3,n);
    display(a3,n);

    return 0;
}
/*
init data
5 4 2 1 6 7 9 8 10 3
insertSort, O(n^2)
1 2 3 4 5 6 7 8 9 10
BubbleSort, O(n^2)
1 2 3 4 5 6 7 8 9 10
QuickSort, O(n*log2n)
1 2 3 4 5 6 7 8 9 10
SelectSort, O(n^2)
1 2 3 4 5 6 7 8 9 10
*/