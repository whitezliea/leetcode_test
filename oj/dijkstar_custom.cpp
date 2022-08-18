#include <iostream>
#define V 9 //定义顶点数
#define INF 9999
using namespace std;

void dijkstra(int graph[V][V], int src)
{
    //创建最短路径数组dist[]，以及顶点访问数组visited[]和最短路径数组path[]
    int dist[V];
    bool visited[V];
    int path[V];

    //初始化
    for (int i = 0; i < V; i++)
    {
        dist[i] = graph[src][i];
        visited[i] = false; //未被访问
        if (graph[src][i] < INF)
            path[i] = src; //顶点src能够到达i时，i的前一个顶点为src
        else
            path[i] = -1; //顶点src无法到达i时，i的前一个顶点为-1
    }

    // base case
    dist[src] = 0;
    path[src] = 0;
    visited[src] = true;

    //开始检索
    for (int i = 0; i < V; i++) //循环直到所有顶点的最短路径都求出
    {
        int MINdist = INF;
        int index = 0;
        for (int j = 0; j < V; j++) //选取还未被访问的且具有最小最短路径长度的相邻顶点index
        {
            if (visited[j] == false && dist[j] < MINdist)
            {
                index = j;
                MINdist = dist[j];
            }
        }

        visited[index] = true; //将顶点index置为访问

        for (int j = 0; j < V; j++)
        {
            if (visited[j] == false)
            {
                if (graph[index][j] < INF && dist[index] + graph[index][j] < dist[j])
                {
                    dist[j] = dist[index] + graph[index][j];
                    path[j] = index;
                }
            }
        }
    }

    //输出dist
    cout << "i to src dist" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << "        " << dist[i] << endl;
    }
    //输出path
    cout << "i to src path" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << "        " << path[i] << endl;
    }
    return;
}

int main()
{
    /* Let us create the example graph discussed above */
    //邻接矩阵
    int graph[V][V] = {{0, 4, INF, INF, INF, INF, INF, 8, INF},
                       {4, 0, 8, INF, INF, INF, INF, 11, INF},
                       {INF, 8, 0, 7, INF, 4, INF, INF, 2},
                       {INF, INF, 7, 0, 9, 14, INF, INF, INF},
                       {INF, INF, INF, 9, 0, 10, INF, INF, INF},
                       {INF, INF, 4, 14, 10, 0, 2, INF, INF},
                       {INF, INF, INF, INF, INF, 2, 0, 1, 6},
                       {8, 11, INF, INF, INF, INF, 1, 0, 7},
                       {INF, INF, 2, INF, INF, INF, 6, 7, 0}};
    dijkstra(graph, 0);
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
i to src path
0        0
1        0
2        1
3        2
4        5
5        6
6        7
7        0
8        2
*/