/*
 * @lc app=leetcode.cn id=797 lang=cpp
 *
 * [797] 所有可能的路径
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    //回溯算法
    void dfs(vector<vector<int>>& graph,int s,vector<int> &path)
    {
        //添加节点s加入路径path
        path.push_back(s);

        int n = graph.size();
        //base case，到达孙子节点后将path加入res
        if (s==n-1)
        {
            res.push_back(path);
            //将节点s移除路径path
            path.pop_back();
            return ;
        }
        //遍历递归
        for(int i=0;i<graph[s].size();i++)
        {
            ////将节点s移除路径path
            dfs(graph,graph[s][i],path);
        }
        
        path.pop_back();
        return ;
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        //从顶点0开始遍历
        vector<int> path;
        dfs(graph,0,path);
        return res;
    }
};
// @lc code=end

