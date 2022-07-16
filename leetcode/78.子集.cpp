/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
  
    vector<vector<int>> subsets(vector<int>& nums) {
        //0的含义是一开始选0个数
        vector<int> temp;
        backtrack(nums,0,temp);
        return res;
    }

    void backtrack(vector<int>& nums,int k,vector<int>& temp) 
    {
        res.push_back(temp);
        for (int i = k;i<nums.size();i++)
        {
                //做选择
                temp.push_back(nums[i]);
                //递归下一层
                //这里错误将i+1写成k+1
                backtrack(nums,i+1,temp);
                //取消选择
                temp.pop_back();
           
        }
    }
};
// @lc code=end
/*
Your Input
[1,2,3]
Output 
[[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
*/
