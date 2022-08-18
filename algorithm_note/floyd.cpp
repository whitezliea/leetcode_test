#include <iostream>
#define V 9
#define INF 9999
using namespace std;

void display(int array[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd(int graph[V][V])
{
    int A[V][V];    // A[i][j]的含义是i到j的最短路径距离
    int path[V][V]; // path[i][j]的含义是i到j的前一个顶点

    //初始化
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            A[i][j] = graph[i][j];
            if (i != j && graph[i][j] < INF)
            {
                path[i][j] = i; // path[i][j]的含义是i到j的前一个顶点为i
            }
            else
            {
                path[i][j] = -1; // i与j没有边
            }
        }
    }

    //动态转移方程
    for (int k = 0; k < V; k++) //遍历0~V个点
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (A[i][j] > A[i][k] + A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    cout << "-------A------" << endl;
    display(A);
    cout << "-------path------" << endl;
    display(path);
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
    floyd(graph);
    return 0;
}
/*
-------A------
0 4 12 19 21 11 9 8 14
4 0 8 15 22 12 12 11 10
12 8 0 7 14 4 6 7 2
19 15 7 0 9 11 13 14 9
21 22 14 9 0 10 12 13 16
11 12 4 11 10 0 2 3 6
9 12 6 13 12 2 0 1 6
8 11 7 14 13 3 1 0 7
14 10 2 9 16 6 6 7 0
-------path------
-1 0 1 2 5 6 7 0 2
1 -1 1 2 5 2 7 1 2
1 2 -1 2 5 2 5 6 2
1 2 3 -1 3 2 5 6 2
7 2 5 4 -1 4 5 6 2
7 2 5 2 5 -1 5 6 2
7 7 5 2 5 6 -1 6 6
7 7 5 2 5 6 7 -1 7
1 2 8 2 5 2 8 8 -1

*/