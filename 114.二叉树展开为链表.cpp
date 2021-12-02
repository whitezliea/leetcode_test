/*
 * @lc app=leetcode.cn id=114 lang=cpp
 * 题型：二叉树
 * [114] 二叉树展开为链表
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
//要求 展开后的单链表应该与二叉树 先序遍历 顺序相同
/*
操作: 保存根节点的右子节点，将左子节点指向右子节点并置左子节点为空，
      将之前保存的右子节点连接到已有的右子节点后面
*/
class Solution {
public:
    void flatten(TreeNode* root) {
        //base case 
        if (root == nullptr )
            return ;
        
        //需要先拉平左右子树才能进行后续操作
        flatten(root->left);
        flatten(root->right);

        //后序遍历位置
        //step1. 左右字数已经被拉平一条链表
        TreeNode *left = root->left;
        TreeNode *right = root->right;

        //step2. 将左子树作为右子树，同时左子树置为空
        root->left = nullptr;
        root->right = left;

        //step3. 将原先的右子树接到当前右子树的后面
        TreeNode *p = root;
        while (p->right != nullptr)
        {
            p = p->right;
        }
        p->right = right; //先的右子树

        return ;
    }


};
// @lc code=end
//总结：思考出每一个节点需要做什么
