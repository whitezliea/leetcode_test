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

    //解法1：Dijkstra算法
    
    //解法2：动态规划/暴力回溯/带备忘录的回溯·是··
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    
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
};
// @lc code=end

