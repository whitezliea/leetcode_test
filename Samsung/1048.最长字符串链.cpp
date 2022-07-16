/*
 * @lc app=leetcode.cn id=1048 lang=cpp
 *
 * [1048] 最长字符串链
 */

// @lc code=start
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
bool cmp1(const string &w1,const string &w2)
{
    return w1.size()<w2.size();
}
class Solution {
public:


    int MATH_max(int n1,int n2)
    {
        return n1>n2?n1:n2;
    }
    bool isOK(const string &w1,string &w2)
    {
        int n1 = w1.size();
        int n2 = w2.size();
        if (n1 != n2-1)
            return false;
        int i=0;
        for (int j=0;j<n2&&i<n1;j++)
        {
            if (w1[i]==w2[j])
            {
                ++i;
            }
        }

        return i == n1;

    }
    int longestStrChain(vector<string>& words) {
        //预处理，从小到大排序
        sort(words.begin(),words.end(), cmp1);
        
        //动态规划
        int n = words.size();
        int *dp = new int[n];
        //初始化
        for (int i=0;i<n;i++)
        {
            dp[i] = 1;
        }
        //保存最大值
        int res = 1;
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<i;j++)
            {
                if (isOK(words[j],words[i]))
                {
                    dp[i] = MATH_max(dp[i],dp[j]+1);
                }
            }
        }

        for (int i=0;i<n;i++)
        {
            res = res > dp[i] ? res:dp[i];
        }

        return res;

    }
};
// @lc code=end

