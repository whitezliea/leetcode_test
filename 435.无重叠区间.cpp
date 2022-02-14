/*
 * @lc app=leetcode.cn id=435 lang=cpp
 *
 * [435] 无重叠区间
 */

// @lc code=start
#include<vector>
#include<algorithm>
using namespace std;
    bool cmp1(const vector<int> &a, const vector<int> &b)
    {
	    return a[0] > b[0];
    }

class Solution {
public:
    //重写sort

    void sort_end(vector<vector<int>>& intervals)
    {
        int temp1=0,temp2=0;
        int n = intervals.size();
        for (int i=n-1;i>=0;i--)
        {
            for (int j=0;j<i;j++)
            {
                if (intervals[j][1] > intervals[j+1][1])
                {
                    temp1 = intervals[j][0];
                    temp2 = intervals[j][1];
                    intervals[j][0] = intervals[j+1][0];
                    intervals[j][1] = intervals[j+1][1];
                    intervals[j+1][0] = temp1;
                    intervals[j+1][1] = temp2;
                }
            }
        }
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int len = intervals.size();
        //按照end升序排序
        //sort_end(intervals);
        sort(intervals.begin(),intervals.end(),cmp1);
        //至少有一个区间不相交
        int count = 1;
        //排序后，第一个区间就是x
        int x_end = intervals[0][1];
        //找到重叠的区间
        for (int i=0;i<len;i++)
        {
            int  start = intervals[i][0];
            if (start >= x_end)
            {
                //找到下一个区间
                count++;
                x_end = intervals[i][1];
            }
        }

        return len - count;
    }
};
// @lc code=end
//冒泡排序算法超时


