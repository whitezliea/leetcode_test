/*
type 1  ---->  --0--  特性：可以与上下左右四个方向的积木进行连接
                 |

                 |
type 2  ---->    0    特性：可以与上下两个方向的积木进行连接
                 |

type 3  ---->  --0--  特性：可以与左右两个方向的积木进行连接

type 4  ---->  --0    特性：可以与左和下两个方向的积木进行连接
                 |

type 5  ---->    0--  特性：可以与右和下两个方向的积木进行连接
                 |

                 |
type 6  ---->    0--  特性：可以与右和上两个方向的积木进行连接

                 |
type 7  ---->  --0    特性：可以与左和上两个方向的积木进行连接
*/
/*
   0  -----> 5
   y
0x 0 4 0 5 3 4   //0代表此处没有积木 ，1~7代表七种不同的积木
   0 2 3 2 0 2
   3 1 3 1 3 7
   0 6 3 5 0 0
4  0 0 0 0 0 0
数组总结，注意数组横向递增方向与竖向递增方向
向下数字增加，向右数字增加
*/
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
int map[50][100] = {0};
struct Node
{
    int endstep = 0, type = 0;
} maze[50][100];
int vaild[7][4] = {
    {1, -1, -1, 1}, //上下左右 --type 1
    {1, -1, 0, 0},  //上下   --type 2
    {0, 0, -1, 1},  //左右    --type 3
    {1, 0, -1, 0},  //下左  --type 4
    {1, 0, 0, 1},   //下右  --type 5
    {0, -1, 0, 1},  //上右    --type 6
    {0, -1, -1, 0}  //上左   --type 7
};
//上下对x操作，左右对y操作
bool my_abs(int x, int y)
{
    return x == y ? true : false;
}
bool isVaild(int sx, int sy, int nx, int ny)
{
    cout << sx << " " << sy << "->" << nx << " " << ny << ",";
    cout << maze[sx][sy].type << " " << maze[nx][ny].type << endl;
    if (!my_abs(sx, nx))
    {
        for (int i1 = 0; i1 < 2; i1++)
            for (int i2 = 0; i2 < 2; i2++)
                if (sx + vaild[maze[sx][sy].type - 1][i1] == nx && nx + vaild[maze[nx][ny].type - 1][i2] == sx)
                    return true;
    }
    if (!my_abs(sy, ny))
    {
        for (int j1 = 2; j1 < 4; j1++)
            for (int j2 = 2; j2 < 4; j2++)
                if (sy + vaild[maze[sx][sy].type - 1][j1] == ny && ny + vaild[maze[nx][ny].type - 1][j2] == sy)
                    return true;
    }
    return false;
}

int main()
{
    int sx = 0, sy = 0, nx = 0, ny = 0, t1 = 0, t2 = 0;
    cin >> sx >> sy >> t1;
    cin >> nx >> ny >> t2;
    maze[sx][sy].type = t1;
    maze[nx][ny].type = t2;
    cout << isVaild(sx, sy, nx, ny) << endl;
}