/*
大致题意：给定一个4*4的棋盘，上面有黑棋与白棋，其中一个棋子翻转时，
会带到旁边的棋子也翻转，当棋盘上全为黑棋或者全为白棋时则视为完成了黑白棋翻转，
对于已有棋盘上的棋子，问需要几步翻转才能到达完成黑白棋翻转。
Sample Input
bwwb
bbwb
bwwb
bwww

Sample Output
4
*/
#include<iostream>
#include<stdlib.h>
#include<malloc.h>
using namespace std;
char map[4][4]={'b'};
int maxnums=16;
int minipath=0;
int step=0;
int flag=false;
int dir[4][2]={
    {1,0},
    {-1,0},
    {0,1},
    {0,-1}
};
bool isOK(char map[][4])
{
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(map[0][0]!=map[i][j])
                return false;
    return true;
}
void display(char map[][4])
{
    for (int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            cout<<map[i][j]<<" ";
        cout<<endl;
    }

}
void filp(char map[][4],int x,int y)
{
    //自己翻转
    if (map[x][y]=='w')
        map[x][y]='b';
    else if(map[x][y]=='b')
        map[x][y]='w';
    //四周翻转
    for (int i=0;i<4;i++)
    {
        int dx=x+dir[i][0];
        int dy=y+dir[i][1];
        if (dx>=0||dy>=0||dx<4||dy<4)
        {
            if (map[dx][dy]=='w')
                map[dx][dy]='b';
            else if(map[dx][dy]=='b')
                map[dx][dy]='w';
        }
    }
}

void dfs(char map[][4],int x,int y,int dep)
{
    //cout<<step<<endl;
    // 搜索深度与步数相同时就回溯
    if (step==dep)
    {
        if (isOK(map))
            flag = true;
        return ;
    }
    //如果已经满足条件就返回
    if (flag||x==4)
        return ;
    //选择翻转棋子
    filp(map,x,y);
    //进行下一状态的搜索
    if (y<3)
        dfs(map,x,y+1,dep+1);
    else
        dfs(map,x+1,0,dep+1);
    //在翻转一次棋子即选择不翻转棋子,也相当于回溯操作
    filp(map,x,y);
    if (y<3)
        dfs(map,x,y+1,dep);
    else
        dfs(map,x+1,0,dep);

    return ;
    
}
int main()
{
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            cin>>map[i][j];
    //对0-16的每个步长都进行搜索
    for ( step = 0; step <= 16; step++)
    {
        dfs(map,0,0,0);
        if (flag)
            break; //如果成功了，该步长就是最小值
    }
    
    //display(map);
    if (flag)
        cout<<step<<endl;
    else
        cout<<"Impossible"<<endl;
    return 0;
}