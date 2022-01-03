#include<iostream>
#include<stdlib.h>
using namespace std;
#define MAX  10000
#define MAXSIZE 1000
int nums[MAX]={0};
bool visited[MAX] = {false};
int k=0;
int init_num=0,final_num=0;
int dir[10] = {9,0,1,2,3,4,5,6,7,8}; 
struct Node
{
    int s[4]={0};
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


bool function(int n)
{
    for (int i=2;i<=n-1;i++)
    {
        if (n%i==0)
            return true;
    }
    return false;
}

void sushu()
{
    for (int i=1000;i<=MAX;i++)
    {
        if (!function(i))
        {
            nums[k++]=i;
            //cout<<i<<" ";
        }
    }

    //cout<<k<<endl;
    // for (int i=0;i<=k-1;i++)
    // {
    //     cout<<nums[i]<<" ";
    // }
}

bool isIn(int n)
{
    for (int i=0;i<k-1;i++)
    {
        if (n==nums[i])
            return true;
    }
    return false;
}

void int_to_array(int n,int a[])
{
    
    for (int i=0,j=1;i<4;i++ )
    {
        a[3-i] = (n/j) % 10;
        j*=10;
    }

}

int  array_to_int(int a[])
{
    int n=0;
    for (int i=0,j=1;i<4;i++)
    {
        n = a[3-i] * j + n;
        j*=10;
    }
    return n;
}

void BFS(int num)
{
    //cout<<"BFS1"<<endl;
    Queue q;
    Node n1;
    int_to_array(num,n1.s);
    n1.step=0;
    visited[num] = true;
    q.add(n1);
    //cout<<"BFS2"<<endl;
    while (!q.isEmpty())
    {
        //cout<<"BFS3"<<endl;
        Node temp = q.getFront();
        q.del();
        if (array_to_int(temp.s)==final_num)
        {
            cout<<temp.step<<endl;
            return ;
        }
        //int minindex[4]={0};
        for (int i=0;i<=3;i++) //找最小值 0 1 2 3  1033 minindex=11
        {
            for (int j=0;j<10;j++)
            {
                Node son = temp;
                //cout<<"BFS4"<<endl;
                son.s[i] = (temp.s[i]+dir[j])%10;
                int a = array_to_int(son.s);
                if (a>=1000&&visited[a]==false&&isIn(a))
                {
                    
                    visited[a]=true;
                    //Node son = temp;1
                    son.step  = temp.step+1;
                    if (a==final_num)
                    {
                        cout<<son.step<<endl;
                        return ;
                    }
                    //cout<<"BFS4"<<endl;
                    //cout<<a<<" "<<son.step<<" "<<q.getSize()<<endl;
                    q.add(son);
                }
            }
            
        }
       
    }
    return ;
}

int main()
{
    int t=0;
    cin>>t;
    sushu();
    while (t--)
    {
        for (int i=0;i<MAX;i++)
            visited[i] = false;
        init_num=0,final_num=0;
        cin>>init_num>>final_num; 
        BFS(init_num);
    }

    return 0;
}

/*
Sample Input
3
1033 8179
1373 8017
1033 1033

Sample Output
6
7
0
*/