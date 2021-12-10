/*
2是火，1是树，0是空地，火能往4个方向烧树，遇空地停下，
最多能砍n=2棵树，怎么砍，最后被烧掉的树最少。
*/

#include<iostream>
#include<malloc.h>
#include<stdlib.h>
using namespace std;
int width=0,height=0;
#define MaxSize 500
//被烧的树的坐标
int canBrun[50][50]={0};
//被烧的树的树木数
int CanBurnNum=0;
//剩余最少的树木数
int minTree = 0;
//剩余最多的树木数
int maxTree = 0;
int nums=0;
struct Map
{
    //原始地图
    int map[50][50]={0};
    //火烧之后的剩余的树木数
    int count=0;
    //需要砍的树的数量
    int killTree=0;
};

//地图对比
bool compare_Map(Map m1,Map m2)
{
    for (int i=0;i<height;i++)
        for(int j=0;j<width;j++)
                if(m1.map[i][j]!=m2.map[i][j])
                    return false;
    return true;
}

class Queue
{
private:
    struct Map data[MaxSize];
    int rear = -1;
    int front = -1;
    int size = 0;
public:
    void add(Map m)
    {
        if (isFull())
        {
            cout<<"FULL"<<endl;
            exit(-1);
        }
        rear = rear+1;
        rear %= MaxSize;
        size++;
        data[rear] = m;
    }
    Map del()
    {
        if (isEmpty())
            exit(-1);
        front = front + 1;
        front %= MaxSize;
        size--;
        return data[front] ;
    }
    int getSize()
    {
        return size;
    }
    Map getFront()
    {
        int index = front+1;
        return data[index];
    }
    bool isFull()
    {
        //cout<<size<<endl;
        return size == MaxSize;
    }
    bool isEmpty()
    {
        return size==0;
    }
    //环形队列查找元素
    bool find_Map(Map m)
    {
        if (rear > front)
        {
            for (int i=front+1;i<=rear;i++)
                if (compare_Map(m,data[i]))
                    return true;
            return false;
        }
        else if (rear <= front)
        {
        for (int i=0;i<=size-1;i++)
            if (compare_Map(m,data[i]))
                return true;
        return false;
        }
    }
};

//获取地图中树的数量
int getCount(Map m)
{
    for (int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            if (m.map[i][j]==1)
                    m.count++;
    return m.count;
}

//模拟火向四周进行燃烧蔓延的情况
void dfs(Map &m,int i,int j)
{
    if(i>=height||j>=width||i<0||j<0)
        return ;
    if (m.map[i][j]==0)
        return ;
    //当一棵树不砍时的初始情况
    if (m.map[i][j]!=2&&m.map[i][j]!=0&&m.killTree==0)
    {   
        canBrun[i][j] = 1;
        CanBurnNum++;
    }
    //火把树烧成空地
    m.map[i][j] = 0;
    dfs(m,i-1,j);
    dfs(m,i+1,j);
    dfs(m,i,j-1);
    dfs(m,i,j+1);
}
//可选函数，直观展示地图，方便观察
void displayMap(Map m)
{
    for (int i=0;i<height;i++)
       { 
           for (int j=0;j<width;j++)
                cout<<m.map[i][j]<< " ";
            cout<<endl;
       }
    cout<<endl;
}
//看完树的最优情况的地图
Map bestMap;

//核心函数，使用BFS的层次遍历来遍历砍的树为0为1为2时的情况
int bfs(Map m)
{
    Queue q;
    q.add(m);
    while (!q.isEmpty())
    {
            Map temp = q.getFront();
            Map backup = q.getFront();
            q.del();
            //结束条件
            if (temp.killTree > 2)
            {
                if (maxTree<=minTree)
                    return -1;
                else
                    return maxTree;
            }

            //进行火烧树操作
            for (int i=0;i<height;i++)
                for (int j=0;j<width;j++)
                    if (temp.map[i][j]==2)
                        dfs(temp,i,j);

            if (temp.killTree == 0)
            {
                minTree = getCount(temp);
                cout<<"一颗树不砍情况下剩余树的数量: "<<minTree<<endl;
                cout<<"一颗树不砍情况下被火烧的树的数量"<<CanBurnNum<<endl;
            }
            else
            { 
                if (getCount(temp)>maxTree)
                {
                    bestMap = backup;
                    maxTree = getCount(temp);
                }
            }

            for (int i1=0;i1<height;i1++)
                for (int i2=0;i2<width;i2++)
                {   //砍掉可以燃烧的树同时防止重复砍一棵树
                    if (canBrun[i1][i2]==1&&backup.map[i1][i2]!=0)
                        {   
                            Map back = backup;
                            back.map[i1][i2] = 0;
                            if (!q.find_Map(back))
                            {
                                back.killTree++;
                                q.add(back);
                            }
                        }
                }
    }
    
    return -1;

}

int main()
{
    Map m1;
    cin>>height>>width;
    for (int i=0;i<height;i++)
        for (int j=0;j<width;j++)
            cin>>m1.map[i][j];
    cout<<endl;
    int t = bfs(m1);
    cout<<"最多可剩余树木: "<<t<<endl;
    cout<<endl;
    cout<<"一颗树不砍情况下被火烧的树的数量的地图"<<endl;
    for (int i=0;i<height;i++)
       { 
           for (int j=0;j<width;j++)
                cout<<canBrun[i][j]<< " ";
            cout<<endl;
       }

    cout<<"BestMap:"<<endl;
    displayMap(bestMap);
    return 0;
}

/*
case 1:
8 8 
1 1 0 0 0 0 1 1
1 0 1 1 1 0 0 0
1 1 0 1 0 0 0 1
0 0 1 2 1 0 1 0
0 0 1 2 2 1 0 1
0 1 1 1 0 0 0 1
0 1 0 0 0 1 1 1
1 0 0 1 1 0 0 1

case 2:
5 7
1 1 0 1 1 0 1 
1 0 1 1 1 1 0 
1 1 0 1 0 0 0 
0 0 1 2 1 0 1 
1 0 1 1 0 1 0 

case 3:
8 8 
1 1 0 0 0 0 1 1
1 0 1 1 0 0 0 0
1 1 0 1 0 0 0 0
0 0 1 2 0 0 0 2
0 0 1 2 0 0 0 1
0 1 1 0 0 0 0 1
0 1 0 0 0 0 0 1
1 1 0 1 1 0 0 1

*/