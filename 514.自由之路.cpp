/*
 * @lc app=leetcode.cn id=514 lang=cpp
 *
 * [514] 自由之路
 */

// @lc code=start
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    int MATH_abs(int n1,int n2)
    {
        return n1>n2?n1-n2:n2-n1;
    }
    int MATH_min(int n1,int n2)
    {
        return n1>n2?n2:n1;
    }

    //解法1：带备忘录的回溯暴力递归算法
    int DFS(string ring,int r,string key ,int k,int **memo)
    {
        //base case 
        if (k==key.size())
            return 0;
        //备忘录，避免重叠子问题
        if (memo[r][k]!=0)
            return memo[r][k];
        
        int n = ring.size();
        int res = 65535;
        //ring上可能有多个字符key[j]
        for (int i=0 ;i<ring.size();i++)
        {
            if (ring[i]==key[k])
            {
                //从i到r需要的步数，拨动指针的次数
                int step = MATH_abs(i,r);
                //选择顺时针还是逆时针
                step = MATH_min(step,n-step);
                //将指针拨到ring[i]处，开始寻找key[k+1]
                int SubProblem = DFS(ring,i,key,k+1,memo);
                //选择整体操作次数最少的
                //加一是因为按动俺就也是一次操作
                res = MATH_min(res,1+step+SubProblem);
            }
        }

        memo[r][k] = res;
        return res;

    }
    int findRotateSteps(string ring, string key) {
        int n = ring.size();
        int m = key.size();
        //创建 字符 -> 索引列表
        // char *map = new char[n];
        // for (int i=0;i<n;i++)
        //     map[i] = ring[i];

        int **memo = new int *[n];
        for (int i=0;i<n;i++)
            memo[i] = new int [m];

        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                memo[i][j] = 0;

        return DFS(ring ,0, key ,0,memo);
        //return dp(ring,key);
    }

    
    //解法2：动态规划
    int dp(string ring ,string key)
    {
        int n = ring.size();
        int m = key.size();

        int **dp = new int *[n+1];
        for (int i=0;i<n+1;i++)
            dp[i] = new int [m+1];
        
        for(int i=0;i<n+1;i++)
            for (int j=0;j<m+1;j++)
                dp[i][j] = 9999;

        //base case 
        for (int i=0;i<n+1;i++)
            dp[i][0] = 0;
        
        int pre_r=0; //每一轮寻找字符时,指针的初始位置(不一定为0)
        for (int j=0;j<key.size();j++)
         {   
            int step =0;
            int r = 0;
            for ( r = 0 ;r<ring.size();r++)
            {
                
                if (ring[r]==key[j])
                {
                    //从r到pre_r需要的步数，拨动指针的次数
                    step = MATH_abs(r,pre_r);
                    //选择顺时针还是逆时针
                    step = MATH_min(step,n-step);
                    //break;
                    dp[r][j+1] = MATH_min(dp[r][j+1],dp[pre_r][j] + step + 1);
                    
                }  
            }
            
        
        }
        
        int res = 65535;
        for (int i=0;i<n+1;i++)
        {
            res = MATH_min(res,dp[i][m]);
        }
        return res;

    }
    
    
};
// @lc code=end

/*
"godding"
"godding"
*/