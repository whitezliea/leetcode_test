/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {
        vector<int> path;
        backtrack(n,1,k,path);
        return res;
    }
    void backtrack(int n,int start,int k, vector<int> &path)
    {
        if (path.size()==k)
        res.push_back(path);

        for (int i = start;i<=n;i++)
        {
           
            path.push_back(i);
            backtrack(n,i+1,k,path);
            path.pop_back();
                
        }
    }
};

// @lc code=end

