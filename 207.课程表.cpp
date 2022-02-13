/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

// @lc code=start
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    /* //DFS
    //默认没有环
    bool hasCycle = false;
    vector<vector<int>> map;
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
    }*/

    // BFS
    //默认没有环
    vector<vector<int>> map;
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

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        //创建邻接表
        bulidmap(numCourses,prerequisites);
        //计算每个点的入度
        int *indgree = new int[numCourses]; 
        //初始化
        for (int i = 0; i < numCourses; i++)
        {
            indgree[i] = 0;
        }
        
        for (int i=0;i<prerequisites.size();i++)
        {
            int from = prerequisites[i][1];
            int to = prerequisites[i][0];
            //节点to的入度+1
            indgree[to] ++;
        }
        queue<int> q;
        //根据入度初始化队列中的节点
        for (int i=0;i<numCourses;i++)
        {
            if (indgree[i]==0)
            {
                //节点没有入度，即没有依赖的点
                // 可以作为排序的起点，加入队列
                q.push(i);
            }
        }

        //记录遍历的节点个数
        int count = 0;
        //开始BFS循环
        while (!q.empty())
        {
            //弹出节点cur，并将它指向的节点的入度减一
            int cur = q.front();
            q.pop();
            count++;
            for (int i=0;i<map[cur].size();i++)
            {
                int next = map[cur][i];
                indgree[next]--;
                if (indgree[next] == 0)
                {
                    //如果入度成为0，说明Next依赖的节点已经被遍历
                    q.push(next);
                }
            }
        }
        

        //如果所有节点都被遍历了，说明不成环
        return count == numCourses;
    }
};
// @lc code=end

