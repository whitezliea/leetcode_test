/*
 * @lc app=leetcode.cn id=174 lang=cpp
 *
 * [174] 地下城游戏
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    
    //解法1:带备忘录的回溯暴力算法
    int DFS(vector<vector<int>>& dungeon,int x,int y,int **memo)
    {
        int n= dungeon.size();
        int m= dungeon[0].size();

        //越界判断
        if (x>=n||y>=m)
            return 65535;
        //base case 
        if (x==n-1&&y==m-1)
            return dungeon[x][y] >= 0 ? 1:1-dungeon[x][y];
        
        if (memo[x][y] != -1)
            return memo[x][y];

        int res = MATH_min(
            DFS(dungeon,x+1,y,memo), //向下走
            DFS(dungeon,x,y+1,memo)  //向右走
        )-dungeon[x][y] ;
        
        memo[x][y] =  res <=0? 1:res;

        return memo[x][y];
    }
    

    //解法2：动态规划
    int dp(vector<vector<int>>& dungeon)
    {
        int n= dungeon.size();
        int m= dungeon[0].size();
        int **dp = new int*[n];
        for (int i=0;i<n;i++)
            dp[i] = new int [m];
        //初始化
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                dp[i][j] = 0;
            
        //base case
        dp[n-1][m-1] = dungeon[n-1][m-1] >= 0 ? 1 : 1-dungeon[n-1][m-1];
        for (int i=n-2;i>=0;i--)
        {
            int res = dp[i+1][m-1] - dungeon[i][m-1];
            dp[i][m-1] = res <= 0 ? 1 :  res;
        }

        for (int j=m-2;j>=0;j--)
        {
            int res = dp[n-1][j+1] - dungeon[n-1][j];
            dp[n-1][j] = res <=0 ? 1 : res;
        }

        for (int i=n-2;i>=0;i--)
            for (int j=m-2;j>=0;j--)
            {
                int res = MATH_min(
                    dp[i+1][j],
                    dp[i][j+1]
                )-dungeon[i][j];
                dp[i][j] = res <=0 ? 1 : res;
            }

        return dp[0][0];

    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n= dungeon.size();
        int m= dungeon[0].size();
        int **memo = new int*[n];
        for (int i=0;i<n;i++)
            memo[i] = new int [m];
        //初始化
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                memo[i][j] = -1;
        //return DFS(dungeon,0,0,memo);
        return dp(dungeon);
    }
};
// @lc code=end

