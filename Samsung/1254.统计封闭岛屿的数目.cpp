/*
 * @lc app=leetcode.cn id=1254 lang=cpp
 * 题型： DFS
 * [1254] 统计封闭岛屿的数目
 */
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;//记录封闭岛屿数量
        int m = grid[0].size();//地图的长
        int n = grid.size();//地图的高
        //把靠边的岛屿都淹没
        //把靠上的岛屿都淹没 i =0
        for (int i = 0; i<m;i++)    
        {
                dfs(grid,0,i);
        }
        //把靠下的岛屿都淹没
        for (int i = 0;i<m;i++)
        {
                dfs(grid,n-1,i);
        }
        //把靠左的岛屿都淹没
        for (int i=0;i<n;i++)
        {
                dfs(grid,i,0);
        }
        //把靠右的岛屿都淹没
        for (int i=0;i<n;i++)
        {
                dfs(grid,i,m-1);
        }

        //遍历grid，查找封闭岛屿
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                if (grid[i][j] == 0)
                {
                    res++;
                    dfs(grid,i,j);
                }
        return res;
    }

    //用算法dfs将相邻（上下左右连接）的岛屿淹没
    void dfs(vector<vector<int>>& grid ,int i ,int j)
    {
        int m = grid[0].size();//地图的长
        int n = grid.size();//地图的高
        //超出边界，跳过
        //先判断越界，真很重要，关乎程序是否能够运行！！！
        if (i<0||j<0||i>=n||j>=m)
            return ;
        //如果是海水，跳过
        if (grid[i][j] == 1)
            return ;


        //将(i,j)处淹没
        grid[i][j] = 1;
        //将节点(i,j)上下左右相邻的陆地全部淹没
        dfs(grid,i-1,j);
        dfs(grid,i+1,j);
        dfs(grid,i,j-1);
        dfs(grid,i,j+1);
    }
};
// @lc code=end

