/*
一个二维数组表示地图，0表示空地，1表示树，2表示火，
火可以往上下左右四个方向蔓延一直烧树，遇到空地或边界会阻断，
砍树可以把1变成0，最多可以砍2颗树，请问火灾之后最多可以剩下多少棵树？
用dfs搜索能被火烧的树的位置，用bfs搜索砍哪些树后留下的树最多。
example：
8 8
1 1 0 0 0 0 1 1
1 0 1 1 1 0 0 0
1 1 0 1 0 0 0 0
0 0 1 2 0 0 0 2
0 0 1 2 2 0 0 1
0 1 1 0 0 0 0 1
0 1 0 0 0 1 1 1
1 1 1 1 0 0 0 1
output :
最多可剩余树木: 19
---------------
砍完树之后的地图为
BestMap:
1 1 0 0 0 0 1 1
1 0 1 1 1 0 0 0
1 1 0 1 0 0 0 0
0 0 1 2 0 0 0 2
0 0 0 2 2 0 0 0
0 1 1 0 0 0 0 1
0 1 0 0 0 1 1 1
1 1 1 1 0 0 0 1
*/

#include <iostream>
#include <malloc.h>
#include <stdlib.h>
using namespace std;
int width = 0, height = 0;
#define MaxSize 200
//被烧的树的坐标
int canBrun[50][2] = {0};
//被烧的树的树木数
int CanBurnNum = 0;
//记录火的坐标
int fireMap[50][2] = {0};
//记录火的个数
int fireNum = 0;
//剩余最少的树木数
int minTree = 0;
//剩余最多的树木数
int maxTree = 0;
struct Map
{
    //原始地图
    int map[50][50] = {0};
    //火烧之后的剩余的树木数
    int count = 0;
    //需要砍的树的数量
    int killTree = 0;
};

//地图对比
bool compare_Map(Map m1, Map m2)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (m1.map[i][j] != m2.map[i][j])
                return false;
    return true;
}

//实现队列功能
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
            cout << "FULL" << endl;
            exit(-1);
        }
        rear = rear + 1;
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
        return data[front];
    }
    int getSize()
    {
        return size;
    }
    Map getFront()
    {
        int index = front + 1;
        return data[index];
    }
    bool isFull()
    {
        // cout<<size<<endl;
        return size == MaxSize;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    //环形队列查找元素
    bool find_Map(Map m)
    {
        if (rear > front)
        {
            for (int i = front + 1; i <= rear; i++)
                if (compare_Map(m, data[i]))
                    return true;
            return false;
        }
        else if (rear <= front)
        {
            for (int i = 0; i <= size - 1; i++)
                if (compare_Map(m, data[i]))
                    return true;
            return false;
        }
    }
};

//获取地图中树的数量
int getCount(Map m)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (m.map[i][j] == 1)
                m.count++;
    return m.count;
}
//获取地图中着火的位置坐标
void getfire(Map m)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            if (m.map[i][j] == 2)
            {
                fireMap[fireNum][0] = i;
                fireMap[fireNum][1] = j;
                fireNum++;
            }
        }
}

