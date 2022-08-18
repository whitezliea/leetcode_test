#include <iostream>
using namespace std;
int datas[11] = {0}; //存储数组
int N;               //输入数的个数
int Ans;             //所求答案
int equal_index;     //等号坐标

void dfs(int index, int left_value, int right_value)
{
    if (left_value == right_value && index == N - 1)
    {
        Ans++;
        return;
    }

    if (index == N - 1)
    {
        return;
    }

    if (index < equal_index) // 等号左边做计算
    {
        dfs(index + 1, left_value + datas[index], right_value);
        dfs(index + 1, left_value * datas[index], right_value);
        dfs(index + 1, left_value % datas[index], right_value);
    }

    if (index >= equal_index) // 等号左边做计算
    {
        dfs(index + 1, left_value, right_value + datas[index + 1]);
        dfs(index + 1, left_value, right_value * datas[index + 1]);
        dfs(index + 1, left_value, right_value % datas[index + 1]);
    }
}
/*
eg:
index      0 1 2 3 4
datas      2 8 5 1 10
           |     |
           |  euqal_index/right_vlaue
           left_vlaue
    -->   2%8*2=1*10
*/

void solution()
{
    for (int i = 1; i <= N - 1; i++)
    {
        equal_index = i;
        int left_value = datas[0], right_value = datas[i];
        dfs(1, left_value, right_value);
    }
}

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> datas[i];
    }
}

int main()
{
    input();
    solution();
    cout << "Ans: " << Ans << endl;
}
/*
5
2 8 5 1 10

Ans: 5
*/