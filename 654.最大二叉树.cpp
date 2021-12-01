/*
 * @lc app=leetcode.cn id=654 lang=cpp
 *
 * [654] 最大二叉树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include<vector>
using namespace std;
class Solution {
public:
    
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0)
            return nullptr;
        return bulid(nums,0,nums.size()-1);
    }

    TreeNode* bulid(vector<int>& nums,int start,int end)
    {
        //base case
        if (start > end)
            return nullptr;

        int index = -1;//最大值的索引
        /*max_num = 0或者正数时就会报错，栈溢出
          max_num = 负数时就正常运行
          why ?
          max_num最好是负数，因为 index默认值为-1(即使不是-1也有有一些情况需要考虑)
          max_num 的值与 index 有关，也就是说，在遍历的过程中，必须要找到一个位置，以此为index赋值
          否则机会报错
        */
        int max_num = -1;
        //在[start,end]区间中寻找最大值
        for (int i = start;i<=end;i++)
        {
            if (nums[i] > max_num)
            { 
                max_num = nums[i];
                index = i;
            }
        }
        //TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
        TreeNode *root = new TreeNode();
        root->val = max_num;
        //递归调用构造左右子树
        root->left = bulid(nums,start,index-1);
        root->right = bulid(nums,index+1,end);

        return root;
    }
};
// @lc code=end

