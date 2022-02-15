
/*
 * @lc app=leetcode.cn id=1514 lang=cpp
 *
 * [1514] 概率最大的路径
 */

 // @lc code=start
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
struct Node
{
    int id = 0;
    double cost = 0;
    friend bool operator < (Node a, Node b)    
    {    
        return a.cost < b.cost;    //重载大于号使得大的先出队列    
    }  
};

class Solution {
public:

    double dijkstar_pq(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end, double dist[],double **maps)
    {
        Node src;
        src.id = start;
        src.cost = 1;
        // base case，start 到 start 的概率就是 1
        dist[start] = 1;

        priority_queue<Node> q;
        q.push(src);
        while (!q.empty())
        {
            Node cur = q.top();
            q.pop();
            int cur_id = cur.id;
            double cur_cost = cur.cost;
            // 遇到终点提前返回
            if (cur_id == end) 
            {
                return cur_cost;
            }
        
            if (cur_cost < dist[cur_id]) {
                // 已经有一条概率更大的路径到达 curNode 节点了
                continue;
            }            
            for (int i = 0; i < n; i++)
            {
                for  (int j = 0;j<n; j++)
                {
                    if (cur_id == i && maps[i][j]>=0)
                    {
                        //cout << "test " << endl;
                        int next_id = j;
                        double weight = maps[i][j];
                        double dist_nextnode = dist[cur_id] * weight;
                        if (dist[next_id] < dist_nextnode)
                        {
                            dist[next_id] = dist_nextnode;
                            Node nexts;
                            nexts.id = next_id;
                            nexts.cost = dist_nextnode;
                            q.push(nexts);
                        }
                    }
                }

            }
        }

        return 0.0;
    }

    double dijkstar(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end, double dist[],double **maps)
    {
        int INF = -1;
        bool *vis = new bool [n];
        for (int i=0;i<n;i++)
        {
            vis[i] = false;
            dist[i] = maps[start][i];
        }
        
        //base case
        dist[start] = 1.00;
        vis[start] = true;

        for (int i=0;i<n-1;i++)
        {
            double MAXdist = INF;
            int next = 0;
            for (int j=0;j<n;j++)
            {
                if (vis[j]==false&&dist[j]>MAXdist)
                {
                    MAXdist = dist[j];
                    next = j;
                }
                vis[next] = true;
                for (int k=0;k<n;k++)
                {   
                    if (vis[k]==false)
                    {
                        if (maps[next][k] > 0 
                        && dist[k] < dist[next] * maps[next][k])
                            dist[k] = dist[next] * maps[next][k];
                    }
                }
            }
        }
        
        double res = dist[end] > 0 ? dist[end]:0.00;
        return res;
    }
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        //首先定义一个dist数组
        double* dist = new double[n];
        //初始化
        for (int i = 0; i < n; i++)
        {
            dist[i] = -1;
        }

        double** maps = new double* [n];
        for (int i = 0; i < n; i++)
        {
            maps[i] = new double[n];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                maps[i][j] = -1;
            }
            
        }


        for (int i = 0; i < edges.size(); i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];
            double weight = succProb[i];
            maps[from][to] = weight;
            maps[to][from] = weight;
        }

        //return 0.0;
        return dijkstar(n, edges, succProb, start, end, dist, maps);
        return dijkstar_pq(n, edges, succProb, start, end, dist, maps);
    }
};
// @lc code=end
//运行超时，需要将邻接矩阵换成邻接表


