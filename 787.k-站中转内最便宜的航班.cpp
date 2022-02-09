/*
 * @lc app=leetcode.cn id=787 lang=cpp
 *
 * [787] K 站中转内最便宜的航班
 */

// @lc code=start
#include<vector>
#include<queue>
using namespace std;
#define MAXSIZE 500
struct Node
{
    int id; //当前节点的id
    int costFromsrc;    //从src节点到当前节点的花费
    int nodeNumFromSrc; //从 src 节点到当前节点个数
    friend bool operator < (Node a, Node b)    
    {    
        return a.costFromsrc > b.costFromsrc;    //重载小于号使得小的先出队列    
    }  
};

class Queue
{
public:
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
    void addNode(Node a)
    {
        if (isFull())
            return ;
        rear ++ ;
        rear %= MAXSIZE;
        data[rear] = a;
        size ++; 
    }
    void delNode()
    {
        if (isEmpty())
            return ;
        front++;
        front %= MAXSIZE;
        size --;
    }
    Node getFront()
    {
        int index = front+1;
        return data[index];
    }
    bool isFull()
    {
        return size == MAXSIZE;
    }
    int getSize()
    {
        return size;
    }
    void sort()
    {

    }
    bool isEmpty()
    {
        return size == 0;
    }
};


class Solution {
    //flights[i] = [fromi, toi, pricei]
public:
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    //解法1：Dijkstra算法 ---> BFS+priority_queue
    //优先级队列重写仿函数
    int dijkstra(int N, vector<vector<int>>& flights, int src, int dst, int K_dij)
    {
        int n1 = flights.size();
        //定义：从起点 src 到节点i的最短路径权重为distTo[i]  ---.确定旅行费用
        int *distTo = new int[N];
        for (int i = 0;i<N;i++)
            distTo[i] = 65535;
        
        //定义：从起点 src 到达节点i至少需要经过 nodeNumTo[i] 个节点    ----> 确定飞机路线数
        int  *nodeNumTo = new int [N];
        for (int i=0;i<N;i++)
            nodeNumTo[i] = 65535;

        //base case
        distTo[src] = 0;
        nodeNumTo[src] = 0;
        
        Node start;
        start.id = src, start.costFromsrc = 0, start.nodeNumFromSrc = 0;
        //优先级队列

        //Queue q;
        priority_queue<Node> q;
        q.push(start);
        while (!q.empty())
        {  
           Node current_state = q.top();
           q.pop();
           int cur_NodeId = current_state.id;
           int cur_costFromSrc = current_state.costFromsrc;
           int cur_NodeNumFromSrc = current_state.nodeNumFromSrc;

            if(cur_NodeId == dst)
            {
                //找到最短路径
                return cur_costFromSrc; 
            }
            if (cur_NodeNumFromSrc == K_dij)
            {
                //中转次数耗尽
                continue;
            }  

            //将curNode 的相邻节点装入队列
            // formi == cur_NodeId,邻接表
            for (int i=0;i<n1;i++)
            {
                if (flights[i][0] == cur_NodeId)
                {
                    int nextNodeID = flights[i][1];
                    int costToNextNode = cur_costFromSrc + flights[i][2];
                    //中转次数消耗1
                    int nextNodeNumFromSrc = cur_NodeNumFromSrc + 1;

                    //更新队列
                    if(distTo[nextNodeID] > costToNextNode)
                    {
                        distTo[nextNodeID] = costToNextNode;
                        nodeNumTo[nextNodeID] = nextNodeNumFromSrc;
                    }

                    //剪枝，如果中转次数更多，花费更大，那必然不是最短路径
                    if(costToNextNode > distTo[nextNodeID]
                        && nextNodeNumFromSrc > nodeNumTo[nextNodeID])
                    {
                        continue;
                    }
            
                    Node next_state;
                    next_state.id = nextNodeID;
                    next_state.costFromsrc = costToNextNode;
                    next_state.nodeNumFromSrc = nextNodeNumFromSrc;

                    q.push(next_state);
                }
            }
        }
        
        return -1;
    }
    
