/*
 * @lc app=leetcode.cn id=200 lang=cpp
 * 题型： DFS
 * [200] 岛屿数量
 */
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        //遍历gird
        int m = grid.size(); //地图的长
        int n = grid[0].size(); //地图的宽
        for (int i=0;i<m;i++)
            for(int j =0 ;j<n;j++)
                if(grid[i][j] == '1')
                {
                    //每发现一个岛屿，岛屿数量加一
                    res++;
                    //然后用DFS将发现的岛屿淹没
                    DFS(grid,i,j);
                }
        return res;

    }

    //从(i,j)开始，将与之相邻的陆地都变成海水
    void DFS(vector<vector<char>>& grid,int i,int j)
    {
        int m = grid.size(); //地图的长
        int n = grid[0].size(); //地图的宽

        if (i<0||i>=m||j<0||j>=n) //超出地图范围
            return ;

        if(grid[i][j] == '0') //已经是海水了，返回
            return ;
        
        //将(i,j)处变为海水
        grid[i][j] = '0';
        //淹没与之相邻（上下左右）的陆地
        DFS(grid,i-1,j); //左
        DFS(grid,i+1,j); //右
        DFS(grid,i,j-1); //下
        DFS(grid,i,j+1); //上

    }
};
// @lc code=end

