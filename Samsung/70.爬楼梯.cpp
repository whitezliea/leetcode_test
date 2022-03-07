/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    //此时求的是排列问题 例如 [2,1,2] 与 [2,2,1]是不同的方法
    //step[0]和step[1]是必须都用到的，
    int dp(int n)
    {
        int *dp = new int[n+1];
        //初始化
        for (int i=0;i<n+1;i++)
            dp[i] = 0;
        //base case 
        dp[0] = 1; dp[1] = 1;
        //step数组有1和2
        int step[2] = {1,2};
        for (int i=2;i<n+1;i++)
            for (int j=0;j<2;j++)
            {
                if (i-step[j]<0)
                    continue;
                dp[i] += dp[i-step[j]];
            }
        return dp[n];
    }
    int climbStairs(int n) {
        return dp(n);
    }
};
// @lc code=end

