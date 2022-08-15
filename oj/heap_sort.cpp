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

// 某个数在index位置，能否往下移动
void heapify(int a[],int index,int heapSize)
{
    int left = index * 2 + 1; //左孩子的下标
    while (left < heapSize) //下方还有孩子时
    {
        // 两个孩子中，谁的值大，把下表给largest
        int largest = left + 1 < heapSize && a[left + 1] > a[left] 
                        ? left + 1 : left;
        
        // 父和孩子之间比较，谁的值大，把下标给largest
        largest = a[largest] > a[index] ? largest : index;
        if (largest == index)   // 已经是最大的，无需交换
        {
            break;
        }
        swap(a, largest, index); //与子节点交换
        index = largest;
        left = index * 2 + 1;   //重新heapify
    }
}

void heap_sort(int a[],int n)
{
    if (a == nullptr || n<2)
        return;
    
    for (int i = 0; i < n; i++) // O(N)
    {
        heapInsert(a,i);    // O(logN)
    }
    int heapSize = n;
    swap(a,0,--heapSize);
    while (heapSize > 0)    //O(N)
    {
        heapify(a, 0, heapSize);    //O(logN)
        swap(a, 0, --heapSize);     //O(1)
    }
    return ;
}

void display(int a[],int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    cout<<"HeapSort, O(N*logN)"<<endl;
    int a2[10] = {5,4,2,1,6,7,9,8,10,3};
    heap_sort(a2,10);
    display(a2,10);
}
