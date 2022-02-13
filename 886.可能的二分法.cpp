/*
 * @lc app=leetcode.cn id=886 lang=cpp
 *
 * [886] 可能的二分法
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    bool  OK = true;
    vector<vector<int>> map;
    void buildmap(int n, vector<vector<int>>& dislikes)
    {
        map.resize(n+1);
        for (int i=0;i<dislikes.size();i++)
        {
            int v = dislikes[i][0];
            int w = dislikes[i][1];
            //无向图相当于双向图
            map[v].push_back(w);
            map[w].push_back(v);
        }
        return ;
    }
    void dfs(int s,bool visited[],bool color[])
    {
        if (OK == false)
        {
            return ;
        }
        visited[s] = true;
        for (int i=0;i<map[s].size();i++)
        {
            int next = map[s][i];
            if (!visited[next])
            {
                color[next] = !color[s];
                dfs(next,visited,color);
            }
            else
            {
                if(color[next] == color[s])
                {
                    OK = false;
                }
            }
        }

        return ;
    }
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        bool visited[n+1];
        bool color[n+1];
        for (int i=0;i<=n;i++)
        {
            visited[i] = false;
            color[i] = false;
        }
        buildmap(n,dislikes);
        for (int i=1;i<=n;i++)
        {
            if (!visited[i])
            {
                dfs(i,visited,color);
            }
        }
        return OK;
    }
};
// @lc code=end

