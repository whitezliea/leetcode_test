/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    //解法1：动态规划
    int lengthOfLIS(vector<int>& nums) {
        //创建dp数组
        int *dp = new int[nums.size()];
        //初始化为1，意思为最大序列数至少为1（包括自己）
        for(int i=0;i<nums.size();i++)
            dp[i] = 1;
        //对nums数组进行遍历
        for(int i=0;i<nums.size();i++)
        //对i之前的dp数组遍历，如果i处的数据大于j处的数据，最大序列数+1
            for(int j=0;j<i;j++)
                if(nums[i]>nums[j])
                    //比较 dp[i]与dp[j]+1的大小，并将较大值赋给dp[i]
                    dp[i] = dp[i]>dp[j]+1 ? dp[i] : dp[j]+1; //状态转移方程
        
        int res = 0;
        for (int i=0;i<nums.size();i++)
            //找出dp数组中的最大值
            res = res > dp[i] ? res : dp[i];

        return res;
    }
};
// @lc code=end

