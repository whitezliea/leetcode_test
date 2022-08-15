/*
 * @lc app=leetcode.cn id=118 lang=cpp
 *
 * [118] 杨辉三角
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;

        if (numRows == 0)
            return res;
        vector<int> first_row;
        first_row.push_back(1);
        res.push_back(first_row); 
        
        for(int i = 1; i < numRows; i++)
        {
            vector<int> prev_row = res[i-1];
            vector<int> cur_row;
            cur_row.push_back(1);

            //杨辉三角
            for (int j = 1; j < i; j++)
            {
                cur_row.push_back(prev_row[j-1]+prev_row[j]);
            }
            cur_row.push_back(1);
            res.push_back(cur_row);
        } 
        
        return res;
    }
};
// @lc code=end

