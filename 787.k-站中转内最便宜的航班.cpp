/*
 * @lc app=leetcode.cn id=787 lang=cpp
 *
 * [787] K 站中转内最便宜的航班
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
    //flights[i] = [fromi, toi, pricei]
public:
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    //解法1：Dijkstra算法---》BFS改良
    
    /*
    //解法2：动态规划/暴力回溯/带备忘录的回溯算法

    int dp(vector<vector<int>>& flights,int src, int s,int k,int **memo)
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
        for (int i = 0;i<n1;i++)
        {
            if (flights[i][1]==s)
            {
                int from = flights[i][0];
                int price = flights[i][2];
                int SubProblem = dp(flights,src,from,k-1,memo);
                if (SubProblem != -1)
                {
                    res = MATH_min(res,SubProblem+price);
                }
            }
        }

        memo[s][k] =  res == 65535 ? -1 : res;
        return memo[s][k];

    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int n1 = flights.size();
        int n2 = flights[0].size();
        
        //经历过k个城市会经过k+1步路
        k++;
        int **memo = new int*[n];
        for (int i=0;i<n;i++)
            memo[i] = new int[k+1];
        for (int i=0;i<n;i++)
            for(int j=0;j<k+1;j++)
                memo[i][j] = -888;
        
        return dp(flights,src,dst,k,memo);
    }
    */
    
    /*
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

        return (res ==65535 ?-1: res);
        
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        return dp(n,flights,src,dst,k);
    }
    */

    //bellman ford算法
    //如何实现
    void array_copy(int *dist,int *clone,int N)
    {
        for (int i=0;i<N;i++)
        {
            clone[i] = dist[i]; 
        }
        return ;
    }
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
        int K = k+1; //K <= n1;
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
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        return bellman_ford(n,flights,src,dst, k);
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

