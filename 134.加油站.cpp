/*
 * @lc app=leetcode.cn id=134 lang=cpp
 *
 * [134] 加油站
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    //数学解法 如果 sum(gas[...]) < sum(cost[...])，
    //总油量小于总的消耗，那肯定是没办法环游所有站点的。
    int math(vector<int>& gas, vector<int>& cost)
    {
        int n =gas.size();
        //相当于图像中的坐标点和最低点
        int sum = 0,minSum = 0;
        int start = 0;
        for (int i=0; i< n;i++)
        {
            sum += gas[i] - cost[i];
            if (sum<minSum)
            {
                //经过第i个站点后，是sum到达新低
                //所以站点i+1就是最低点（起点）
                start = i+1;
                minSum = sum;
            }
        }
        if (sum <0)
        {
            //若总油量小于总的消耗，无解
            return -1;
        }
        //环形数组的特性
        //如果start 起点为节点n即最后一个点，即是从0开始
        return start == n?0:start;
    }
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        //解法1：数学图像解法
        return math(gas,cost);
        //解法2：贪心算法（待更
        //return best(gas,cost);
    }
};
// @lc code=end

