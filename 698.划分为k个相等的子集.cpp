/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 */

// @lc code=start
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
/*
    //方法1：以数字的视角进行回溯算法
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        //base case 排除一些基本情况
        if (nums.size()==0)
            return false;
        int sum=0;
        for (int i=0;i<nums.size();i++)
            sum += nums[i];
        if (sum % k !=0)
            return false;
        //理论上每个桶（集合）中的数字之和
        int target = sum / k;
        //创建容量为k的bucket，记录每个桶的数字之和
        int *bucket = new int[k];
        for (int i=0;i<k;i++)
            bucket[i] = 0;
        int index = 0;//遍历到nums中的哪个数字
        int bucket_len = k;
        sort(nums.begin(),nums.end());
        return trackbucket(bucket,nums,target,index,bucket_len);
    }

    //递归穷举nums中的每个数字
    bool trackbucket(int bucket[],vector<int>& nums,int target,int index,int bucket_len)
    {   //如果index已经遍历完nums数组了，下标index已经超过了nums.size()-1了
        if (index == nums.size())
        {
            //检查所有桶中的数字是否都是target
            for(int i=0;i<bucket_len;i++)
                if(bucket[i] != target)
                    return false;
            //nums成功平分k个子集
            return true;
        }

         // 穷举 nums[index] 可能装入的桶
         for (int i = 0;i<bucket_len;i++)
         {
             //剪枝操作，桶装满了
            if (bucket[i] + nums[index] > target)
                continue;

            //进桶操作，将nums[index]装入bucket[i]
            bucket[i] += nums[index];
            //递归穷举下一个数字的选择
            if (trackbucket(bucket,nums,target,index+1,bucket_len))
                return true;
            //出桶操作，撤销选择
            bucket[i] -= nums[index];
         }
        
        //nums[index]无法插入bucket。
         return false;
    }
*/

    //方法2：以桶的视角进行回溯算法，
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        //base case 
        if (nums.size()==0|k>nums.size())
            return false;
        int sum=0;
        for (int i=0;i<nums.size();i++)
            sum += nums[i];
        if (sum %k !=0)
            return 0;
        int target  =sum/k;
        //int *bucket = new int [k] {0};
        //used数组含义，nums[i]是否被装入桶
        bool *used = new bool [nums.size()];
        for (int i=0;i<nums.size();i++)
            used[i] = false;
        int bucket = 0; //bucket里存的数
        int start = 0; //nums数字开始递归的下标
        return trackback(k,nums,bucket,start,used,target);
    }
    bool trackback(int k,vector<int>& nums,int bucket,int start,bool used[],int target)
    {   
        //说明所有的的桶已经装满
        if (k==0)
            return true;
        //当前桶装满了target
        //开始装下一个桶，下一个桶从0开始计数
        if (bucket == target )
        {
            return trackback(k-1,nums,0,0,used,target);
        }

        //如果没有装满桶
        // 从 start 开始向后探查有效的 nums[i] 装入当前桶
        for (int i= start;i<nums.size();i++)
        {
            //如果nums[i]处的数字已经被装入，剪枝操作
            if(used[i])
                continue;
            //如果nums[i]处的数字不能装入，剪枝操作
            if(bucket+nums[i]>target)
                continue;
            
            //做选择
            used[i] = true;
            bucket += nums[i];
            //进行下一步递归，递归穷举下一个数字是否装入当前桶
            if(trackback(k,nums,bucket,i+1,used,target))
                return true;
            //撤销选择
            used[i] = false;
            bucket -= nums[i];
        }
        return false;

    }


};
// @lc code=end

