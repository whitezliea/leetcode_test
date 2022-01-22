/*
 * @lc app=leetcode.cn id=516 lang=cpp
 *
 * [516] 最长回文子序列
 */

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    int MATH_max(int n1,int n2)
    {
        return n1>n2?n1:n2;
    }
    /*
    //解法1：暴力破解
    int dp(string s,int i1,int i2)
    {
        //base case 
        if (i1>i2)
            return 0;
        if (i1==i2)
            return 1;
        if (s[i1]==s[i2])
        {
            return dp(s,i1+1,i2-1)+2;
        }
        else
        {
            return MATH_max(
                dp(s,i1+1,i2),
                dp(s,i1,i2-1));
        }
    }
    int longestPalindromeSubseq(string s) {
        int len = s.size();
    
        return dp(s,0,len-1);
    }
    */

    //解法2：动态规划
    int dp(string s)
    {
        int len = s.size();
        int **dp = new int *[len];
        for (int i= 0;i<len;i++)
            dp[i] = new int[len];
        //初始化
        for (int i=0;i<len;i++)
            for (int j=0;j<len;j++)
                dp[i][j] = 0;
        //base case 
        for (int i=0;i<len;i++)
            dp[i][i] = 1;
        
        for (int i=len-1;i>=0;i--)
            for (int j=i+1;j<len;j++) //j>i
            {
                if (s[i]==s[j])
                    dp[i][j] = dp[i+1][j-1] + 2;
                else
                {
                    dp[i][j] = MATH_max(
                        dp[i+1][j],
                        dp[i][j-1]
                    );
                }
                
            }
        return dp[0][len-1];
    }
    int longestPalindromeSubseq(string s) {
        return dp(s);
    }
};
// @lc code=end

