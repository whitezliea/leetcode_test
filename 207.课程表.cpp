/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    //默认没有环
    bool hasCycle = false;
    vector<vector<int>> map;
    void bulidmap(int numCourses, vector<vector<int>>& prerequisites)
    {
        //vector<int> adj;
        map.resize(numCourses);
        for (int i=0;i<prerequisites.size();i++)
        {
            int from = prerequisites[i][0];
            int to = prerequisites[i][1];
            map[from].push_back(to);
        }

    }
    void dfs(int s,bool onPath[],bool visited[])
    {
        //出现了环
        if (onPath[s] == true)
        {
            hasCycle = true;
        }
        if(visited[s]==true||hasCycle==true )
        {
            //若已经发现环，则无需遍历
            return ;
        }
        visited[s] = true;
        //添加
        onPath[s] = true;

        for (int i=0;i<map[s].size();i++)
        {
            dfs(map[s][i],onPath,visited);
        }

        //撤回
        onPath[s] = false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //遍历节点路径
        bool onPath[numCourses];
        //该点是否被遍历
        bool visited[numCourses];
        //初始化
        for (int i=0;i<numCourses;i++)
        {
            onPath[i] = false;
            visited[i] = false;
        }
        //构建邻接表
        bulidmap(numCourses,prerequisites);
        for (int i=0;i<numCourses;i++)
        {
            dfs(i,onPath,visited);
        }
        return !hasCycle;
    }
};
// @lc code=end

