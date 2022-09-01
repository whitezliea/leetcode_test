#include <functional>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void print(T q, string name)
{
    cout << name << ": \t";
    for (auto n : q)
        cout << n << ' ';
    cout << '\n';
}

template <typename T>
void print_queue(T q, string name)
{ // NB: pass by value so the print uses a copy
    vector<typename T::value_type> content;
    while (!q.empty())
    {
        content.push_back(q.top());
        q.pop();
    }
    print(content, name);
}

int main()
{
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    print(data, "data");

    priority_queue<int> q1; // Max priority queue
    for (int n : data)
        q1.push(n);
    print_queue(q1, "q1");

    // Min priority queue
    // std::greater<int> makes the max priority queue act as a min priority queue
    priority_queue<int, vector<int>, greater<int>> minq1(data.begin(), data.end());
    print_queue(minq1, "minq1");

    // Second way to define a min priority queue    //can't be used
    // priority_queue minq2(data.begin(), data.end(), greater<int>()); ==> C++23特性
    // print_queue(minq2, "minq2");

    // Using lambda to compare elements. 自定义比较器
    auto cmp = [](int left, int right)
    {
        // return (left ) < (right ); //Max priority queue
        return (left ^ 1) < (right ^ 1);
    };

    priority_queue<int, vector<int>, decltype(cmp)> q5(cmp);
    for (int n : data)
    {
        q5.push(n);
    }
    print_queue(q5, "q5");

    // Using a custom function object to compare elements. 重写仿函数
    struct customLess
    {
        bool operator()(const int l, const int r) const
        {
            return l < r;
        }
    };

    // priority_queue minq3(data.begin(), data.end(), customLess);  ==> C++ 23特性
    priority_queue<int, vector<int>, customLess> q6;
    for (int n : data)
    {
        q6.push(n);
    }
    print_queue(q6, "q6");

    /* 类型被指定为结构体了
        // 重写 < 运算符
        struct cmp_less //
        {
            int val;
            bool operator<(const cmp_less CMP) const
            {
                return this->val < CMP.val;
            }
        };

        priority_queue<cmp_less> q7;
        for (int n : data)
        {
            q7.push(cmp_less{n});
        }
        print_queue(q7, "q7");
    */
    return 0;
}