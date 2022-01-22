/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 */

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    int MATH_max(int n1,int n2,int n3)
    {
        int max = 0;
        max = n1 < n2 ? n2 : n1;
        max = max < n3 ? n3 : max;
        return max;
    }
    int MATH_max_2(int n1,int n2)
    {
        return n1> n2 ? n1: n2;
    }
    /*
    //解法1：暴力递归 容易超时
    int dp(string s1,int index1,string s2,int index2)
    {
        //bacse case
        if (index1 == s1.size()||index2 == s2.size())
            return 0; //表示剩下的都是空串
        
        if (s1[index1]==s2[index2])
            return dp(s1,index1+1,s2,index2+1)+1;
        
        else
        {   return MATH_max(
                dp(s1,index1+1,s2,index2),  //s1不在lcs中
                dp(s1,index1,s2,index2+1),  //s2 不在lcs 中
                dp(s1,index1+1,s2,index2+1) //s1 s2都不在lcs中
            );
        }
    }
    int longestCommonSubsequence(string text1, string text2) {
        return dp(text1,0,text2,0);
    }
    */
    
    //解法2：带备忘录的递归 //还是有超时的问题
    /*
    int dp(string s1,int index1,string s2,int index2,int **memo )
    {
        //base case 
        if (index1==s1.size() || index2 == s2.size())
            return 0;
        
        if (memo[index1][index2] != -1)
            return memo[index1][index2];

        if (s1[index1] == s2[index2])
            memo[index1][index2] = dp(s1,index1+1,s2,index2+1,memo)+1;
        else
        { 
            memo[index1][index2] = MATH_max_2(
                dp(s1,index1+1,s2,index2,memo),
                dp(s1,index1,s2,index2+1,memo)
            );
        }

        return memo[index1][index2];
        
    }
    int longestCommonSubsequence(string text1, string text2) {
        //创建备忘录
        int n1= text1.size();
        int n2= text2.size();
        int **memo = new int *[n1];
        for (int i=0;i<n1;i++)
            memo[i] = new int [n2]; 
        for (int i=0;i<n1;i++)
            for (int j=0;j<n2;j++)
                memo[i][j] = -1;
        return dp(text1,0,text2,0,memo);
    }
    */
   
    //解法3：动态规划
    int dp(string s1,string s2)
    {
        //int dp[n1+1][n2+1]
        //最后返回dp[n1][n2] 表示n1或则n2到达s1.size()/s2.size();
        int n1= s1.size();
        int n2 = s2.size();
        int **dp = new int *[n1+1];
        for (int i=0;i<n1+1;i++)
            dp[i] = new int[n2+1];
        //初始化
        for (int i = 0;i<n1+1;i++)
            for (int j=0;j<n2+1;j++)
                dp[i][j] = -1;
        
        //base case 
        for (int i=0;i<n1+1;i++)
            dp[i][0] = 0;
        for (int j=0;j<n2+1;j++)
            dp[0][j] = 0;
        
        for (int i=1;i<=n1;i++)
            for (int j=1;j<=n2;j++)
            {
                if (s1[i-1] == s2[j-1] )
                {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else
                {
                    dp[i][j] = MATH_max_2(
                        dp[i-1][j],dp[i][j-1]
                    );
                }   
            }
        return dp[n1][n2];
    }
    int longestCommonSubsequence(string text1, string text2) {
        return dp(text1,text2);
    }
};
// @lc code=end

