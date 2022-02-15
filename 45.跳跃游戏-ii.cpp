/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_min (int a,int b)
    {
        return a>b?b:a;
    }
    int MATH_max (int a,int b)
    {
        return a>b?a:b;
    }
    // 定义：从索引 p 跳到最后一格，至少需要 dp_memo(nums, p,memo) 步
    int dp_memo(vector<int>& nums, int p ,int *memo)
    {
        int n = nums.size();
        //base case
        if (p >= n-1)
            return 0;
        //子问题已经解决过了
        if (memo[p]!=n)
            return memo[p];
        int steps = nums[p];
        //你可以跳 <= steps的步数，最少从1开始
        for (int i=1;i<=steps;i++)
        {
            //穷举
            //计算子问题
            int SubProblem = dp_memo(nums,p+i,memo);
            //+1是进行一次跳跃
            memo[p] = MATH_min(memo[p],SubProblem+1);  
        }
        return memo[p];
    }
    int jump(vector<int>& nums) {
        //解法1：带备忘录的穷举算法
        int n = nums.size();
        // int *memo = new int [n];
        // for (int i = 0; i < n; i++)
        // {
        //     memo[i] = n;
        // }

       // return dp_memo(nums,0,memo);
       //解法2：贪心算法
       int end = 0,farthest = 0;
       int jumps = 0;
       for (int i=0;i<n-1;i++)
       {
           //每一步都尽量跳出最远
           farthest= MATH_max(nums[i]+i,farthest);
           if (end == i)
           {
               jumps++;
               end = farthest;
           }
       }
        return jumps;
    }
};
// @lc code=end

