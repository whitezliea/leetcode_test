/*
问题描述：现在有七种不同类型的积木，分布在一个长度为width，高度为hight的图中，
积木类型有：      |
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

在了解积木的类型之后，在一个给定的 width * hight 的图中，给定起始点(i,j)与可走步数，
问从起始点的积木开始，向积木连接方向寻找，每寻找一个新的连接的积木，可走步数-1，
在可走步数走完之后，最多能找到几根积木（算上起始点）。

需要输入的参数：
input:
5 6           //6->width 5->height
(2,1)  3      //(2,1)起始点坐标，3-->可走步数
   0  -----> 5
   y
0x 0 4 0 5 3 4   //0代表此处没有积木 ，1~7代表七种不同的积木
   0 2 3 2 0 2
   3 1 3 1 3 7
   0 6 3 5 0 0
4  0 0 0 0 0 0
数组总结，注意数组横向递增方向与竖向递增方向
output:
10
*/
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
// int map[50][100] = { 0 };
struct Node
{
    int endstep = 0, type = 0;
} maze[50][100];
int vis[50][100] = {0};
int find_num = 0;
int dir[4][2] = {
    {0, 1},  //向上
    {0, -1}, //向下
    {-1, 0}, //向左
    {1, 0}   //向右
};
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
int width = 0, height = 0;

bool my_abs(int x, int y)
{
    return x == y ? true : false;
}
//判断能否与附近的积木进行连接
bool isVaild(int sx, int sy, int nx, int ny)
{
    /*cout << sx << " " << sy << "->" << nx << " " << ny << ",";
    cout << maze[sx][sy].type - 1 <<" " << maze[nx][ny].type - 1 << endl;*/
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
//判断是否越界
bool in(int x, int y)
{
    if (x < 0 || y < 0 || x >= height || y >= width || maze[x][y].type == 0)
    {
        // cout << "false next " << x << "," << y << endl;
        return false;
    }
    return true;
}
// BFS解法

// Backtrack解法 回溯算法
void Backtrack(int sx, int sy)
{
    // Backtrack 结束条件
    if (maze[sx][sy].endstep == 0)
        return;
    if (in(sx, sy))
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = sx + dir[i][0];
            int ny = sy + dir[i][1];
            // cout << "have next " << nx << "," << ny << endl;
            //将要连接的下一个积木未越界且未被访问时
            if (in(nx, ny) && vis[nx][ny] == 0)
            {
                // cout << "ture next " << nx <<"," << ny << endl;
                //两个积木可以被连接
                if (isVaild(sx, sy, nx, ny))
                {
                    maze[nx][ny].endstep = maze[sx][sy].endstep - 1;
                    cout << sx << " " << sy << "->" << nx << " " << ny << " ";
                    cout << " ed: " << maze[nx][ny].endstep << " type: " << maze[nx][ny].type << endl;
                    //(sx,sy)设置已访问
                    vis[sx][sy] = 1;
                    find_num++;
                    //进行下一层回溯
                    Backtrack(nx, ny);
                    //撤销访问记录
                    vis[sx][sy] = 0; //这行代码加不加都行，这是DFS与回溯算法的区别
                }
            }
        }
    }

    return;
}

/* 因为要考虑相邻两根积木之间的连接性，不能直接暴力遍历
void DFS(int sx, int sy, int endstep)
{
    //DFS结束条件
    if (maze[sx][sy].type == -1 || endstep == 0)
        return;
    //未越界
    if (in(sx, sy))
    {
        //拿走sx,sy处的积木，类型记为-1
        maze[sx][sy].type = -1;
        DFS(sx - 1, sy, endstep - 1);
        DFS(sx + 1, sy, endstep - 1);
        DFS(sx, sy - 1, endstep - 1);
        DFS(sx, sy + 1, endstep - 1);
    }
    return;
}
*/

int main()
{
    int sx = 0, sy = 0, endstep = 0;
    cin >> height >> width >> sx >> sy >> endstep;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cin >> maze[i][j].type;
    // cout << i << " " << j<<" ";
    // for (int i = 0; i < height; i++)
    //     for (int j = 0; j < width; j++)
    //         cout << maze[i][j].type<<" ";

    maze[sx][sy].endstep = endstep;
    cout << "help" << endl;
    Backtrack(sx, sy);
    cout << find_num + 1 << endl; //加1是因为要加上本身(sx,sy)处的积木

    // DFS(sx,sy,endstep);
    // int counts;
    // for (int i = 0; i < height; i++)
    //     for (int j = 0; j < width; j++)
    //         if(maze[i][j].type == -1)
    //             counts++;
    // cout<<counts<<endl;
}
/*
case 1:
input :
5 6 2 1 3
0 4 0 5 3 4
0 2 3 2 0 2
3 1 3 1 3 7
0 6 3 5 0 0
0 0 0 0 0 0
output :10

case 2:
input :
6 7 4 2 4
0 0 0 0 0 0 0
0 3 2 0 0 0 0
0 0 5 7 0 0 0
0 4 2 5 2 0 0
3 1 1 2 0 2 0
0 2 6 1 3 3 7
output: 14

*/
/*
  本题遇到的坑：
  1、DFS与回溯算法弄混淆
  什么是DFS算法
  从起始点向四周扩散，直至遍历完所有情况
  什么是回溯算法
  其核心就是 for 循环里面的递归，在递归调用之前「做选择」，在递归调用之后「撤销选择」
  2、对于数组的排列顺序不太清楚
  3、对于积木对接条件没有考虑仔细
  反思之处：
  模块化考虑函数功能
*/