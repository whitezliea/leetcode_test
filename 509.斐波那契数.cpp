/*
 * @lc app=leetcode.cn id=509 lang=cpp
 * 题型：动态规划
 * [509] 斐波那契数
 */

// @lc code=start
class Solution {
public:
/*
//解法1：暴力穷举递归算法
    int fib(int n) {
        if(n==0||n==1)
            return n;
        return fib(n-1)+fib(n-2);
    }  
*/

/*
//解法2：自动向下的带备忘录的递归算法。
    int fib(int n) {
        //创建备忘录，初始化为0
        int  *memo = new int [n+1]{0};
        
        return slove(memo,n);
    }

    int slove(int memo[],int n)
    {
        if(n==0||n==1)
            return n;
        //已经计算过了，就不用继续计算了
        if(memo[n]!=0)
            return memo[n];
        memo[n] = slove(memo,n-1) + slove(memo,n-2);
        return memo[n];
    }
*/

/*
//解法3：动态规划数组的迭代算法
    int fib(int n) {
        if(n==0)
            return 0;
        //创建DP数组
        int *dp = new int[n+1]{0};
        //创建base case
        dp[0]=0; dp[1]=1;
        //进行迭代操作 2~N
        for(int i=2;i<n+1;i++)
        //明确状态转移方程
            dp[i]=dp[i-1]+dp[i-2];
        //迭代完之后，返回最后一个数组
        return dp[n];
    }
*/

//解法4：优化空间复杂度的DP数组
    int fib(int n) {
        if(n==0||n==1)
            return n;
        //递推关系
        int prev=0,cur=1;
        int sum=0;
        for(int i=2;i<=n;i++)
        {
            sum = prev + cur;
            prev = cur;
            cur = sum;
        }
        return sum;
    }
    
};
// @lc code=end

