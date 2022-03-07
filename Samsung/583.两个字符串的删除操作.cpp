/*
 * @lc app=leetcode.cn id=583 lang=cpp
 *
 * [583] 两个字符串的删除操作
 */

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    int MATH_min(int n1,int n2,int n3)
    {
        int min=0;
        min = n1 > n2 ?n2:n1;
        min = min > n3 ?n3 :min;
        return min;
    }
    int MATH_min_2(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }
    /*
    //解法1：暴力破解
    int dp(string s1,int i1, string s2,int i2)
    {
        int l1 = s1.size();
        int l2 = s1.size();
        //basce case 
        if (i1 == -1 )
            return i2+1;
        if (i2 == -1)
            return i1 + 1;
        
        if (s1[i1] == s2[i2])
        {
            return dp (s1,i1-1,s2,i2-1);
        }
        else 
        {
            return MATH_min(
                dp(s1,i1-1,s2,i2)+1,
                dp(s1,i1,s2,i2-1)+1,
                dp(s1,i1-1,s2,i2-1)+2    
            );
        }
    }
    int minDistance(string word1, string word2) {
        int l1 = word1.size();
        int l2 = word2.size();
        return dp(word1,l1-1,word2,l2-1);
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
        for (int i=0;i<l1+1;i++)
            dp[i][0] = i; 
        for (int j=0;j<l2+1;j++)
            dp[0][j] = j;

        for (int i=1;i<=l1;i++)
            for (int j=1;j<=l2;j++)
            {
                if (s1[i-1] == s2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    dp[i][j] = MATH_min_2(
                        dp[i-1][j]+1,
                        dp[i][j-1]+1
                        //dp[i-1][j-1]+2
                    );
                }
            }

        return dp[l1][l2];
                
            
    }
    int minDistance(string word1, string word2) {

        return dp(word1,word2);
    }
};
// @lc code=end

