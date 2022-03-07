/*
 * @lc app=leetcode.cn id=226 lang=cpp
 * 题型：递归、二叉树
 * [226] 翻转二叉树
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
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        //base case
        //step1. 判断父节点不为空
        if (root == nullptr)
            return nullptr;
        
        //前序遍历位置
        //也可以放到后序遍历位置，但是不能放到中序遍历位置
        //因为放到中序位置遍历反转时，左右子节点位置已经发生变化
        //step2. root节点需要交换它的左右子节点
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;

        //step4. 让左右子节点继续反转它们的子节点
        invertTree(root->left);
        invertTree(root->right);

        //step5. 递归返回root节点
        return root;
    }
};
// @lc code=end