    //解法2：动态规划/暴力回溯/带备忘录的回溯算法
    //此算法是从dst---->src 反推。
    //s为当前目的地，k为剩余飞机路线数
    int dp_memo(vector<vector<int>>& flights,int src, int s,int k,int **memo)
    {
        int n1 = flights.size();
        int n2 = flights[0].size();
        if (s==src)
            return 0;
        if (k==0)
            return -1;
        
        if (memo[s][k] != -888)
            return memo[s][k];
        
        int res = 65535;
        for (int i = 0;i<n1;i++) //遍历flight函数，找到to是dst的数组
        {
            if (flights[i][1]==s)
            {
                int from = flights[i][0];
                int price = flights[i][2];
                int SubProblem = dp_memo(flights,src,from,k-1,memo);
                if (SubProblem != -1)
                {
                    res = MATH_min(res,SubProblem+price);
                }
            }
        }

        memo[s][k] =  res == 65535 ? -1 : res;
        return memo[s][k];

    }
    
    //二维DP
    int dp(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        //k是最多可经过的中转站，k+1是需搭乘的飞机次数
        int n1 = flights.size();
        int n2 = flights[0].size();
        int T = k+1;
        //dp[t][n] = 费用 t是搭乘飞机次数，n是经过的城市编号
        int **dp = new int *[T+1];
        for (int i=0;i<T+1;i++)
            dp[i] = new int[n];
        //初始化
        for (int i=0;i<T+1;i++)
            for (int j=0;j<n;j++)
                dp[i][j] = 65535; //给定一个超大值
        
        //base case 
        dp[0][src] = 0;
        //动态转移方程
        //对于T+1次
        for (int t = 1 ;t<T+1;t++)
        {
            for (int j=0;j<n1;j++)
            {
                int from = flights[j][0];
                int to = flights[j][1];
                int price = flights[j][2];
                dp[t][to] = MATH_min(dp[t][to],dp[t-1][from]+price);
            }
        }

        int res = 65535;
        for (int t =1;t<T+1;t++)
        {
            res = MATH_min(res,dp[t][dst]);
        }

        return (res == 65535 ?-1: res);
        
    }


    //bellman ford算法
    void array_copy(int *dist,int *clone,int N)
    {
        for (int i=0;i<N;i++)
        {
            clone[i] = dist[i]; 
        }
        return ;
    }
    //N是地图有多少个点，与flight.size()关系不是很大
    int bellman_ford(int N, vector<vector<int>>& flights, int src, int dst, int k)
    {
        int INF = 65535;
        int n1 = flights.size();
        int **graphic = new int *[N];
        for (int i=0;i<N;i++)
            graphic[i] = new int [N];
        //初始化
        for (int i=0;i<N;i++)
            for (int j=0;j<N;j++)
                graphic[i][j] = i==j ? 0 : INF;
        for (int i = 0; i < n1; i++)
        {
            graphic[flights[i][0]][flights[i][1]] = flights[i][2];
        }
        
        int *dist = new int [N];
        int *clone = new int [N];
        for (int i=0;i<N;i++)
            dist[i] = INF;
        //初始化
        dist[src] = 0;
        //k是最多可经过的中转站，k+1是需搭乘的飞机次数
        //限制最多不超过k+1条边，但是注意本题中n1才是总的边数，且 k+1 < n1;
        int K = k+1; //我们应该注意到 K <= n1;
        //bellman ford算法，但是不是完整的bellman ford，不需要进行n1-1次循环
        for (int limit = 0;limit<K;limit++)  
        {
            //需要注意的是，在遍历所有的“点对/边”进行松弛操作前，
            //需要先对 distdist 进行备份，否则会出现「本次松弛操作所使用到的边，
            //也是在同一次迭代所更新的」，从而不满足边数限制的要求
            //dist[a] 是同一次迭代所更新的话，那么使用的边数将会大于K条。
            array_copy(dist,clone,N);
            for (int  i = 0; i < N; i++)
            {
                for (int j=0;j<N;j++)
                {
                    if (dist[j]>clone[i]+graphic[i][j])
                        dist[j] = clone[i] + graphic[i][j];
                }
            }
        }  

        int ans = dist[dst];
        //判断是否有answer，不一定是ans == INF ,因为会大于或者小于的情况。
        return ans > INF / 2 ? -1 : ans; 
    }

