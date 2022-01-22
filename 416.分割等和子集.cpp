/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */

// @lc code=start
//转化成0-1背包问题
#include<vector>
using namespace std;
class Solution {
public:
    int sum(vector<int> &nums)
    {
        int sum=0;
        for (int i=0;i<nums.size();i++)
            sum += nums[i];
        return sum;
    }
    int MATH_max(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    bool dp(vector<int> &nums, int target)
    {
        int len = nums.size();
        //dp的含义 dp[nums[i]][target] = true/false
        bool **dp = new bool *[len+1];
        for (int i=0;i<len+1;i++)
            dp[i] = new bool [target+1];
        //初始化
        for (int i=0;i<len+1;i++)
            for (int j=0;j<target+1;j++)
                dp[i][j] = false;
        //base case
        for (int i=0;i<len+1;i++)
            dp[i][0] = true;//这种情况是默认ture

        for (int i=1;i<len+1;i++)
            for (int j=1;j<target+1;j++)
            {
                if (j-nums[i-1]<0)
                {
                    //背包容量不足，不能放入nums[i-1]
                    dp[i][j] = dp[i-1][j];
                }
                else 
                {
                    //装入或者不装入背包，只要有一个为真，dp[i][j]就为真
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                    //当dp[i-1][j] 不装入背包
                    //与dp[i-1][j-nums[i-1]]装入背包
                    //都为假时，说明这个已经不能达到目标
                }
            }
         
         //返回最终的状态
         return dp[len][target];

    }
    bool canPartition(vector<int>& nums) {
        int target = sum(nums);
        if (target %2 !=0)
            return false;
        return dp(nums,target/2);
    }
};
// @lc code=end

/*
0-1背包问题总结
    //问题抽象
    dp[状态1][状态2][...] = dp数组所代表的含义
    //base case 
    dp[边缘状态][...] = 初始树
    //动态转移方程
    dp[状态1][状态2][...] = 择优函数(选择1,选择2,.....)
    //最后所求值
    dp[最终状态1][最终状态2][....]
*/

