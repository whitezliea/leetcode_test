/*
 * @lc app=leetcode.cn id=695 lang=cpp
 * 题型 DFS
 * [695] 岛屿的最大面积
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxsum=0; //岛屿最大的面积
        int res;
        int height = grid.size();//地图的高度
        int width = grid[0].size();//地图的宽度
        
        for (int i =0 ;i< height; i++)
            for (int j = 0;j<width;j++)
                if (grid[i][j] == 1) //如果是陆地
                {
                    res = dfs(grid,i,j);
                    maxsum = maxsum > res ? maxsum:res;//求最大值
                }
        return maxsum;
    }

    int dfs(vector<vector<int>>& grid,int i ,int j)
    {
        int height = grid.size();//地图的高度
        int width = grid[0].size();//地图的宽度
        //先判断下标合法性，是否越界
        if (i<0||j<0||i>=height||j>=width)
            return 0;
        if (grid[i][j]==0)//已经是海水了
            return 0;
        //将陆地淹没
        grid[i][j] = 0;
        return  dfs(grid,i-1,j)+
                dfs(grid,i+1,j)+
                dfs(grid,i,j-1)+
                dfs(grid,i,j+1)+1;
    }
};
// @lc code=end

