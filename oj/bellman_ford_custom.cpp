#include <iostream>
#define V 9
#define INF 9999
using namespace std;

void bellman_ford(int graph[V][V], int src)
{
    int dist[V]; // i到各个点的距离
    //初始化
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
    }
    // base case
    dist[src] = 0;

    // bellman_ford
    for (int k = 0; k < V - 1; k++) //因为dist[src]已经确定，所以还需要循环V-1次
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
            {
                if (graph[i][j] != INF && graph[i][j] != 0)
                {
                    int start = i;
                    int dst = j;
                    int weight = graph[i][j];
                    if (dist[start] != INT_MAX && dist[start] + weight < dist[dst])
                        dist[dst] = dist[start] + weight;
                }
            }

    //输出dist
    cout << "i to src dist" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << "        " << dist[i] << endl;
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
    cout << "bellman_ford" << endl;
    bellman_ford(graph, 0);
    return 0;
}
/*
bellman_ford
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