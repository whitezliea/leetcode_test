// 二分搜索的前提是数组整体有序
#include <iostream>
#include <vector>
using namespace std;

//左右闭合区间[]
int binarySearch(vector<int> nums, int target) // 基本的二分搜索
{
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) //当搜索区间为空时停止
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }
        else if (nums[mid] < target) // target在mid位置右侧 nums[mid] < target
        {
            low = mid + 1; //   更新区间左值[low,high] => [mid+1,high] 收缩左侧区间
        }
        else if (target < nums[mid]) // target在mid位置左侧 target < nums[mid]
        {
            high = mid - 1; //  更新区间右值[low,high] => [low,mid-1] 收缩右侧区间
        }
    }

    return -1;
}

///
//  寻找target左侧边界,搜索区间为[left,right]，通过修改left与right的值来收缩区间
int left_bound_plus(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            right = mid - 1; // 收缩右侧边界
        }
        else if (nums[mid] < target) //  target在mid位置右侧
        {
            left = mid + 1; //  搜索区间变为[mid+1,right]  收缩左侧区间
        }
        else if (target < nums[mid]) // target在mid位置左侧
        {
            right = mid - 1; //  搜搜区间变为[left,mid-1]  收缩右侧区间
        }
    }

    // 判断target是否存在与nums中
    // 此时target比所有数都大，返回-1
    if (left == nums.size())
        return -1;
    //判断一下nums[left]是不是target
    return nums[left] == target ? left : -1;
}

//寻找target左侧边界,搜索区间为[left,right)
int left_bound(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size(); //注意越界风险

    while (left < right) //注意left == right情况,此时终止
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            right = mid; //找到target时不返回，搜索左侧边界，收缩右侧搜索区间
        }
        else if (nums[mid] < target) //  target在mid位置右侧
        {
            left = mid + 1; // 收缩左侧区间
        }
        else if (target < nums[mid]) //  target在mid位置左侧
        {
            right = mid; // 收缩右侧搜索区间
        }
    }

    // 判断target是否存在与nums中
    // 此时target比所有数都大，返回-1
    if (left == nums.size())
        return -1;
    //判断一下nums[left]是不是target
    return nums[left] == target ? left : -1; //返回左边界值的下标
}

///

///
//寻找target右侧边界,搜索区间为[left,right]
int right_bound_plus(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            left = mid + 1; //收缩左侧区间
        }
        else if (nums[mid] < target) // target在mid右侧
        {
            left = mid + 1; //收缩左侧区间
        }
        else if (target < nums[mid]) // target在mid左侧
        {
            right = mid - 1; //收缩右侧区间
        }
    }

    //最后改成返回 left - 1;
    if (left - 1 < 0)
        return -1;
    return nums[left - 1] == target ? (left - 1) : -1;
}

//寻找target右侧边界,搜索区间为[left,right)
int right_bound(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size();

    while (left < right) //注意left == right情况,此时终止
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            left = mid + 1; //收缩左侧区间
        }
        else if (nums[mid] < target) // target在mid右侧
        {
            left = mid + 1; //收缩左侧区间
        }
        else if (target < nums[mid]) // target在mid左侧
        {
            right = mid; //收缩右侧区间
        }
    }
    // 判断 target 是否存在于 nums 中
    // 此时 left - 1 索引越界
    if (left - 1 < 0)
        return -1;
    // 判断一下 nums[left-1] 是不是 target
    return nums[left - 1] == target ? left - 1 : -1;
}

///

int main()
{
    vector<int> v2{-1, 0, 3, 5, 9, 9, 9, 12};

    int target = 9;
    int pos = binarySearch(v2, target);
    cout << "[low,right] ==> binary_search: " << pos << endl;

    int left_pos = left_bound(v2, target);
    cout << "[left,right) ==> left_bound " << left_pos << endl;

    int left_plus_pos = left_bound_plus(v2, target);
    cout << "[left,right] ==> left_bound_plus: " << left_plus_pos << endl;

    int right_pos = right_bound(v2, target);
    cout << "[left,right) ==> right_bound: " << right_pos << endl;

    int right_plus_pos = right_bound_plus(v2, target);
    cout << "[left,right] ==> right_bound_plus: " << right_plus_pos << endl;

    return 0;
}

/*
output:
[low,right] ==> binary_search: 5
[left,right) ==> left_bound 4
[left,right] ==> left_bound_plus: 4
[left,right) ==> right_bound: 6
[left,right] ==> right_bound_plus: 6
*/
