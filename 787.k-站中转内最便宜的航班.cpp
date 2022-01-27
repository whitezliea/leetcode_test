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
    //解法1：Dijkstra算法
    
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
};
// @lc code=end

