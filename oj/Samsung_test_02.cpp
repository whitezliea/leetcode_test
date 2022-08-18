/* ↑↓→←
题目要求：
给你十组数字
一组数字，例如1 2 2 3 3 4 4 1 4 5
表示下图有向图：
1←--4--→5
↓   ↑
2--→3
需要打印所有的成环路径

思路：先把输入的信息转换成邻接表
通过邻表来找环

*/
#include <vector>
#include <iostream>
using namespace std;
const int N = 100000;

vector<int> graph[N];
vector<int> cycles[N];

void dfs_find_cycle(int u, int p, int color[], int mark[], int par[], int &cyclenumber)
{

    if (color[u] == 2)
    {
        return;
    }

    if (color[u] == 1)
    {
        cyclenumber++;
        int cur = p;
        mark[cur] = cyclenumber;

        while (cur != u)
        {
            cur = par[cur];
            mark[cur] = cyclenumber;
        }

        return;
    }

    par[u] = p;

    color[u] = 1; //被访问第一次

    for (int v : graph[u])
    {
        //不走回头路
        if (v == par[u])
            continue;

        dfs_find_cycle(v, u, color, mark, par, cyclenumber);
    }

    color[u] = 2; //被访问第二次
}

// undirected graph
void addEdge(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void print_Cycles(int edges, int mark[], int &cyclenumber)
{

    for (int i = 1; i <= edges; i++)
    {
        if (mark[i] != 0)
            cycles[mark[i]].push_back(i);
    }

    for (int i = 1; i <= cyclenumber; i++)
    {
        cout << "Cycle Number" << i << ": ";
        for (int x : cycles[i])
        {
            cout << x << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "hello world1!" << endl;

    // add edges
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 6);
    addEdge(4, 7);
    addEdge(5, 6);
    addEdge(3, 5);
    addEdge(7, 8);
    addEdge(6, 10);
    addEdge(5, 9);
    addEdge(10, 11);
    addEdge(11, 12);
    addEdge(11, 13);
    addEdge(12, 13);

    addEdge(9, 10);
    addEdge(10, 9);
    // arrays required to color the
    // graph, store the parent of node
    int color[N]; //三种颜色 0,1,2
    int par[N];

    // mark with unique numbers
    int mark[N];

    // store the numbers of cycle
    int cyclenumber = 0;
    int edges = 13;

    // call DFS to mark the cycles
    dfs_find_cycle(1, 0, color, mark, par, cyclenumber);

    // function to print the cycles
    print_Cycles(edges, mark, cyclenumber);

    return 0;
};
