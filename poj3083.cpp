#include<iostream>
#include<malloc.h>
#include<stdlib.h>
using namespace std;
char maze[50][50] = { '.' };
int height = 0, width = 0;
int sx = 0, sy = 0, ex = 0, ey = 0;
bool flag = false;
bool visited[50][50] = { false };
/*
0 y------->9
x
|
|
9
*/
int dir[4][2] =
{
    {0,-1}, //左0
    {-1,0}, //上1
    {0,1},  //右2
    {1,0},  //下3
};
int my_abs(int a, int b)
{
    return a > b ? a - b : b - a;
}
void DFS(int x, int y, int step, int dirs)
{
    //cout <<"step: " << step << endl;
    if (x == ex && y == ey)
    {
        flag = true;
        cout << step << " ";
        return;
    }
    if (!flag)
    {
        for (int i = 0; i <= 3  ; i++)
        {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if (nx < 0 || ny < 0 || nx >= height || ny >= width)
                continue;
            if (!flag && !visited[nx][ny] && maze[nx][ny] != '#' )
            {
                if (my_abs(dirs, i) != 2)
                {
                    cout << "方向：" << i << " ";
                    cout << nx << " " << ny << endl;
                    DFS(nx, ny, step + 1, i);
                }

            }
        }
    }
}

int main()
{
    cin >> height >> width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cin >> maze[i][j];
            if (maze[i][j] == 'S')
                sx = i, sy = j;
            if (maze[i][j] == 'E')
                ex = i; ey = j;
        }
    }
    flag = false;
    for (int i = 0; i < 4; i++)
        if (maze[sx + dir[i][0]][sy + dir[i][1]] == '.')
        {
            visited[sx][sy] = true;
            DFS(sx, sy, 1, i);
        }

}