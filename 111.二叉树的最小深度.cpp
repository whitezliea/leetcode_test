/*
 * @lc app=leetcode.cn id=111 lang=cpp
 *
 * [111] 二叉树的最小深度
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

/* //自定义队列
#define MAXSIZE 100
class _Queue
{
private:
    struct TreeNode data[MAXSIZE];
    int front; //队首指针
    int rear;  //队尾指针
    int size; //队列大小
public:
    _Queue();//构造函数
    void addQueue(TreeNode *t);
    TreeNode *delQueue();
    bool isEmpty();
    bool isFull();
    TreeNode *getFront();
    int getSize();
};

_Queue::_Queue()
{
    front=-1;
    rear =-1;
    size = 0;
}
void _Queue::addQueue(TreeNode *t)
{
    if(isFull())
        return;
    rear++;
    rear = rear%MAXSIZE;
    size++;
    data[rear] = *t;
}
TreeNode *_Queue::delQueue()
{
    if(isEmpty())
        return nullptr;
    front++;
    front = front%MAXSIZE;
    size--;
    return &data[rear];
}

bool _Queue::isEmpty()
{
    return size==0;
}

bool _Queue::isFull()
{
    return size==MAXSIZE; //MAXSIZE为队列大小
}

TreeNode* _Queue::getFront()
{
    int t = front+1;
    return &data[t];
}

int _Queue::getSize()
{
    return size;
}
*/
#include<queue>
using namespace std;
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr)
            return 0;
        queue<TreeNode *> q;
        q.push(root);
        //root 本身就是一层，depth初始化为1
        int depth = 1;
        while (!q.empty())
        {
            int sz = q.size(); //记录当前栈大小，注意栈大小是在实时变化的

            //将当前队列中的所有节点向四周扩散
            for(int i=0;i<sz;i++)
            {     
                //注意获取以及删除节点的时机，在for循环内外结果不同
                //获取队首节点
                TreeNode *cur = q.front();
                //删除队首节点
                q.pop();
                //判断是否到达终点
                if(cur->left==nullptr && cur->right==nullptr)
                    return depth;
                if(cur->left!=nullptr)
                    q.push(cur->left);
                if(cur->right!=nullptr)
                    q.push(cur->right);
                
            }
            //这里增加步数
            depth++;
        }
        return depth;
        
    }
};
// @lc code=end

