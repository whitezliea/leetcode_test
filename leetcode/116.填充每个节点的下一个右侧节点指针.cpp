/*
 * @lc app=leetcode.cn id=116 lang=cpp
 * 题型：递归、二叉树
 * [116] 填充每个节点的下一个右侧节点指针
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        //base case 
        if (root == nullptr)
            return nullptr;
        //拆分问题,并且连接两个节点
        connectTwoNode(root->left,root->right);
        return root; 
    }

    void connectTwoNode(Node *node1,Node *node2)
    {
        //step1. 判断左右节点必须不为空才能进行连接
        if (node1==nullptr||node2==nullptr)
            return ;
        
        //前序遍历位置
        //step2. 具体的连接动作，将传入的两个子节点进行连接
        node1->next = node2;
        //step3. 连接相同父节点的两个子节点
        connectTwoNode(node1->left,node1->right);
        connectTwoNode(node2->left,node2->right);
        //step4. 连接跨越父节点的连个子节点
        connectTwoNode(node1->right,node2->left);
        //step5. 返回
        return ;
    }

};
// @lc code=end

/*
刷题总结：
把一个大问题拆分成一个无法再分割的小问题，并且递归执行
*/