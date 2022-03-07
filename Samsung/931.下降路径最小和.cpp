/*
 * @lc app=leetcode.cn id=931 lang=cpp
 *
 * [931] 下降路径最小和
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_min(int n1,int n2)
    {
        return n1>=n2?n2:n1;
    }
    int MATH_mins(int n1,int n2,int n3)
    {
        return MATH_min(n1,MATH_min(n2,n3));
    }
/*
//解法1：暴力破解法，会超时
    int dp(vector<vector<int>>& matrix,int i,int j)
    {
        //排除不合理情况
        if (i<0||i>=matrix.size()||j<0||j>=matrix.size())
            return 65535;
        
        //递归结束条件
        if (i==0) //已是最底下一行
            return matrix[i][j];
        
        //DFS 遍历所有情况
        return matrix[i][j] + MATH_mins(
            dp(matrix,i-1,j-1),
            dp(matrix,i-1,j),
            dp(matrix,i-1,j+1)
        );

    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int res = 65535;
        //终点会落在最下面一行的任意一个位置
        for (int i=0;i<n;i++)
        {
            res = MATH_min(res,dp(matrix,n-1,i));
        }
        return res;
    }
*/


//解法2：带有备忘录的递归，消除重叠子问题
    int **memo;
        int dp(vector<vector<int>>& matrix,int i,int j)
    {
        //排除不合理情况
        if (i<0||i>=matrix.size()||j<0||j>=matrix.size())
            return 65535;
        
        //递归结束条件
        if (i==0) //已是最底下一行
            return matrix[i][j];
        
        //先查备忘录。防止重复计算
        if (memo[i][j]!=6666)
            return memo[i][j];
        //DFS 遍历所有情况 记录memo数组
        memo[i][j] = matrix[i][j] + MATH_mins(
            dp(matrix,i-1,j-1),
            dp(matrix,i-1,j),
            dp(matrix,i-1,j+1)
        );

        return memo[i][j];

    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int res = 65535;
        memo = new int*[n];
        for (int i=0;i<n;i++)
            memo[i] = new int[n];
        //初始化memo数组
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                memo[i][j] = 6666;
        //终点会落在最下面一行的任意一个位置
        for (int i=0;i<n;i++)
        {
            res = MATH_min(res,dp(matrix,n-1,i));
        }
        return res;
    }

};
// @lc code=end

