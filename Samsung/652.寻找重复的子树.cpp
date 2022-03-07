/*
 * @lc app=leetcode.cn id=652 lang=cpp
 *
 * [652] 寻找重复的子树
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
#include<set>
#include<string>
using namespace std;
class Solution {
public:
    //记录所有子树
    multiset<string> memo; //备忘录
    //记录所有重复的子树节点
    vector<TreeNode*> res;
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        //还需要将res进行反序操作
        //[[4],[2,4]] --> [[2,4],[4]]
        reverse(res.begin(),res.end());
        return res;
    }

    string traverse(TreeNode* root)
    {   
        //base case 
        if (root == nullptr)
            return "#";
        //后序遍历
        string left = traverse(root->left);
        string right = traverse(root->right);
        string SubTree;
        SubTree.append(left);
        SubTree.append(","); //逗号起到分割数字，防止歧义性
        SubTree.append(right);
        SubTree.append(",");
        SubTree.append(std::to_string(root->val));
        //使用multiset.count()函数来统计子树出现的频率
        if (memo.count(SubTree) == 1)
        {
            //如果有子树重复，把自己加入结果列表
            res.push_back(root);
        }
        //不管有没有重复拆入memeo
        memo.insert(SubTree);
        
        return SubTree; 
    }
};
// @lc code=end
/*
 本题难点：如何描述二叉树，方法->序列化二叉树
          如何序列化二叉树 --> 使用字符串，并且要用进行各元素的分割，防止歧义性
*/