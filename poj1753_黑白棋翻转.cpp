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
    
    //当前状态不反转棋子，进行下一状态的搜索
    dfs(map,nx,ny,dep);
    //翻转棋子
    filp(map,x,y);
    //进入下层状态
    dfs(map,nx,ny,dep+1);
    //回溯操作
    filp(map,x,y);

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

/*
代码反思：
对于本题，因为棋子有翻转或者不翻转的选择
不翻转的情况下：
    dfs(nx,ny,dep);直接进入下一层递归，步数也不增加，也无需做回溯操作
翻转的情况下：
    flip(nx,ny);  //翻转操作
    dfs(nx,ny,dep+1); //进入下一层递归，需要回溯操作
    filp(nx,ny);  //回溯操作
DFS的思路就是遍历当前状态的所有情况并且进入下一层，然后递归返回后进行回溯操作。
*/