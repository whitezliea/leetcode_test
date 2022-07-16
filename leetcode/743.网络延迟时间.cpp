/*
 * @lc app=leetcode.cn id=743 lang=cpp
 *
 * [743] 网络延迟时间
 */

// @lc code=start
#include<vector>
#define INF 9999
#define MAXSIZE 200
#include<queue>
using namespace std;
struct Node
{
    int id=0;
    int cost=0;
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
        front=-1;
        size=0;
    }
    void add(Node a)
    {
        if (isFull())
            return;
        rear++;
        rear %= MAXSIZE;
        size++;
        data[rear] = a;
        
    }
    void del()
    {
        if (isEmpty())
            return;
        front++;
        front %= MAXSIZE;
        size--;
    }
    Node getFront()
    {
        int index = front+1;
        return data[index];
    }
    bool isEmpty()
    {
        return size == 0;
    }
    bool isFull()
    {
        return size==MAXSIZE;
    }

    
};


class Solution {
public:
    /*解法1：优先级队列
    void dijstar_pq(vector<vector<int>>& times, int n, int src,int dist[])
    {
  
        Node s;
        s.id = src;
        s.cost = 0;
        dist[src] = 0;
        
        //Queue q;
        queue<Node>q;
        q.push(s);
        while (!q.empty())
        {
            Node cur = q.front();
            q.pop();
            int cur_id = cur.id;
            int cur_cost = cur.cost;

            //剪枝操作，优化效率
            if (cur_cost > dist[cur_id])
            {
                continue;
            }
            for (int i=0;i<times.size();i++)
            {
                if (cur_id==times[i][0])
                {
                    int next_id = times[i][1];
                    int weight = times[i][2];
                    if (dist[next_id] > dist[cur_id]+ weight)
                    {
                        dist[next_id] = dist[cur_id] + weight;
                        Node nexts;
                        nexts.id = next_id;
                        nexts.cost = dist[cur_id] + weight;
                        q.push(nexts);
                    }
                }
            }
        }

        return ;
        

    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        int *dist = new int[n+1];
        //初始化
        for (int i=1;i<=n;i++)
        {
            dist[i] = INF;
        }
        dijstar_pq(times,n,k,dist);
        int res=0;
        for (int i=1;i<=n;i++)
        {
            if(dist[i] == INF)
                return -1;
            res = res > dist[i] ? res :dist[i];
        }

        return res;
    }
    */
    int dijkstar(vector<vector<int>>& times, int n, int src,int **map)
    {
        bool *vis = new bool[n+1];
        int *dist = new int [n+1];
        for (int i=0;i<=n;i++)
        {
            dist[i] = INF;
            vis[i] = false;
        }
       
        for (int i=1;i<=n;i++)
        {
            dist[i] = map[src][i];
        }
        //base case
        dist[src] = 0;
        vis[src] = true;

        for (int i=0;i<n-1;i++)
        {
            int MINdist = INF;
            int next = 0;
            for (int j=1;j<=n;j++)
            {
                if (vis[j]==false&&dist[j] < MINdist)
                {
                    MINdist = dist[j];
                    next = j;
                }
            }
            vis[next] = true;
            for (int k=1;k<=n;k++)
            {
                if (vis[k]==false)
                {
                    if (map[next][k] < INF && 
                    dist[k] > dist[next] + map[next][k])
                    {
                        dist[k] = dist[next]+ map[next][k];
                    }
                }
            }

        }
        int res = 0;
        for (int i=1;i<=n;i++)
        {
            if (dist[i]==INF)
                return -1;
            res = res > dist[i] ? res : dist[i];
        }
        return res;

    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        
        int **map = new int*[n+1];
        for (int i=0;i<=n;i++)
        {
            map[i] = new int [n+1];
        }
        for (int i=0;i<=n;i++)
            for (int j=0;j<=n;j++)
                map[i][j] = INF;
        //转换成邻接表
        for (int i=0;i<times.size();i++)
        {
            int from = times[i][0];
            int to = times[i][1];
            int weight = times[i][2];
            map[from][to] = weight;
        }
        return dijkstar(times,n,k,map);
    }
};
// @lc code=end

