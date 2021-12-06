/*
点的数字随便标
主要是点数v和边数e
然后输入9条边连接的两个点
每个点只能填黑或白2种颜色
要求一条边连接的两个点不同色
所有点填上颜色，输出#+测试案例号+白色的点总数+每个白色点的号码
每个测试案例其实有至少两种情况，黑白一换也是符合要求的，都给过。
无法按要求填满两色的案例输出-1
*/

/*
case 1:
input:
1---2---3
|  /|  /
| 5 | 7
|/  |/
4---6
v e
6 9 1 2 1 4 2 3 2 5 2 6 3 7 4 5 4 6 6 7 
*/
#include<iostream>
#include<stdlib.h>
#include<malloc.h>
using namespace std;
int edge[100]={0};
//int node[50]={0};
//bool iswhite[50]={false};
int v=0,e=0;
int count=0;
struct Node
{
    int i =0;
    bool iswhite = false;
}node[50];


#define Queue_MAXSIZE 20
class Queue
{
private:
    struct Node data[Queue_MAXSIZE]; //存储数据
    int front;//队首指针
    int rear; //队尾指针
    int size; //队列大小
public:
    Queue();
    void addQueue(Node a);
    Node delQueue();
    Node getFront();
    bool isFull();
    bool isEmpty();
    int getSize();
};

Queue::Queue()
{
    front = -1;
    rear = -1;
    size = 0;
}

void Queue::addQueue(Node a)
{
    if (isFull())
    {
        exit(-1);
    }
    rear++;
    rear %= Queue_MAXSIZE;
    size++;
    data[rear] = a;
}
Node Queue::delQueue()
{
    if (isEmpty())
    {
        exit(-1);
    }
    front++;
    front %= Queue_MAXSIZE;
    size--;
    return data[front];
}

Node Queue::getFront()
{
    int index = front + 1;
    return data[index];
}

bool Queue::isFull()
{
    return size == Queue_MAXSIZE;
}
bool Queue::isEmpty()
{
    return size == 0;
}
int Queue::getSize()
{
    return size;
}

void BFS(Node a)
{
    Queue q;
    a.iswhite = true;
    q.addQueue(a);
    while (!q.isEmpty())
    {
        for (int )
    }
    
}

int main()
{
    
    cin>>v>>e;
    // int **edge = (int**)malloc(sizeof(int*)*e);
    // for (int i=0;i<e;i++)
    //     edge[i] = (int*)malloc(sizeof(int)*2);
    // cout<<v<<e;
    // int *p = (int *)malloc(sizeof(int*)*(e)/2);
    // for(int i=0;i<e;i++)
    //     for(int j=0;j<2;j++)
    //         cin>>edge[i][j];

    for (int i=0;i<e*2-1;i++)
        cin>>edge[i];
    for (int i =1;i<=v;i++)
    {
        node[i].i=v;
        node[i].iswhite = false;
    }
    BFS(node[1]);
    cout<<count<<endl;
    cout<<endl;
    return 0;
}