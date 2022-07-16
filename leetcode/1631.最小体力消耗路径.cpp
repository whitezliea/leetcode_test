/*
 * @lc app=leetcode.cn id=1631 lang=cpp
 *
 * [1631] 最小体力消耗路径
 */

// @lc code=start
#include<vector>
#include<iostream>
#include<queue>
#include<limits.h>
using namespace std;
class Solution {
public:
    
    int dirs[4][2]=
    {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    
    int MATH_abs(int a,int b)
    {
        return a>b?a-b:b-a;
    }
    int MATH_max(int a,int b)
    {
        return a>b?a:b;
    }
    /*
    void adj(vector<vector<int>>& heights,int **dist,int x,int y)
    {
        int n1 = heights.size();
        int n2 = heights[0].size();
        for (int i=0;i<4;i++)
        {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if (nx>=0&&nx<n1&&ny>=0&&ny<n2)
            {
                dist[nx][ny] = MATH_abs(x,nx)+MATH_abs(y,ny);
            }
        }
        return ;
    }
    int dijkstar(vector<vector<int>>& heights)
    {
        int INF = 9999;
        //建立邻接矩阵
        //int **matrix = new int
        
        int n1 = heights.size();
        int n2 = heights[0].size();
        int **distToSrc = new int *[n1];
        bool **visited = new bool *[n1];
        for (int i=0;i<n1;i++)
        {
            distToSrc[i] = new int[n2];
            visited[i] = new bool [n2];
        }
        //初始化
        for (int i=0;i<n1;i++)
            for (int j=0;j<n2;j++)
            {
                distToSrc[i][j] = INF;
                visited[i][j] = false;
            }
        
        //base case
        distToSrc[0][0] = 0;
        adj(heights,distToSrc,0,0);
        visited[0][0] = true;

        for (int i=0;i<n1*n2-1;i++)
        {
            int MINdist = INF;
            int next_x = 0,next_y = 0;

        }
    }
    */
   int minimumEffortPath(vector<vector<int>>& heights) {
        
        int m = heights.size();
        int n = heights[0].size();
        
        auto tupleCmp = [](const auto& e1, const auto& e2) {
            auto&& [x1, y1, d1] = e1;
            auto&& [x2, y2, d2] = e2;
            return d1 > d2;
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(tupleCmp)> q(tupleCmp);
        q.emplace(0, 0, 0);

        vector<int> dist(m * n, INT_MAX);
        dist[0] = 0;
        vector<int> seen(m * n);

        while (!q.empty()) {
            auto [x, y, d] = q.top();
            q.pop();
            int id = x * n + y;
            if (seen[id]) {
                continue;
            }
            if (x == m - 1 && y == n - 1) {
                break;
            }
            seen[id] = 1;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && MATH_max(d, MATH_abs(heights[x][y] , heights[nx][ny])) < dist[nx * n + ny]) {
                    dist[nx * n + ny] = MATH_max(d, MATH_abs(heights[x][y] , heights[nx][ny]));
                    q.emplace(nx, ny, dist[nx * n + ny]);
                }
            }
        }
        
        return dist[m * n - 1];
    }
};
// @lc code=end

