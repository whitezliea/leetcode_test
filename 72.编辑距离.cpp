/*
 * @lc app=leetcode.cn id=72 lang=cpp
 * 题型：动态规划
 * [72] 编辑距离
 */
#include<string>
using namespace std;
// @lc code=start
class Solution {
public:

/*
//解法1：原始的暴力解法 存在重叠子问题 数据太大时会运行超时
    int minDistance(string word1, string word2) {
        //定义: dp(i,j) 返回word1[0...i]和word2[0...j]的最小编辑距离
        // i,j初始化指向最后一个索引,即指向最后一个字符
        int l1 = word1.size();
        int l2 = word2.size();
        return dp(word1,word2,l1-1,l2-1);
                
        //return dp(word1,word2,word1.size()-1,word2.size()-1);
    }
    int min(int i,int j, int k)
    {
        int min;
        if (i>j)
            min=j;
        else
            min=i;
        if(min>k)  
            min = k;
        return min;
    }
    int dp(string word1, string word2,int i,int j)
    {
        //base case
        //解释，如果某一个字符串下标走到尽头，就返回另外一个字符串的下标+1,
        //意思是将另外一个字符串的下标及之前的数全部插入/删除
        if (i==-1)
            return j+1;
        if(j==-1)
            return i+1;
        
        if(word1[i] == word2[j])
            return dp(word1,word2,i-1,j-1); //啥也不做
        else
            return min(
                dp(word1,word2,i,j-1) +1 , //插入
                dp(word1,word2,i-1,j) +1 , //删除
                dp(word1,word2,i-1,j-1) +1  //替换
            );
    }
*/

/*
    //解法2：带备忘录的递归解法 不会超时，但是运行时间与内存占用不太理想
    int minDistance(string word1, string word2) {
        //定义: dp(i,j) 返回word1[0...i]和word2[0...j]的最小编辑距离
        int l1 = word1.size();
        int l2 = word2.size();
        int **memo = new int *[l1+1]{0};
        for(int i = 0;i<l1+1;i++)   
            memo[i] = new int [l2+1]{0};
        //数组初始化
        for(int i = 0;i<l1+1;i++)
            for(int j = 0;j<l2+1;j++)
                memo[i][j]=-666;
        return dp(word1,word2,l1-1,l2-1,memo);
    }

    int min(int i,int j, int k)
    {
        int min;
        if (i>j)
            min=j;
        else
            min=i;
        if(min>k)  
            min = k;
        return min;
    }

    int dp(string word1, string word2,int i,int j,int **memo)
    {
        //base case
        if(i==-1)
            return j+1;
        if(j==-1)
            return i+1;
        
        //查备忘录
        if (memo[i][j]!=-666)
            return memo[i][j];
        
        if(word1[i]==word2[j])
            memo[i][j] = dp(word1,word2,i-1,j-1,memo); //啥也不做
        else
            memo[i][j]=min(
                dp(word1,word2,i,j-1,memo)+1,   //插入
                dp(word1,word2,i-1,j,memo)+1,   //删除
                dp(word1,word2,i-1,j-1,memo)+1  //替换
            );
        return memo[i][j];
    }
*/

//解法3：自底向上的迭代解法
    int min(int i,int j, int k)
    {
        int min;
        if (i>j)
            min=j;
        else
            min=i;
        if(min>k)  
            min = k;
        return min;
    }

    int minDistance(string word1, string word2) {
        
        int l1 = word1.size();
        int l2 = word2.size();
        //创建二维数组，状态转移方程
        //定义: dp[i][j] 返回word1[0...i]和word2[0...j]的最小编辑距离
        int **dp = new int *[l1+1]{0};
        for(int i = 0;i<l1+1;i++)   
            dp[i] = new int [l2+1]{0};
        //数组初始化
        for(int i = 0;i<l1+1;i++)
            for(int j = 0;j<l2+1;j++)
                dp[i][j]=0;
        
        //base case 
        //j==0与i==0表示字符串下标已经走到尽头
        for(int i=1;i<=l1;i++)
            dp[i][0] = i;  //下标为[i][0]还剩i个字符
        for(int j=1;j<=l2;j++)
            dp[0][j] = j;  //下标为[0][j]还剩j个字符

        //自底向上求解
        for(int i=1;i<=l1;i++)
            for(int j=1;j<=l2;j++)
                if(word1[i-1]==word2[j-1]) //如果i-1处的字符与i-2处的字符相等，状态转移到[i-1][j-1]
                    dp[i][j] = dp[i-1][j-1]; //啥也不做，状态转移方程
                else
                    dp[i][j] = min(
                        dp[i][j-1] + 1,  //插入
                        dp[i-1][j] + 1,  //删除
                        dp[i-1][j-1] + 1  //替换
                    ); 
        
        return dp[l1][l2];
    }

};
// @lc code=end

