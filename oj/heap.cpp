#include<iostream>
using namespace std;
/*
 i  0 1 2 3 4 5 6
num 3 5 2 7 1 9 6
           3
          / \
        5     2
      / \     / \
     7   1   9   6
堆(heap)是一种满二叉树，分为大根堆和小根堆
物理含义上，堆可以连续放在一起，但逻辑含义上有
对于索引i，其
父索引为  (i-1)/2     
左子索引为 2*i+1
右子索引为 2*i+2
*/
void swap(int a[],int n1,int n2)
{
    int temp = a[n1];
    a[n1] = a[n2];
    a[n2] = temp;
}

void heapInsert(int a[],int index)
{
    while(a[index] > a[(index - 1) / 2])
    {
        swap(a, index, (index - 1) / 2);  // 与父节点进行交换
        index = (index - 1) / 2;
    }
}

