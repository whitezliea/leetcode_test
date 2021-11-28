/*
题意：
给你一个可装载重量为 W 的背包和 N 个物品，每个物品有重量和价值两个属性。
其中第 i 个物品的重量为 wt[i]，价值为 val[i]，现在让你用这个背包装物品，最多能装的价值是多少？
inupt:
N = 3, W = 4
wt = [2, 1, 3]
val = [4, 2, 3]

output: 6
*/
#include<iostream>
#include<stdio.h>
using namespace std;


int knapsack(int W,int N,int wt[],int val[])
{
    //base case 初始化
    //创建dp二维数组
    int **dp = new int*[N+1];
    for(int i=0;i<N+1;i++)
        dp[i] = new int[W+1];
    //dp数组初始化
    for (int i=0;i<N+1;i++)
        for(int j=0;j<W+1;j++)
            dp[i][j]=0;
    
    //状态转移方程
    for(int i=1;i<=N;i++)
        for(int w=1;w<=W;w++)
            if(w-wt[i-1]<0)//装入的重量超过了限制
                //这种情况下只能选择不装入背包
                dp[i][w]=dp[i-1][w];
            else 
                //装入或者不装入背包，择优
                dp[i][w] = dp[i-1][w-wt[i-1]]+val[i-1] > dp[i-1][w]? //求两者中的最大值
                dp[i-1][w-wt[i-1]]+val[i-1] : //把第i个物品装入背包
                dp[i-1][w];     //不把第i个物品装入背包
    
    //返回最后终点状态值
    return dp[N][W];
}

int main()
{
    //一个可装载重量为 W 的背包和 N 个物品
    int W =4,N = 3;
    //第 i 个物品的重量为 wt[i]，价值为 val[i]
    int wt []= {2, 1, 3};
    int val []= {4, 2, 3};
    cout<<knapsack(W,N,wt,val)<<endl;
    return 0;
}

/*
解题思路：

第一步：明确【状态】和【选择】
状态：
# 背包的空余容量还剩多少 -----> W
# 可选择的物品还有哪些 ----> N
选择：
# 把这个物品装进背包
# 不把这个物品装进背包

第二步：明确dp数组的定义
 dp[i][w]的含义为：
 对于前i个物品，当背包的容量为w时，可以装的最大值时dp[i][w]

 比如说d[3][5]=6的含义为：
 对于给定的一些列物品中，若只对前3个物品进行选择，当背包容量为5时，最多可以装下的价值为6

 根据此定义，可得出
 base case 为 dp[0][...] = dp[0][...] = 0,我们想计算的结果时dp[N][W]

 第三步：根据选择写出状态转移逻辑方程

*/