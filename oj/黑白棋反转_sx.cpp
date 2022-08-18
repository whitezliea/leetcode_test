/*
题意可能描述不准确：
对于N*M的棋盘，有白棋和黑棋，可以按列翻转棋盘（即白棋变黑棋，黑棋变白棋），
先假设棋盘的一行都为黑棋时则判定为一条道路，现在给定次数K，必须将棋盘翻转K次，
问翻转之后最多有多少条道路，如果没有返回-1。
解：
0--->白棋，1--->黑棋
case1 :
input:
4 5 6
1 1 0 0 1
1 0 0 1 1
1 0 0 1 1
0 1 1 0 0
output:
2
方法1：DFS
*/

#include <iostream>
#include <malloc.h>
#include <stdlib.h>
using namespace std;
int height = 0, width = 0, filpnums = 0;
int maxPath = -1;

//翻转棋盘列的函数
void filp(int map[][50], int n)
{
    for (int i = 0; i < height; i++)
    {
        if (map[i][n] == 0)
            map[i][n] = 1;
        else if (map[i][n] == 1)
            map[i][n] = 0;
    }
}
bool isBlack(int map[][50], int n)
{
    for (int i = 0; i < width; i++)
    {
        if (map[n][i] != 1)
            return false;
    }
    return true;
}
//统计翻转棋盘后有多少路数
int countPath(int map[][50])
{
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        if (isBlack(map, i))
            count++;
    }
    return count;
}

void display(int map[][50])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void dfs(int map[][50], int k)
{
    if (k == filpnums + 1)
    {
        return;
    }
    for (int i = 0; i < width; i++)
    {
        //做选择
        filp(map, i);
        maxPath = maxPath > countPath(map) ? maxPath : countPath(map);
        //递归进入下一层
        dfs(map, k + 1);
        //撤销选择
        filp(map, i);
    }
    return;
}

int main()
{
    int map[50][50] = {0};
    cin >> height >> width >> filpnums;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cin >> map[i][j];
    dfs(map, 1);
    // filp(map,1);
    cout << endl;
    display(map);
    cout << maxPath << endl;
}

/*
case 1:
input:
4 5 6
1 1 0 0 1
1 0 0 1 1
1 0 0 1 1
0 1 1 0 0
output:
2

case 2:
input :
6 4 4
0 1 1 0
1 0 0 0
1 1 0 1
1 1 0 1
1 1 0 1
0 1 0 1
output:
3

方案2：位运算

*/