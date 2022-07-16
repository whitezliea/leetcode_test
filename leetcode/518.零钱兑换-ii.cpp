/*
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int dp1(int amount,vector<int>& coins)
    {
        int len = coins.size();
        int **dp = new int *[len+1];
        for (int i=0;i<len+1;i++)
            dp[i] = new int [amount+1];
        
        //初始化
        for (int i=0;i<len+1;i++)
            for (int j=0;j<amount+1;j++)
                dp[i][j] = 0;
        
        //base case
        for (int i=0;i<len+1;i++)
            dp[i][0] = 1; //对于amount为0时，有一种方式（即0枚硬币）
        
        for (int i=1;i<len+1;i++)
            for (int j=1;j<amount+1;j++)
            {
                //当前金额可以用coins[i-1]的硬币额度来凑
                if (j-coins[i-1]>=0)
                {
                    //dp[i][j]的值为使用coins[i-1]时的值与不使用coins[i-1]时的值相加
                    //表示两种情况都要考虑----》可以逆推成暴力递归函数。
                    dp[i][j] = dp[i-1][j]
                            +dp[i][j-coins[i-1]];
                }
                else
                {
                    dp[i][j] = dp[i-1][j];
                }
            }
        return dp[len][amount];
        
    }

    //此时求的是组合问题，对于amount有几种组合方法例如[2,2,1]与[2,1,2]是相同的方法
    //对于coins[i]硬币是否可以凑出目标
    int dp2(int amount, vector<int>& coins)
    {
        int n = coins.size();
        int *dp = new int[amount+1];
        //初始化
        for (int i=0;i<amount+1;i++)
            dp[i] = 0;
        //base case 
        dp[0] = 1; //凑出金额为0的方法有一种

        for(int i=0;i<n;i++)
            for (int j=0;j<amount+1;j++)
            {
                if (j-coins[i]<0)
                    continue;
                dp[j] += dp[j-coins[i]];
            }
        
        return dp[amount];
    }

    int change(int amount, vector<int>& coins) {
        //return dp1(amount , coins);
        return dp2(amount,coins);
    }
};
// @lc code=end

