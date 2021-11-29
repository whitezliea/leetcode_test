/*
 * @lc app=leetcode.cn id=752 lang=cpp
 * 题型：BFS
 * [752] 打开转盘锁
 */

// @lc code=start


#include<vector>
#include<string>
#include<queue>
using namespace std;



class Solution {
public:
    //将数字向上拨一位
    string pulsOne(string s, int j)
    {
        string s2 = s;
        if (s2[j] == '9')
            s2[j] = '0';
        else
            s2[j] += 1;
        return s2;
    }

    //将数字向下拨一位
    string minusOne(string s, int j)
    {
        string s2 = s;
        if (s2[j] == '0')
            s2[j] = '9';
        else
            s2[j] -= 1;
        return s2;
    }

    //实现功能 ，判断两个字符串是否相等
    bool string_equal(string a, string b)
    {
        int n = a.size();
        for(int i=0;i<n;i++)
            if(a[i]!=b[i])  
                return false;
        return true;
    }

    //实现功能，在类型为stirng的vector数组里是否含有目标数组
    bool string_find(vector<string>& d, string s)
    {
        for(vector<string>::iterator it = d.begin();it!=d.end();it++)
        {
            if(string_equal(s,*it))
                return true;
        }
    return false;
    }
    int openLock(vector<string>& deadends, string target) {
        //记录已经穷举过的密码，防止走回头路
        vector<string> visited;
        queue<string> q;
        //从起点开始启动BFS
        int step = 0;
        q.push("0000");
        visited.push_back("0000");

        while(!q.empty())
        {
            int sz = q.size();
            //将当前队列中的所有结点向周围扩散
            for (int i=0;i<sz;i++)
            {
                string cur = q.front();
                q.pop();

                //判断是否到达终点
                if(string_find(deadends,cur))
                    continue;
                if(string_equal(cur,target))
                    return step;

                //将一个节点的未遍历相邻节点加入队列
                // 4表示拨轮拨动，up与down是两种可能，总之就是列举所有可能的情况
                for(int j =0;j<4;j++)
                {
                    string up = pulsOne(cur,j);
                    if (!string_find(visited,up))
                    {  
                        q.push(up);
                        visited.push_back(up);
                    }
                    string down = minusOne(cur,j);
                    if (!string_find(visited,down))
                    {
                        q.push(down);
                        visited.push_back(down);
                    }

                }
            }
            //增加步数
            step++;
        }
        //如果穷举完都没有找到目标密码，那就是找不到，返回-1
        return -1;
    }
};
// @lc code=end

/*
算法需要进一步优化，仅仅是BFS暴力穷举所有情况
提交test通过
提交submit超时
运行超时，因为空间复杂度太高了，每出队一个元素，后面会入队4*2个元素，
如果用到set或者map可能会快一点。
*/