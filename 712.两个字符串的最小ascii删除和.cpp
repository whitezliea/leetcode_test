/*
 * @lc app=leetcode.cn id=712 lang=cpp
 *
 * [712] 两个字符串的最小ASCII删除和
 */

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    int sum(string s,int n)
    {
        int sum=0;
        for (int i=0;i<=n;i++)
            sum += s[i];
        return sum;
    }
    
    /*
    //解法1：暴力递归
    int dp(string s1,int i1,string s2,int i2)
    {
        //base case 
        if (i1==-1)
            return sum(s2,i2);
        if (i2 == -1)
            return sum(s1,i1);

        if (s1[i1]==s2[i2])
            return dp(s1,i1-1,s2,i2-1);
        else
        {
            return MATH_min(
                dp(s1,i1-1,s2,i2)+s1[i1],
                dp(s1,i1,s2,i2-1)+s2[i2]
            );
        }
    }
    int minimumDeleteSum(string s1, string s2) {
        int l1 = s1.size();
        int l2 = s2.size();
        return dp(s1,l1-1,s2,l2-1);
    }
    */

    //解法2：动态规划
    int dp(string s1,string s2)
    {
        int l1 = s1.size();
        int l2 = s2.size();
        int **dp = new int *[l1+1];
        for (int i=0;i<l1+1;i++)
            dp[i] = new int [l2+1];
        //初始化
        for (int i=0;i<l1+1;i++)
            for (int j=0;j<l2+1;j++)
                dp[i][j] = 0;
        //base case
        dp[0][0] = 0; 
        for (int i=1;i<l1+1;i++)
            dp[i][0] = sum(s1,i-1);
        for (int j=1;j<l2+1;j++)
            dp[0][j] = sum(s2,j-1);

        for (int i=1;i<=l1;i++)
            for (int j=1;j<=l2;j++)
            {
                if (s1[i-1]==s2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                {
                    dp[i][j]=MATH_min(
                            dp[i-1][j] + s1[i-1],
                            dp[i][j-1] + s2[j-1]
                    );
                }
            }
        
        return dp[l1][l2];
    }
    int minimumDeleteSum(string s1, string s2) {

        return dp(s1,s2);
    }
};
// @lc code=end

