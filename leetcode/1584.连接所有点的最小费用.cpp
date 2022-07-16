/*
 * @lc app=leetcode.cn id=1584 lang=cpp
 *
 * [1584] 连接所有点的最小费用
 */

// @lc code=start
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
class UF
{
private:
    //连同分量个数
    int count;
    //存储一棵树
    int *parent;
    //记录树的的节点的重量
    int *size;
public:
    UF(int n)
    {
        count = n;
        parent = new int[n];
        size = new int[n];
        for (int i=0;i<n;i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }
    //将节点p和q进行连通
    void union_(int p,int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP==rootQ)
            return ;
        
        //小树接到大树下面，平衡
        if (size[rootP] > size[rootQ])
        {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        else
        {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        //两个连通分量变为一个联通分量
        count--;
    }

    //返回节点x的连通分量根节点
    int find(int x)
    {
        while (parent[x]!=x)
        {
            //将路径进行压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool connected(int p,int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        return rootP == rootQ;
    }

    //返回图中的连通分量个数
    int getCount()
    {
        return count;
    }
    
};
struct EDGE
{
    int from =0;
    int to =0;
    int weight =0;
};

bool cmp1(const vector<int> &v1,const vector<int> &v2)
{
    return v1[2] < v2[2];
}
class Solution {
public:
    int MATH_abs(int a,int b)
    {
        return a>b?a-b:b-a;
    }
    //升序排序
    void edge_sort(EDGE *e,int n)
    {
        EDGE temp;
        for (int i=n-1;i>=0;i--)
        {
            for (int j=0;j<i;j++)
            {
                if (e[j].weight > e[j+1].weight)
                {
                    temp = e[j];
                    e[j] = e[j+1];
                    e[j+1] = temp;
                }
            }
        }
        return ;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int len = n*(n-1)/2;
        //EDGE *data = new EDGE[len];
        vector<vector<int>> edges;
        edges.resize(len);

        int k=0;
        
        for (int i=0;i<n;i++)
        {
            for (int j=i+1;j<n;j++)
            {
                edges[k].reserve(3);
                //edges[k].resize(3);
                int xi = points[i][0],yi = points[i][1];
                int xj = points[j][0], yj = points[j][1];
                int weight = MATH_abs(xi,xj)+MATH_abs(yi,yj);
                //data[k].from = i;
                //data[k].to = j;
                //data[k].weight = MATH_abs(xi,xj)+MATH_abs(yi,yj);
                edges[k].push_back(i);
                edges[k].push_back(j);
                edges[k].push_back(weight);
                k++;
            }
        }
       // edge_sort(data,len);
        sort(edges.begin(),edges.end(),cmp1);
        //执行Kruskal算法
        int mst = 0;
        UF uf(n);
        for (int i=0;i<len;i++)
        {
            //int u = data[i].from;
            //int v = data[i].to;
            //int weight = data[i].weight;
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2];
            //若这条边会产生环，则不能加入mst
            if (uf.connected(u,v))
                continue;
            //若这条边不产生环，则属于最小生成树
            mst += weight;
            uf.union_(u,v);
        }

        return mst;
    }
};

// @lc code=end

