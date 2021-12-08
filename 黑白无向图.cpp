/*
点的数字随便标
主要是点数v和边数e
然后输入9条边连接的两个点
每个点只能填黑或白2种颜色
要求一条边连接的两个点不同色
所有点填上颜色，输出#+测试案例号+白色的点总数+每个白色点的号码
每个测试案例其实有至少两种情况，黑白一换也是符合要求的，都给过。
无法按要求填满两色的案例输出-1
*/
 // 参考资料：https://blog.csdn.net/qq_44766883/article/details/106760748
/*
case 1:

1---2---3
|  /|  /
| 5 | 7
|/  |/
4---6
v e
input:
7 9 1 2 1 4 2 3 2 5 2 6 3 7 4 5 4 6 6 7 
output:
1 3 5 6 
*/
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<malloc.h>
using namespace std;

int v=0;
int e=0;
int edge[50][50]={0};
//int isWhite[50]={0};
//存储各点的着色情况
int used[50]={0};
//记录着色方案数
int count=0;


//判断当前作色点是否合法，k是递归层数，也是已经着色的节点索引
bool isVaild(int k)
{
    for (int i=1;i<k;i++)
    {
        //如果两点相同，并且周围点的着色相同，表示当前颜色选择不合法，结束判断
        if (edge[k][i] == 1&& used[k]==used[i])
            return false;
    }
    return true;
}

void backtrack(int k)
{
    //已经遍历完所有点数
    if(k>v)
    {
       count += 1;
       //cout<<"方法"<<count<<" :";
       //只打印第一种方案
       if (count == 1)
        {
            for (int i=1;i<=v;i++)
            {
                //输出白棋的的索引
                if(used[i]==1)
                {
                    cout<<i<<" ";
                }
            }
       }
       //cout<<endl;
       return;
    }
    else
    {
        for (int i=1;i<=2;i++)
        {
            used[k] = i;
            //当前颜色选择合法
            if (isVaild(k))
                backtrack(k+1);
            used[k] = 0;
        }
    }

}

int main()
{
    cin>>v>>e;
    int e1=0,e2=0;
    for (int i=1;i<=e;i++)
    {
        cin>>e1>>e2;
        //表示两点是连通的 ,无向图
        edge[e1][e2]= edge[e2][e1] = 1;
    }
    cout<<"图的邻接矩阵为"<<endl;
    for (int i=1;i<=e;i++)
    {
        for (int j = 1; j <= e; j++)
        {
            cout<<edge[i][j]<<" "; 
        }
        cout<<endl;
    }
    //从节点1开始递归
    cout<<"白色点编号为 ："<<endl;
    backtrack(1);
    cout<<endl;
}