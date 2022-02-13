/*
 * @lc app=leetcode.cn id=785 lang=cpp
 *
 * [785] 判断二分图
 */

// @lc code=start
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    //记录图是否符合二分图性质
    bool OK  = true;
    void dfs(vector<vector<int>>& graph,int s,bool visited[],bool color[])
    {
        //如果已经确定不是二分图了，就不要浪费时间再递归遍历了
        if(OK==false)
        {
            return ;
        }
        //顶点s置为被访问
        visited[s] = true;
        for (int i=0;i<graph[s].size();i++)
        {
            int next = graph[s][i];
            //如果相邻节点next还未被访问过
            //那么应该给节点next涂上与节点s不同的颜色
            if (!visited[next])
            {
                color[next] = !color[s];
                //继续遍历w
                dfs(graph,next,visited,color);
            }
            else
            {
                // 相邻节点都被访问过了
                // 根据s和next的颜色判断是否是二分图
                if (color[next]==color[s])
                {
                    OK = false;
                }
            }
        }
        return ;

    }

    void bfs(vector<vector<int>>& graph,int s,bool visited[],bool color[])
    {
        queue<int> q;
        visited[s]=true;
        q.push(s);
        while (!q.empty()&&OK)
        {
            int cur = q.front();
            q.pop();
            for (int i=0;i<graph[cur].size();i++)
            {
                int next = graph[cur][i];
                if (!visited[next])
                {
                    color[next] = !color[cur];
                    visited[next] = true;
                    q.push(next);
                }
                else
                {
                    if (color[next] == color[cur])
                    {
                        OK = false;
                    }
                }
            }
        }
        return ;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        //记录图中节点颜色，false与true代表两种不同的颜色
        bool color[n];
        //记录图中的节点是否被访问
        bool visited[n];
        //初始化
        for (int i = 0;i<n;i++)
        {
            color[i] = false;
            visited[i] = false;
        }
        //DFS算法
        //因为图不一定连通，可能存在多个子图
        //所以要把每个节点都作为起点进行一次遍历
        //如果发现任何一个子图都不是二分图，整幅图都不算二分图
        for (int i=0;i<n;i++)
        {
            if (visited[i]==false)
            {
                //dfs(graph,i,visited,color);
                bfs(graph,i,visited,color);
            }
        }
        return OK;
    }
};
// @lc code=end