    //BFS＋剪枝
    int BFS(int n, vector<vector<int>>& flights, int src, int dst, int K_BFS)
    {
        int INF = 65535;
        //distFromSrc表示src到i的最小价格
        int *distFromSrc = new int[n];
        //初始化
        for (int i=0;i<n;i++)
            distFromSrc[i] = INF;
        
        //base case 
        distFromSrc[src] = 0;
        Node start;
        start.id = src;
        start.costFromsrc = 0;
        Queue q;
        q.addNode(start);

        //退出条件加上k的限制
        while (!q.isEmpty()&& K_BFS>0)
        {
            //sz的含义，当前队列的元素个数
            int sz = q.getSize();
            for (int j=0;j<sz;j++)
            {
                Node Cur_Node = q.getFront();
                q.delNode();
                for (int i=0;i<flights.size();i++)
                {
                    if (flights[i][0] == Cur_Node.id)
                    {
                        int dist_NextNode = flights[i][2]+Cur_Node.costFromsrc;
                        //剪枝1：小于i之前记录的最小值，且小于dst之前记录的最小值
                        if (dist_NextNode < distFromSrc[flights[i][1]]
                                &&dist_NextNode < distFromSrc[dst])
                            {       
                                distFromSrc[flights[i][1]] = dist_NextNode;
                            
                                //在剪枝1的基础上进行剪枝2：如果还未到dst，将邻接点放入队列中
                                if (flights[i][1] != dst)
                                {
                                    Node next;
                                    next.id = flights[i][1];
                                    next.costFromsrc = dist_NextNode;
                                    q.addNode(next);
                                }
                            }
                    }
                }
            }
            K_BFS--;
        }

        return distFromSrc[dst] >= INF ? -1 : distFromSrc[dst];
        
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int n1 = flights.size();
        int n2 = flights[0].size();
        //memo
        int K_memo = k;
        //经历过k个城市会经过k+1步路
        K_memo++;
        int **memo = new int*[n];
        for (int i=0;i<n;i++)
            memo[i] = new int[K_memo+1];
        for (int i=0;i<n;i++)
            for(int j=0;j<K_memo+1;j++)
                memo[i][j] = -888;
        //memo
        //dijk
        int K_dij = k+1; 
        //dijk
        //
        int K_BFS = k+1;
        //
        //return dp_memo(flights,src,dst,K_memo,memo);  //带备忘录的暴力递归算法
        //return dp(n,flights,src,dst,k);               //动态规划算法
        //return bellman_ford(n,flights,src,dst, k); //bellman ford算法
        //return dijkstra(n,flights,src,dst,K_dij);      //带约束的单源最短路径问题   //dijkstra算法
                                                         //BFS+优先级队列优化(需要用到priority_queue)
        return BFS(n,flights,src,dst,K_BFS);  //BFS+剪枝操作
    }

};
// @lc code=end
/*
bellman ford笔记
如何构建bellman ford算法
（1）抽象并初始化点与点之间的邻接矩阵graphic[][]
g[i][i] = 0;
g[i][j] = cost i与j相邻时
g[i][j] = INF  i与j不相邻时
（2）抽象原点source到各个点的距离数组dist[]
dist[source] = 0
dist[other point] =  INF

*/

