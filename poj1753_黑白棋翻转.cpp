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
const int inf =9999;
int ans=inf;
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


    if (isOK(map))
    {   
        if(ans > dep)
            ans = dep;
        return ;
    }
    
    //条件溢出
    if (y>=4||x>=4)
        return ;
    int nx = (x+1)%4;
    int ny = y+(x+1)/4;
    //选择翻转棋子
    filp(map,x,y);
    //进行下一状态的搜索
    dfs(map,nx,ny,dep+1);
    //在翻转一次棋子即选择不翻转棋子,也相当于回溯操作
    filp(map,nx,ny);
    dfs(map,nx,ny,dep);

    return ;
    
}
int main()
{
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            cin>>map[i][j];
    //对0-16的每个步长都进行搜索
    dfs(map,0,0,0);
    //display(map);
    if (ans != inf)
        cout<<ans<<endl;
    else
        cout<<"Impossible"<<endl;
    return 0;
}