/*
 * @lc app=leetcode.cn id=100 lang=cpp
 *
 * [100] 相同的树
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

    bool Compare(TreeNode *p, TreeNode *q)
    {
        if (p==nullptr && q!=nullptr) //p指针为空，q指针不为空
            return false;
        else if (p!=nullptr && q==nullptr)
            return false;
        else if (p==nullptr&&q==nullptr)
            return true;
        else if (p->val!=q->val)
            return false;

        bool b1 = Compare(p->left,q->left);
        bool b2 = Compare(p->right,q->right);
        bool isSame = b1&&b2;
        return isSame;
        
    }
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return Compare(p,q);
    }

};
// @lc code=end

