#include<iostream>
#include<stdlib.h>
using namespace std;
int nums=0;
#define MAXSIZE 200
int s[100]={1};
long long int maxnums = 0;
int n=0;

struct Node
{
    int s1[50]={0};
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

long long int math_s(int n) 
{
    long long int ten=2;
    if (n==0)
    {
        return 1; 
    }
    else
    {
    for (int i=1;i<=n-1;i++)
        ten = 2 * ten;
    }
    return ten;
}

bool isOK(Node n)
{
    int max = 0;
    for (int i=n.step;i>=1;i--)
    {
        max += math_s(n.step-i)*n.s1[i] ;
    }
    if (max%nums == 0 && n.step >= nums)
    {
        maxnums = max;
        return true;
    }

    return false;
}

void show(Node t)
{
    for (int i=1;i<=t.step;i++)
        cout<<t.s1[i]<<" ";
    cout<<t.step;
    
}


void BFS()
{
    Queue q;
    Node n1;
    n1.step=1;
    n1.s1[1]=1;
    q.add(n1);
    while (!q.isEmpty())
    {
        Node temp = q.getFront();
        q.del();
        show(temp);
        cout<<" size:"<<q.getSize()<<endl;
        if (temp.step >= 1)
        {
            if (isOK(temp))
            {
                cout<<"answer: "<<maxnums<<endl;
                return ;
            }
        }

        Node n=temp;
        n.step=temp.step+1;
        int k = n.step;
        n.s1[k] = 1;
        q.add(n);

        n.s1[k] = 0;
        q.add(n);
        
    }
    
    return ;
}

int main()
{
    while (1)
    {
        nums = 0 ;
        cin>>nums;
        if (nums == 0)
            break;
        BFS();
    }
    return 0;
}

/*
Sample Input

2
6
19
0
Sample Output

10
100100100100100100
111111111111111111
*/