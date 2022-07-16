/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
class Solution {
public:
    //注意：数组是连续的
    //状态：1、子数组num[i],前i个数  2、子数组之和dp[left][right]=sum
    //选择  1、对于前i个数的子数组，i+1可以放入，也可以不放入
    int MATH_max(int n1, int n2)
    {
        return n1>n2?n1:n2;
    }
    int dp(vector<int>& nums)
    {
        int length = nums.size();
        if (length == 0)
            return 0;
        if (length == 1)
            return nums[0];
        int *dp = new int[length];
        //初始化dp数组
        for (int i=0;i<length;i++)
            dp[i]=0;
        //明确base case
        dp[0] = nums[0];
        //明确状态与选择
        //明确状态转移方程
        for (int i=1;i<length;i++)
        {
            //nums[i]要么自成一派，要么加入之前的数组之和
            dp[i] = MATH_max(nums[i],nums[i]+dp[i-1]);
        }
        //返回所需结果
        int res = -65535;
        for (int i=0;i<length;i++)
        {
            res = dp[i]>res?dp[i]:res; //取最大值
        }
        return res;
    }
    int maxSubArray(vector<int>& nums) {
        return dp(nums);
    }
};
// @lc code=end

