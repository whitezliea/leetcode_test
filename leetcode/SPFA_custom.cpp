#include<iostream>
#define V 9
#define INF 9999
#define MAXSIZE 100
using namespace std;

struct Node
{
    int id;
};


class Queue
{
private:
    Node data[MAXSIZE];
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
    void add(Node a)
    {
        if (isFull())
            return ;
        rear++;
        rear %= MAXSIZE;
        size++;
        data[rear] = a;
    }
    void del()
    {
        if(isEmpty())
            return ;
        front++;
        front %= MAXSIZE;
        size--;
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
    bool isEmpty()
    {
        return size == 0;
    }
    bool isFull()
    {
        return size == MAXSIZE;
    }
};

void shortestPathFaster(int graph[V][V],int src)
{
    int dist[V]; //i到各个点的距离
    bool inQueue[V] = {false}; //各个点是否在队列中
    //初始化 
    for (int i =0;i<V;i++)
    {
        dist[i] = INF;
    }
    //base case
    dist[src] = 0;

    Queue q;
    Node start;
    start.id = src;
    q.add(start);
    inQueue[start.id] = true;

    //BFS
    while (!q.isEmpty())
    {
        Node temp = q.getFront();
        q.del();
        inQueue[temp.id] = false;
        
        for (int i = 0; i < V ; i++)
        {
            if (graph[temp.id][i] != INF && graph[temp.id][i] != 0)
            {
                int next = i;
                int weight = graph[temp.id][i];

                if (dist[next] > dist[temp.id] + weight)
                {
                    dist[next] = dist[temp.id] + weight;

                    if (inQueue[next] == false)
                    {
                        Node next_node;
                        next_node.id = next;
                        q.add(next_node);
                        inQueue[next] = true;
                    }
                }
            }
        }

    }

    //输出dist
    cout<<"i to src dist"<<endl;
    for (int i=0;i<V;i++)
    {
        cout<<i<<"        "<<dist[i]<<endl;
    }

    return ;
    
}

int main()
{
    /* Let us create the example graph discussed above */
    //邻接矩阵
    int graph[V][V] = { { 0, 4, INF, INF, INF, INF, INF, 8, INF },
                        { 4, 0, 8, INF, INF, INF, INF, 11, INF },
                        { INF, 8, 0, 7, INF, 4, INF, INF, 2 },
                        { INF, INF, 7, 0, 9, 14, INF, INF, INF },
                        { INF, INF, INF, 9, 0, 10, INF, INF, INF },
                        { INF, INF, 4, 14, 10, 0, 2, INF, INF },
                        { INF, INF, INF, INF, INF, 2, 0, 1, 6 },
                        { 8, 11, INF, INF, INF, INF, 1, 0, 7 },
                        { INF, INF, 2, INF, INF, INF, 6, 7, 0 } };

    shortestPathFaster(graph,0);
    return 0;
}
/*
i to src dist
0        0
1        4
2        12
3        19
4        21
5        11
6        9
7        8
8        14
*/