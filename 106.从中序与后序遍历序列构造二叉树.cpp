/*
 * @lc app=leetcode.cn id=106 lang=cpp
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        //传入都是索引值
        return build(inorder,0,inorder.size()-1,
                    postorder,0,postorder.size()-1);
    }

    TreeNode* build(vector<int>& inorder, int inStart,int inEnd,
                    vector<int>& postorder,int posStart,int posEnd)
    {
        //base case 判断结束条件
        if (inStart > inEnd)
            return nullptr;
        //中序 左根右
        //后序 左右根
        int root_num = postorder[posEnd];
        //获取root在中序中所在的索引值，默认为0
        int index = 0 ; 
        for (int i=inStart;i<=inEnd;i++)
            if (root_num == inorder[i])
            {
                index = i;
                break;
            }
        //获取左子树的大小
        int left_size = index - inStart;
        
        //构造根节点
        TreeNode* root = new TreeNode();
        root->val = root_num;
        //递归构造左右子树
        root->left = build(inorder,inStart,index-1,
                            postorder,posStart ,posStart+left_size-1);
        root->right = build(inorder,index+1,inEnd,
                            postorder,posStart+left_size,posEnd-1);
        
        //返回根节点
        return root;
    }
};
// @lc code=end

