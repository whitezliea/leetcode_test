/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_max(int a,int b)
    {
        return a>b?a:b;
    }
    int dp_memo(vector<int>& nums,int p,int *memo)
    {
        int n= nums.size();
        if (p>=n)
            return 0;
        //避免重复计算
        if (memo[p]!=-1)
            return memo[p];
        
        int res = MATH_max(dp_memo(nums,p+1,memo), //不抢，去下一家
                            nums[p] + dp_memo(nums,p+2,memo));       //抢，计算金额

        memo[p] = res;
        return res;
    }
    int rob(vector<int>& nums) {
        //解法1：带备忘录的暴力算法
        int n = nums.size();
        // int *memo = new int[n];
        // for (int i=0;i<n;i++)
        //     memo[i] = -1;
        
        //解法2：动态规划
        //return dp_memo(nums,0,memo);
        //从第 i 间房子开始抢劫，最多能抢到的钱为 x
        int *dp = new int[n+2];
        // base case: dp[n] = 0
        for (int i=0;i<n+2;i++)
            dp[i] = 0;
        for (int i=n-1;i>=0;i--)
        {
            dp[i] = MATH_max(dp[i+1], //不抢，去下一家
                            nums[i]+dp[i+2]); //抢，计算金额
        }
        //为什么要return dp[0],因为终点不确定，但是起点是确定的，所以逆向思维
        return dp[0];
    }
};
// @lc code=end

