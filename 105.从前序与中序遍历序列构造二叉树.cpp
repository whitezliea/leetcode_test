/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
 TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return build(preorder, 0, preorder.size() - 1,
                     inorder, 0, inorder.size() - 1);
    }
    TreeNode *build(vector<int> &preorder, int prestart, int preend,
                    vector<int> &inorder, int instart, int inend)
    {
        //base case 判断结束条件
        if (prestart > preend)
            return nullptr;

        //前序遍历 根左右
        //后序遍历 左根右
        //step1. 获取根节点
        int root_num = preorder[prestart];
        //step2. 获取根节点在中序遍历结果数组中的位置索引
        int index =0;
        for (int i =instart ;i<=inend;i++)
            if (root_num == inorder[i])
            {
                index = i;
                break;
            }
        //通过中序结果算出左子树的大小，root节点索引值减去起点索引值
        int left_size  = index - instart;
        //TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
        TreeNode *root = new TreeNode();
        root->val = root_num;
        
        //递归构建左右子树
        root->left = build(preorder, prestart+1 , prestart + left_size ,
                        inorder,instart,index-1);
        root->right= build(preorder,prestart + left_size + 1 ,preend,
                            inorder,index+1,inend);

        //返回根节点
        return root;
        
    }
};
// @lc code=end

