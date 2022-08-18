/*
0 ---- 空地
1 ---- 石头
2 ---- 起始点
3 ---- 结束点
冰壶从起始点出发，向四周方向行动，在碰到冰壶之前都不会停止，
冰壶超出边界就判为失败，
冰壶只有在静止的时候才能改变方向，
冰壶碰到石头会停止，但是石头也会破碎，变为空地
sample input:
2 1
3 2
6 6
1 0 0 2 1 0
1 1 0 0 0 0
0 0 0 0 0 3
0 0 0 0 0 0
1 0 0 0 0 1
0 1 1 1 1 1
6 1
1 1 2 1 1 3
6 1
1 0 2 1 1 3
12 1
2 0 1 1 1 1 1 1 1 1 1 3
13 1
2 0 1 1 1 1 1 1 1 1 1 1 3
0 0
output:
1
4
-1
4
10
-1
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
int height = 0, width = 0;
int map[50][50] = {0};
int minipath = 9999;
int sx = 0, sy = 0, ex = 0, ey = 0;
bool flag = false;
/*
0 ---------y
|
|
|
x
*/
int dir[4][2] =
    {
        {-1, 0}, //左
        {0, -1}, //上
        {1, 0},  //右
        {0, 1}   //下
};
void DFS(int x, int y, int step)
{
    // cout <<"step: "<< step << endl;
    //  结束条件2 步数等10且未到达终点
    if (step >= 10)
    {
        flag = true;
        return;
    }

    //向四周方向进发，在碰到石头之前都不会停止
    //也就是说此时冰壶是静止的
    for (int i = 0; i < 4; i++)
    {
        // flag控制出界过，tag控制冰壶静止移动
        int flag = 1, tag = 0;
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        while (1)
        {
            //如果出界，就换个方向
            if (nx < 0 || ny < 0 || nx >= height || ny >= width)
            {
                flag = 0;
                break;
            }
            // 结束条件 到达终点
            if (map[nx][ny] == 3)
            {
                step++;
                //找到最小步数
                if (minipath > step)
                {
                    minipath = step;
                    // cout<<step<<endl;
                    return;
                }
            }

            //当碰到石头后，就停止，重新选择方向，即进入下一层递归
            if (map[nx][ny] == 1)
            {
                tag = 1;
                break;
            }

            //没有遇到其他情况，冰壶会一直滑下去
            nx += dir[i][0];
            ny += dir[i][1];
        }

        if (!flag)
            continue;
        if (tag)
        {
            // 若出现冰壶旁边就是石头的情况就跳过,冰壶无法动弹
            if (nx - dir[i][0] == x && ny - dir[i][1] == y)
            {
                continue;
            }
            //石头撞碎，变为空地
            map[nx][ny] = 0;
            //路径回头，并且路数加一
            // cout << nx - dir[i][0] << " " << ny - dir[i][1] << "方向：" << i << endl;
            DFS(nx - dir[i][0], ny - dir[i][1], step + 1);
            //进行回溯操作
            map[nx][ny] = 1;
        }
    }
}

int main()
{
    while (1)
    {
        //地 图 初 始 化
        flag = false;
        minipath = 9999;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                map[i][j] = 0;
        cin >> width >> height;
        if (width == 0 && height == 0)
            break;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == 2)
                {
                    sx = i;
                    sy = j;
                }
            }

        DFS(sx, sy, 0);
        // cout << "answer:";
        if (minipath <= 10)
            cout << minipath << endl;
        else
            cout << "-1" << endl;
    }
    return 0;
}
/*
 * 代码反思：
 * 慎用循环结构，特别是while(1)的形式，
 * 若达到某个要求，最好跳出while循环结果，直接开始while循环外一层的代码执行。
 */