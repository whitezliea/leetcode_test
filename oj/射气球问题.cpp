/*
题意大意：
射气球 ，有分数 1 2 3 4 四个气球
射中2 ，得分是2左右两个数字相乘，即1*3=3
射完之后，气球剩 1 3 4
射中1 ，因为左边没有，得分就是右边数字3
剩下气球3 4， 射中 4，得分3，剩下3，左右都没有了，射3就得分3
*/

#include <malloc.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

//存储气球位置与分数
int nums[50] = {0};
//判断气球是否被射中
int used[50] = {0};
//初始气球个数
int n = 0;
//射中气球得分
int sum = 0;
//最高气球得分
int maxsum = 0;

//存储射气球最大分数的的顺序
int maxpath[50] = {0};
int count = 1;

// path[]是否含有数字n
bool find_num(int path[], int n)
{
    for (int i = 1; i <= count; i++)
        if (path[i] == n)
            return true;
    return false;
}

//[0,i-1]
int left_score(int n1, int n2) //左边的数
{

    for (int i = n2; i >= n1; i--)
    {
        if (used[i] == 0 || used[i] == 2)
            return nums[i];
    }
    return 1;
}

//[i+1 ,n]
int right_score(int n1, int n2) //右边的数
{

    for (int i = n1; i <= n2; i++)
    {
        if (used[i] == 0 || used[i] == 2)
            return nums[i];
    }
    return 1;
}

void backtrack(int nums[], int path[])
{
    //结束条件 射完所有气球之后
    if (count == n + 1)
    {
        if (sum > maxsum)
        {
            for (int i = 1; i <= n; i++)
                maxpath[i] = path[i];
        }
        maxsum = maxsum > sum ? maxsum : sum;
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (find_num(path, i))
            continue;
        //表示已经射中
        used[i] = 1;
        path[count] = i;
        //只剩最后一个气球
        if (count == n)
        {
            // cout<<"sum="<<sum<<endl;
            sum = sum + nums[i];
        }
        else
            sum = sum + left_score(0, i - 1) * right_score(i + 1, n);
        count++;

        //递归进入下一层
        backtrack(nums, path);
        //撤销选择
        used[i] = 0;
        path[count] = 0;
        count--;
        if (count == n)
            sum = sum - nums[i];
        else
            sum = sum - left_score(0, i - 1) * right_score(i + 1, n);
    }
    return;
}

int main()
{
    //读入气球个数
    cin >> n;

    //存储射气球的顺序；
    int path[50] = {0};
    // nums[]与used[]初始化
    for (int i = 0; i < 50; i++)
    {
        nums[i] = 1;
        used[i] = 2;
        path[i] = 0;
        maxpath[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> nums[i];
        used[i] = 0;
    }

    backtrack(nums, path);
    cout << maxsum << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << maxpath[i] << " ";
    }
    return 0;
}
