/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
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
    int dp(vector<int>& nums,int start,int end)
    {
        int n=nums.size();
        int *dp = new int[n+2];
        // base case: dp[n] = 0
        for (int i=0;i<n+2;i++)
            dp[i] = 0;
        for (int i=end;i>=start;i--)
        {
            dp[i] = MATH_max(dp[i+1], //不抢，去下一家
                            nums[i]+dp[i+2]); //抢，计算金额
        }
        //为什么要return dp[0],因为终点不确定，但是起点是确定的，所以逆向思维
        return dp[start];
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n==1)
            return nums[0];
        return MATH_max(dp(nums,0,n-2),
                        dp(nums,1,n-1));
    }
};
// @lc code=end

