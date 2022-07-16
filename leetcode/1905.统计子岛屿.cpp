/*
 * @lc app=leetcode.cn id=1905 lang=cpp
 * 题型：DFS
 * [1905] 统计子岛屿
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int res = 0;//统计子岛屿数量
        int height = grid1.size(); //地图的高
        int width = grid1[0].size(); //地图的宽
        //遍历gird1与grid2，先淹没grid2与没grid1没有重合的地方
        for (int i=0;i<height;i++)  
            for (int j =0 ;j<width;j++) //肯定不是子岛，淹掉
                if(grid1[i][j]==0&&grid2[i][j]==1)
                {
                    dfs(grid2,i,j);
                }
        //grid2剩下没被淹掉的全是子岛屿，再次统计
        for (int i=0;i<height;i++)  
            for (int j =0 ;j<width;j++) 
                if(grid1[i][j]==1&&grid2[i][j]==1)
                {
                    res++;
                    dfs(grid2,i,j);
                }
        return res;
    }
    //grid1与grid2如果同时都是陆地，则淹没grid2，grid1保留
    void dfs( vector<vector<int>>& grid,int i,int j)
    {
        int height = grid.size(); //地图的高
        int width = grid[0].size(); //地图的宽
        //首先判断越界问题
        if (i<0||j<0||i>=height||j>=width)
            return ;
        if (grid[i][j]==0)
            return ;
        //淹没grid2
        grid[i][j] = 0;
        dfs(grid,i-1,j);
        dfs(grid,i+1,j);
        dfs(grid,i,j-1);
        dfs(grid,i,j+1);
    }
};
// @lc code=end

/*
题目总结:
当一个问题正面情况比较难以解决时，可以先排除他的所有反面情况，
剩下的情况就全是正面情况了。此时便于解决。
*/