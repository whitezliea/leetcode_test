/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
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

    //解法1：回溯算法暴力递归
    int DFS(vector<vector<int>>& grid, int x,int y)
    {
        int n = grid.size();
        int m = grid[0].size();
        //越界处理
        if (x<0||y<0)
            return 65535;
        //base case
        if (x==0&&y==0)
            return grid[x][y];
        
        return MATH_min(
            DFS(grid,x,y-1), //向右走
            DFS(grid,x-1,y) //向下走
        )+grid[x][y];
    }

    //解法3:动态规划
    int dp(vector<vector<int>>& grid)
    {
        int n=grid.size();
        int m=grid[0].size();

        int **dp = new int*[n];

        for (int i=0;i<n;i++)
            dp[i] = new int[m];
        //初始化
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                dp[i][j] = 0;
        //base case 
        ////////////////////
        dp[0][0] = grid[0][0];
        for (int i=1;i<n;i++)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        
        for (int j=1;j<m;j++)
            dp[0][j] = dp[0][j-1] + grid[0][j];
        /////////////////////
        
        for (int i=1;i<n;i++)
            for (int j=1;j<m;j++)
            {
                dp[i][j] = MATH_min(
                        dp[i-1][j], //向右走 
                        dp[i][j-1]  //向下走
                        )+grid[i][j];
            }

        return dp[n-1][m-1];
        
    }
    int minPathSum(vector<vector<int>>& grid) {
        //return dp(grid);
        return DFS(grid,grid.size()-1,grid[0].size()-1);
    }
};
// @lc code=end

/*
动态规划base case 与题目要求有关
例如题目要求只能向右或者向下走，那么定义dp的base case时，
吧dp[...][0]与dp[0][...]初始化
对于grid[3][3]来说
1 3 1 
1 5 1
4 2 1
dp[3][3]的base case为
1 4 5
2 0 0
6 0 0
*/

