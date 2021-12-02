#include<vector>
#include<string>
#include<iostream>
#include<set>
using namespace std;
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int height = grid.size();
        int width  = grid[0].size();
        //记录岛屿的序列化结果
        set<vector<int>> island;
        for (int i =0;i<height;i++)
            for(int j=0;j<width;j++)
                if (grid[i][j] == 1)
                {
                    //淹没这个岛屿同时存储岛屿的序列化结果
                    vector<int> s;
                    //初始化方向随便写，不影响序列化结果
                    dfs(grid,i,j,s,0);
                    island.insert(s);
                }
        //返回不同岛屿的数量
        return island.size();
    }
    //dfs不仅要遍历grid，还需要记录遍历的顺序，
    /*
    debug发现的问题，vector<int>& s误写为vector<int> s
    区别：
    vector<int>& s vector容器s的地址指针，进行引用，在函数内的一系列操作都是对s进行操作
    vector<int> s 新声明的一个容器，只在函数内生效。
    刷题感想，一定要小心且细心，写代码时要思考为什么要这样写，有什么含义，拒绝无意识写代码
    学思路学技巧
    */
    void dfs(vector<vector<int>>& grid,int i,int j,vector<int>& s,int dir)
    {
        int height = grid.size();
        int width = grid[0].size();
        if (i<0||j<0||i>=height||j>=width||grid[i][j]==0)
            return ;
        //前序遍历位置，进入(i,j)
        grid[i][j] = 0;//将岛屿淹没
        s.push_back(dir);

        //递归顺序
        dfs(grid,i-1,j,s,1);    //上
        dfs(grid,i+1,j,s,2);    //下
        dfs(grid,i,j-1,s,3);    //左
        dfs(grid,i,j+1,s,4);    //右
        //后序遍历位置，离开(i,j)
        s.push_back(-dir);
    }
};

int main()
{   
    Solution s1;
    vector<vector<int>> g1(4,vector<int>(5));
    int a1[][5] = {
        {1,1,0,0,0},
        {1,1,0,0,0},
        {0,0,0,0,1},
        {0,0,0,1,1}
    };
    for (int i=0;i<4;i++)
        for(int j=0;j<5;j++)
            g1[i][j]=a1[i][j];
    cout<<s1.numDistinctIslands(g1)<<endl;

    Solution s2;
    vector<vector<int>> g2(4,vector<int>(5));
    int a2[][5]={
        {1,1,0,0,0},
        {1,1,0,0,0},
        {0,0,0,0,1},
        {1,0,0,1,1}
    };
    for (int i=0;i<4;i++)
        for(int j=0;j<5;j++)
            g2[i][j]=a2[i][j];
    cout<<s2.numDistinctIslands(g2)<<endl;
}
//题型：DFS