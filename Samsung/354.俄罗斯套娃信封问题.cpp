/*
 * @lc app=leetcode.cn id=354 lang=cpp
 *
 * [354] 俄罗斯套娃信封问题
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int MATH_max(int n1,int n2)
    {
        return n1>n2?n1:n2;
    }
    void FUNC_sort(vector<vector<int>>& envelopes)
    {
        int i,j,t1,t2;
        for (j = 0;j<envelopes.size()-1;j++)
        {
            for (i = 0; i< envelopes.size()-1-j;i++)
            {
                //升序排序
                if ( envelopes[i][0] > envelopes[i+1][0])
                {
                    t1 = envelopes[i][0], t2 = envelopes[i][1];
                    envelopes[i][0] = envelopes[i+1][0];
                    envelopes[i][1] = envelopes[i+1][1];

                    envelopes[i+1][0] = t1;
                    envelopes[i+1][1] = t2;

                }
            }
        }
    }
    int dp(vector<vector<int>>& envelopes)
    {
        int len = envelopes.size();
        int l2 = envelopes[0].size(); // 2
        int *dp = new int[len];
        //base case
        for (int i=0;i<len;i++)
            dp[i] = 1;
        
        //对envelopes数组排序，优化成最长递增子序列问题
        FUNC_sort(envelopes);
        for (int i =0;i<len;i++)
            for (int j = 0;j<i;j++)
            {
                if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
                    dp[i] = MATH_max(dp[i] , dp[j]+1);
            }
        
        int res = 0;
        for (int i = 0; i < len;i++)
        {
            res = MATH_max(res,dp[i]);
        }

        return res;

    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        return dp(envelopes);
    }
};
// @lc code=end

/*
运行超时，推测原因1:排序优化
*/

