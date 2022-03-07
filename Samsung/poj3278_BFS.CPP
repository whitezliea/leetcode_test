/*
题意：就是给出a和b点的横坐标，求到a，b的最小行动次数，
每次可以向左或向右移动一步，即横坐标加1或者减1，也可以横坐标变成原来的两倍。
*/
#include<iostream>
#include<stdlib.h>
using namespace std;
int a=0,b=0;
bool visited[10000] = {false};
#define MAXSIZE 200
struct Node
{
    int nums=0;
    int step=0;
};

class Queue
{
private:
    struct Node data[MAXSIZE];
    int rear;
    int front;
    int size;
public:
    Queue()
    {
        rear = -1;
        front = -1;
        size = 0;
    }
    void add(Node n)
    {
        if (isFull())
            exit(-1);
        rear ++;
        rear %= MAXSIZE;
        size++;
        data[rear] = n ;
    }
    Node del()
    {
        if (isEmpty())
            exit(-1);
        front ++ ;
        front %= MAXSIZE;
        size--;
        return data[front];
    }
    bool isEmpty()
    {
        return size  == 0;
    }
    bool isFull()
    {
        return  size == MAXSIZE;
    }
    Node getFront()
    {
        int index = front+1;
        return data[index];
    }
    int getSize()
    {
        return size;
    }
   
};


void BFS(Node n)
{
    Queue q;
    n.step=0;
    q.add(n);
    while (!q.isEmpty())
    {
        Node temp = q.getFront();
        cout<<temp.nums<<" "<<q.getSize()<<" "<<temp.step<<endl;
        q.del();
        
        //结束条件
        if (temp.nums == b)
        {
            cout<<temp.step<<endl;
            return ;
        }
        if (temp.nums>=0&&temp.nums<=b&&visited[temp.nums]==false)
        {
        
        Node n2;
        visited[temp.nums]=true;
        n2.step = temp.step+1;
        //向左走一步
        n2.nums = temp.nums-1;
        q.add(n2);

        //向右走一步
        n2.nums=temp.nums+1;
        q.add(n2);

        
        //两倍路数
        n2.nums = temp.nums * 2;
        q.add(n2);
        }
    }
    return; 
}

int main()
{
    cin>>a>>b;
    Node n1;
    n1.nums = a;
    BFS(n1);
    return 0;
}