//模拟火向四周进行燃烧蔓延的情况
void dfs(Map &m, int i, int j)
{
    if (i >= height || j >= width || i < 0 || j < 0)
        return;
    if (m.map[i][j] == 0)
        return;
    //当一棵树不砍时的初始情况,存储被火烧的树的坐标
    if (m.map[i][j] == 1 && m.killTree == 0)
    {
        canBrun[CanBurnNum][0] = i;
        canBrun[CanBurnNum][1] = j;
        CanBurnNum++;
    }
    //火把树烧成空地
    m.map[i][j] = 0;
    dfs(m, i - 1, j);
    dfs(m, i + 1, j);
    dfs(m, i, j - 1);
    dfs(m, i, j + 1);
}
//可选函数，直观展示地图，方便观察
void displayMap(Map m)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << m.map[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
//砍完树的最优情况的地图
Map bestMap;

//核心函数，使用BFS的层次遍历来遍历砍的树为0为1为2时的情况
int bfs(Map m)
{
    Queue q;
    q.add(m);
    while (!q.isEmpty())
    {

        Map temp = q.getFront();
        Map fatherMap = q.getFront();
        q.del();

        //进行火烧树操作
        for (int i = 0; i < fireNum; i++)
        {
            int x = fireMap[i][0], y = fireMap[i][1];
            dfs(temp, x, y);
        }
        //获取火烧树之后剩余树木的数量
        if (temp.killTree == 0)
        {
            //当一棵树也不砍时，就是火灾后剩余树数量最少情况
            minTree = getCount(temp);
            // cout << "一颗树不砍情况下剩余树的数量: " << minTree << endl;
            // cout << "一颗树不砍情况下被火烧的树的数量" << CanBurnNum << endl;
        }
        else
        {
            if (getCount(temp) > maxTree)
            {
                bestMap = fatherMap;
                maxTree = getCount(temp);
            }
        }

        //结束条件，砍2棵树的情况全都遍历完。
        if (q.getSize() == 0 && temp.killTree == 2)
        {
            //如果砍1棵树或者砍2颗树的情况比不砍树的情况差时，就返回-1，否则返回最好情况。
            if (maxTree <= minTree)
                return -1;
            else
                return maxTree;
        }

        for (int i1 = 0; i1 < CanBurnNum; i1++)
        { //砍掉可以燃烧的树同时防止重复砍同一棵树
            int x = canBrun[i1][0], y = canBrun[i1][1];
            if (fatherMap.map[x][y] != 0)
            {
                Map sonMap = fatherMap;
                sonMap.map[x][y] = 0;
                sonMap.killTree++;
                if (!q.find_Map(sonMap) && sonMap.killTree <= 2)
                {
                    q.add(sonMap);
                }
            }
        }
    }
    return -1;
}

int main()
{
    Map m1;
    cin >> height >> width;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cin >> m1.map[i][j];
    cout << endl;
    getfire(m1);
    int t = bfs(m1);
    cout << "最多可剩余树木: " << t << endl;
    cout << endl;
    cout << "BestMap:" << endl;
    displayMap(bestMap);
    return 0;
}

/*
case 1:
8 8
1 1 0 0 0 0 1 1
1 0 1 1 1 0 0 0
1 1 0 1 0 0 0 0
0 0 1 2 0 0 0 2
0 0 1 2 2 0 0 1
0 1 1 0 0 0 0 1
0 1 0 0 0 1 1 1
1 1 1 1 0 0 0 1

case 2:
5 7
1 1 0 1 0 0 1
1 0 1 1 0 0 0
1 0 0 1 1 0 0
0 1 1 2 1 0 1
0 1 0 0 0 1 0

case 3:
8 8
1 1 0 1 1 0 1 1
1 0 1 1 1 1 0 0
1 1 0 1 0 0 0 0
0 0 1 2 0 0 0 2
0 0 1 2 0 0 0 1
0 0 1 0 0 0 0 1
0 0 1 0 0 0 0 1
0 1 1 1 0 0 0 1

*/

/*
刷题总结：
1、 题目思路
 首先将问题分为两个小问题，第一个是火向四周进行燃烧，这符合DFS的特性
1 1 0 1 0 0 1
1 0 1 1 0 0 0
1 0 0 | 1 0 0
0 1 <-2-> 0 1
0 1 0 | 0 1 0
 第二个是问题是砍树问题，最多砍二棵树，即可以砍0棵树，砍一棵树，砍两颗树，
 由于砍n+1棵树时地图状态跟砍n棵树时地图状态有关，这符合BFS的特性。
    0           0  --------->砍0棵树的情况
    |          / \
    |         /   \
    |        / ... \
    1       1       1  ------> 砍1棵树的情况
    |      / \     / \
    |     /...\   /...\
    2    2     2 2     2   -------->砍2棵树的情况
 BFS是层次遍历二叉树的同时也在构建二叉树，也就说，我们必须在遍历完构建高度为1的树之后，
 通过父节点的情况遍历构建高度为2的二叉树子节点。

2、代码反思
（1）如何存储可以被火烧的树的位置信息，以及存储火的位置信息。
 简单粗暴的方法就是每次都遍历一次地图来进行砍树与火烧的操作，
 优化的操作是用两个二维数组来分别存储可以被烧的树的信息，以及存储火的位置信息。
 这样就不需要每次都遍历地图了。
（2）结束条件的位置
 判断什么时候BFS函数结束，当时就直接设置killTree=3，即出队的队首元素砍到第三棵树是就停止，
 结果就是队列容量直接FULL（假设一共在十颗树里砍3棵，就是10*9*8=720），后面就进行了优化
 结束条件改为队列为空的同时出队的元素被砍树为2，即将所有砍0棵树，砍1棵树，砍2根树的情况全都遍历完之后，
 在这些情况选择剩余树木数最多的情况。同时入队条件处也需修改，砍3棵树的情况就不入队了（假设一共在十颗树里砍2棵，就是10*9=90），
 此时队列就不容易满了。
*/