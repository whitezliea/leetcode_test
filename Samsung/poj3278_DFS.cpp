/*
题意：就是给出a和b点的横坐标，求到a，b的最小行动次数，
每次可以向左或向右移动一步，即横坐标加1或者减1，也可以横坐标变成原来的两倍。
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define MAXSIZE 10000
int minstep=9999;
int a=0,b=0;
//a--->b
bool visited[MAXSIZE] = {false};

void DFS(int cnt,int step)
{
    if (cnt<0||cnt>b)
        return;
    //cout<<cnt<<" "<<step<<endl;
    if (cnt == b)
    {
        if (minstep > step)
            minstep = step;
        return ;
    }

    if (visited[cnt] == false)
    {
        //向右走一步
        visited[cnt] = true;
        cnt = cnt +1;
        DFS(cnt,step+1);
        cnt = cnt - 1;
        visited[cnt] = false;

        //向左走一步
        visited[cnt] = true;
        cnt = cnt -1;
        DFS(cnt,step+1);
        cnt = cnt + 1;
        visited[cnt] = false;
        
        //两倍
        visited[cnt] = true;
        cnt = cnt *2;
        DFS(cnt,step+1);
        cnt = cnt /2;
        visited[cnt] = false;
    }
    
    return ;
}

int main()
{
    cin>>a>>b;
    DFS(a,0);
    cout<<minstep<<endl;
    return 0;
}