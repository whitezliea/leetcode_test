/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
public:
   vector<string> res;
    vector<string> generateParenthesis(int n) 
    {
        if (n==0)
            return {};
        string s;
        //可放左括号数量与可放右括号数量都初始化为n
        backtrack(n,n,s);
        return res;
    }

    void backtrack(int left,int right,string &s)
    {
        //判断回溯结束条件,左右括号都已经用完
        if (left == 0&& right ==0)
        {
            res.push_back(s);
            return ;
        }
        //未放的左括号数量大于未放的右括号数量
        if (left > right)
            return ;
        //剪枝，去除不合理情况
        if(right<0||left <0)
            return ;
        
        //回溯操作，分别放左括号与右括号
        //做选择
        s.push_back('(');
        //递归进入下一层
        backtrack(left-1,right,s);
        //取消选择
        s.pop_back();

        s.push_back(')');
        backtrack(left,right-1,s);
        s.pop_back();

    }
};
// @lc code=end

/*
刷题总结：
    目前对回溯套路已经比较了解了，但是如何构建函数经验还是比较欠缺
    例如这题，我一开始是打算用数组的方式来做，用数组下标来表示左括号右括号的位置与数量，
    这样不如直接通过左右括号的数量好控制。
    其次，对于如何遍历子节点，还是不熟练，不一定要用for循环，for循环也只是为了列举所有子节点情况，
    因此也可以直接列举当前父节点下所有子节点的情况。
*/