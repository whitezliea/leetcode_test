/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */
#include<vector>
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
/*
//解法1：暴力递归解法，缺点运行时间太长
    int coinChange(vector<int>& coins, int amount) {
        //base case
        if(amount<0) 
            return -1;
        if(amount==0)
            return 0;
        int res = 99999;//设置一个极大数
        for (vector<int>::iterator coin =coins.begin();coin!=coins.end();coin++)
        {
            //计算子问题的结果
            int subProblem = coinChange(coins,amount - *coin);
            //如果子问题没有结果则跳过
            if(subProblem == -1)
                continue;
            //在子问题中选择最优解，然后加一
            res = res > subProblem+1 ? subProblem+1:res;//取最小值
        }

        return res == 99999 ? -1 :res;
    }
*/

/*
//解法2：带备忘录的自顶向下递归解法
    int coinChange(vector<int>& coins, int amount) {
        int *memo = new int[amount+1]{0};
        //memo数组全都初始化为特殊值
        for(int i=0 ;i<=amount;i++)    
            memo[i]=-666;
        
        return dp(coins,amount,memo);
    }

    int dp(vector<int>& coins, int amount,int memo[])
    {
        if(amount<0)
            return -1;
        if(amount==0)
            return 0;
        
        //查备忘录，防止重复计算
        if(memo[amount]!=-666)
            return memo[amount];

        int res = 99999;
        for(vector<int>::iterator coin = coins.begin();coin!= coins.end();coin++)
        {
            //计算子问题的结果
            int subProblem = dp(coins,amount-*coin,memo);
            //子问题无解则跳过
            if(subProblem == -1 )
                continue;
            //在子问题中选择最优解，然后加1
            res = res>subProblem+1 ? subProblem+1: res;

        }
        //把计算结果存入备忘录
        memo[amount] = (res==99999)?-1:res;
        return memo[amount];
    }
*/

//解法3：自底向上的迭代解法
    int coinChange(vector<int>& coins, int amount) {
        int *dp = new int[amount+1]{0};
        for (int i=0;i<=amount;i++)
        //dp数组全都初始化为特殊值amount+1
            dp[i]=amount+1;
        
        //dp数组的定义：凑出总金额amont，至少需要dp[amount]枚金币

        //base case
        dp[0] = 0;
        //外层 for 循环在遍历所有状态的所有值
        for(int i = 0;i<amount+1;i++)
            //内层for循环在求所有选择的最小值
            for(vector<int>::iterator coin=coins.begin();coin!=coins.end();coin++)
            {
                //子问题无解，跳过
                if(i-*coin<0)
                    continue;
                //状态转移,选择dp[i]与dp[i-*coin]中的最小值
                dp[i] = dp[i]>dp[i-*coin]? dp[i-*coin]+1: dp[i];
            }

        //看金额amount能不能凑出来
        return (dp[amount] == amount+1) ? -1 : dp[amount];
   }

};
// @lc code=end

