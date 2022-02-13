/*
 * @lc app=leetcode.cn id=241 lang=cpp
 *
 * [241] 为运算表达式设计优先级
 */

// @lc code=start
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    int func(int N)
    {
        if (N==0)
            return 1;
        int a=1;
        for (int i=0;i<N;i++)
        {
            a = a*10;
        }
        return a;
    } 
    int S_toi(string s)
    {
        int a = 0;
        int len = s.size();
        for (int i=len-1;i>=0;i--)
        {
            a += (s[i]-'0') * func(len-1-i);
        }
        return a;
    } 
    vector<int> mergre(string Str)
    {
        vector<int> res;
        int length = Str.size();
        //首先循环字符串
        for (int i=0;i<length;i++)
        {
            char c = Str[i];
            //若找到字符串中的运算符
            if (c=='-' || c=='*' || c =='+')
            {
                //分
                vector<int> left;
                left = mergre(Str.substr(0,i));
                vector<int> right;
                right = mergre(Str.substr(i+1));
                //治
                //通过子问题的结果，合成原问题的结果
                for(int i1 = 0;i1<left.size();i1++)
                {
                    for (int i2=0;i2<right.size();i2++)
                    {
                        if (c=='+')
                            res.push_back(left[i1]+right[i2]);
                        else if (c=='-')
                            res.push_back(left[i1]-right[i2]);
                        else if (c=='*')
                            res.push_back(left[i1]*right[i2]);
                    }
                }
            }
        }
        
        //base case
        //如果 res为空
        if(res.empty())
        {
            int a=S_toi(Str);
            res.push_back(a);
        }
        return res;
    }
    vector<int> diffWaysToCompute(string expression) {
        return mergre(expression);
    }
};
// @lc code=end

