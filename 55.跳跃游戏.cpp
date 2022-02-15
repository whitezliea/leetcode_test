/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_max  (int a,int b)
    {
        return a>b?a:b;
    }
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0;
        //nums[n-1]即为终点，无需关注farthest
        for (int i=0;i<n-1;i++)
        {
            //不断计算能跳到的最远距离
            farthest = MATH_max(farthest,i+nums[i]);
            //可能碰到0，卡住跳不动,或者说无法到达终点
            if (farthest <= i)
                return false;
            
        }

        return farthest >= n-1 ;
    }
};
// @lc code=end

