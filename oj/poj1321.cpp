#include <iostream>
#include <stdlib.h>
using namespace std;
char map[8][8] = {'.'};
// n是棋盘规格，k是棋子数量
int n = 0, k = 0;
int nums = 0;

int DFS(int col, int m)
{
    //棋子都放完
    if (m == k)
    {
        return 1;
    }
    //限制在一行进行操作，一行一行进行操作
    int t = n - k + m + 1, res = 0;
    for (int i = col; i < t; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == '#')
            {
                map[i][j] = '.';
                res += DFS(i + 1, m + 1);
                map[i][j] = '#';
            }
        }
    }
    return res;
}

int main()
{

    while (1)
    {
        //初始化
        nums = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                map[i][j] = '.';
        cin >> n >> k;
        if (n == -1 && k == -1)
            break;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        int t = DFS(0, 0);
        // cout << "tesy" << endl;

        cout << t << endl;
    }
    return 0;
}

/*
#是棋盘区域,.是空白区域
Sample Input
2 1
#.
.#
4 4
...#
..#.
.#..
#...
5 2
....#
...#.
..#..
.#...
#....
-1 -1


Sample Output
2
1
5
*/
