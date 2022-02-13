/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 */

// @lc code=start
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    //默认没有环
    bool hasCycle = false;
    vector<vector<int>> map;
    vector<int> potser;
    void bulidmap(int numCourses, vector<vector<int>>& prerequisites)
    {
        //vector<int> adj;
        map.resize(numCourses);
        for (int i=0;i<prerequisites.size();i++)
        {
            int from = prerequisites[i][1];
            int to = prerequisites[i][0];
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

        //撤回 后序遍历的地方
        potser.push_back(s);
        onPath[s] = false;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
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
        //回溯算法
        for (int i=0;i<numCourses;i++)
        {
            dfs(i,onPath,visited);
        }

        //// 逆后序遍历结果即为拓扑排序结果
        reverse(potser.begin(),potser.end());
        vector<int> res;
        res.reserve(numCourses);
        //如果没有环，就输出序列
        if (hasCycle == false)
        {
            for (int i=0;i<numCourses;i++)
            {
                res.push_back(potser[i]);
            }
            return res;
        }
        else
            return res;
    }
};
// @lc code=end

