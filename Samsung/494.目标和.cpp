/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */
#include<vector>
#include<map>
#include<string>
using namespace std;
// @lc code=start
class Solution {
    public:
    /*
    //方法1：DFS 遍历所有可能性
    int count = 0;
    void DFS(vector<int>& nums,int target,int index,int sum)
    {

        if (index==nums.size()&&sum == target)
        {
            count++;
            return ;
        }

        if (index >= nums.size())
            return ;

        sum += nums[index];
        DFS(nums,target,index+1,sum);
        sum -= nums[index];

        sum -= nums[index];
        DFS(nums,target,index+1,sum);
        sum += nums[index];

    }

    int findTargetSumWays(vector<int>& nums, int target) {
        DFS(nums, target, 0,0);
        return count;
    }
    */

    /*
    // 方法2：带备忘录的回溯
    map <string, int> mp;
    int dp(vector<int> nums, int index, int target, int sum)
    {
        if (index == nums.size() && sum == target)
        {
            return 1;
        }

        if (index >= nums.size())
            return 0;

        // int to string
        string s1 = to_string(index);
        s1 += ',';
        string s2 = to_string(sum);
        string s = s1 + s2;

        if (mp.count(s) != 0)
            return mp[s];

        int result = dp(nums, index + 1, target, sum + nums[index])
            + dp(nums, index + 1, target, sum - nums[index]);

        mp[s] = result;
        return result;
    }

    int findTargetSumWays(vector<int>& nums, int target)
    {
        if (nums.size() == 0)
            return 0;
        int nu = dp(nums, 0, target, 0);
        //for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++)
        //{
        //    cout << it->first << " " << it->second << endl;
        //}
        //cout << endl;
        return nu;
    }*/

    //方法3：动态规划
    int findTargetSumWays(vector<int>& nums, int target) 
    {
        if (nums.size()==0)
            return 0;
        int sum = 0;
        for (int i=0;i<nums.size();i++)
        {
            sum+=nums[i];
        }

        if (sum<target||(sum+target)%2==1|| (sum + target) < 0)
            return 0;
        
        return subsets(nums,(sum+target)/2);
    }

    int subsets(vector<int>& nums, int temp)
    {
        int n = nums.size();
        //创建二维数组
        int **dp;
        dp = new int *[n+1];
        for (int i=0;i<n+1;i++)
            dp[i] = new int[temp + 1];
        //初始化二维数组
        for (int i=0;i<n+1;i++)
            for (int j=0;j<temp+1;j++)
                dp[i][j] = 0;
        //base case 
        for (int i=0;i<n+1;i++)
            dp[i][0] = 1; //意味对于nums[i],target=0时的解法只要一种
        
        //dp状态转移方程
        for (int i = 1; i<=n; i++)
            for (int j=0;j<=temp;j++) //target < temp
            {
                if (j>=nums[i-1])
                {
                    //两种选择的结果之和 放入这个数与不放这个数
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
                }
                else
                {
                    //背包空间不足，只能选择不装物品i
                    dp[i][j] = dp[i-1][j];
                }
            }
        
        return dp[n][temp];
    }
};
// @lc code=end

