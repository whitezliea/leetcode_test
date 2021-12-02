/*
 * @lc app=leetcode.cn id=1020 lang=cpp
 * 题型： DFS
 * [1020] 飞地的数量
 */
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int step;
    int numEnclaves(vector<vector<int>>& grid) {
        int res;
        int height = grid.size(); //地图的高
        int width = grid[0].size(); //地图的长 
        //淹没靠近上下的岛屿
        for (int i = 0;i<width;i++)
        {
            dfs(grid,0,i);
            dfs(grid,height-1,i);
        }
        //淹没靠近左右的岛屿
        for (int i=0;i<height;i++)
        {
            dfs(grid,i,0);
            dfs(grid,i,width-1);
        }

        //遍历grid，查找岛屿，并将其淹没
        for(int i = 0; i<height;i++)
            for(int j =0 ;j<width;j++)  
                if (grid[i][j] == 1)
                {
                    res = dfs(grid,i,j);
                    step += res;
                }
        return step;
    }
    int dfs(vector<vector<int>>& grid,int i ,int j)
    {
        int height = grid.size(); //地图的高
        int width = grid[0].size(); //地图的长 
        //先判断是否越界
        if (i<0||j<0||i>=height||j>=width)
            return 0;
        //判断是否已被淹没
        if (grid[i][j] == 0)
            return 0;
        //若是陆地，则将其淹没
        grid[i][j]=0;
        //将(i,j)相邻（上下左右）的陆地也全部淹没
        return  dfs(grid,i-1,j)+
                dfs(grid,i+1,j)+
                dfs(grid,i,j-1)+
                dfs(grid,i,j+1)+1;
    }
};
// @lc code=end

