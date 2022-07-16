/*
 * @lc app=leetcode.cn id=46 lang=cpp
 * 题型： 回溯算法（DFS）
 * [46] 全排列
 */
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    //主函数，输入一组不重复的数字，返回它们的全排列
    vector<vector<int>> permute(vector<int>& nums)
    {
        //存储全排列的结果
        vector<vector<int>> res;
       //记录路径
        vector<int> track ;
        backtrack(nums,track,res);
        return res;
    }

    bool my_find(vector<int>& t,int i)
    {
        for(vector<int>::iterator it=t.begin();it!=t.end();it++)
            if(i == *it)
                return true;
        return false; //默认是false，即找不到
    }

    //回溯算法框架
    void backtrack(vector<int>& nums,vector<int> track,vector<vector<int>> & res)
    {
        //到达叶子节点，将路径装入结果列表
        if (track.size() == nums.size())
        {
            res.push_back(track);
            //递归出口
            return ;
        }

        for(vector<int>::iterator it=nums.begin();it!=nums.end();it++)
        {
            //排除不合法的选择
            if(my_find(track,*it))
                continue;
            //做选择
            track.push_back(*it);
            //进入下一层决策树
            backtrack(nums,track,res);
            //取消选择
            track.pop_back();
        }
        
    }

};
// @lc code=end

