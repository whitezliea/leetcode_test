/*
 * @lc app=leetcode.cn id=312 lang=cpp
 *
 * [312] 戳气球
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_max(int n1,int n2)
    {
        return n1>n2?n1:n2;
    }
    int maxCoins(vector<int>& nums) {

        int n = nums.size();
        //两端加入两个虚拟气球
        int *point = new int[n+2];
        //初始化
        for (int i=0;i<n+2;i++)
            point[i] = 1;
        //赋值
        for (int i=1;i<n+1;i++)
            point[i] = nums[i-1];
        
        //定义dp数组的含义
        //dp[i][j]=x 表示戳破气球i与j（不包括i和j）的所有气球，可以获取的最高分数为x
        int **dp = new int *[n+2];
        for (int i=0;i<n+2;i++)
            dp[i] = new int [n+2];
        //初始化
        for (int i=0;i<n+2;i++)
            for(int j=0;j<n+2;j++)
                dp[i][j] = 0;
        
        //base case
        //反向思考
        //如果最后戳破的是气球k
        //dp[i][j] = dp[i][k]+dp[k][j]+point[i]*point[k]*point[j];
        
        //状态转移方程 //假定i<j
        //i应该从下往上
        for (int i=n;i>=0;i--)
            for(int j=i+1;j<n+2;j++)
            //k位于i与j之间
                for (int k=i+1;k<j;k++)
                {
                    dp[i][j] = MATH_max
                    (
                        dp[i][j],
                        dp[i][k]+dp[k][j] + point[i] * point[k] *point[j]
                    );
                }
        
        return dp[0][n+1];
    }
};
// @lc code=end

