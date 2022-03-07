#include<iostream>
#include<stdlib.h>
using namespace std;
//int map[8][8]={0};
bool visited[8][8]={false};
bool flag = false;
int p=0,q=0; 

int dir1[8][2] = {
-1, -2, 
1, -2, 
-2, -1,
2, -1, 
-2, 1,
2, 1,
-1, 2,
1, 2
};

char b[200]={'0'};
void dfs(int x,int y,int step)
{
    //结束条件
    if (step == p*q)
    {
        cout<<"A1";
        for (int i=2;i<2*step;i++)
            cout<<b[i];
        flag = true;
        cout<<endl<<endl;
        return ;
    }
    if (!flag)
        for(int i=0;i<8;i++)
        {
            int nx=x+dir1[i][0];
            int ny=y+dir1[i][1];
            if (nx<1||ny<1||nx>p||ny>q)
                continue;
            if (!visited[nx][ny])
            {
                visited[nx][ny]=true;
                b[2*step] = 'A' + ny - 1;
                b[2*step+1] = '1' + nx - 1;
                //cout<<nx<<" "<<ny<<" "<<step<<endl;
                dfs(nx,ny,step+1);
                visited[nx][ny] = false;
            }
        }
}

int main()
{
    int t=0,ca=0;
    cin>>t;
    while (t--)
    {
        cin>>p>>q;
        cout << "Scenario #" << ++ca << ':' << endl;
        for (int i=0;i<8;i++)
            for (int j=0;j<8;j++)
                visited[i][j]=false;
        flag = false;
        visited[1][1] = true;
        dfs(1,1,1);
        if (!flag) 
            cout << "impossible" << endl << endl;
    }
    
    return 0;
}