/*
问题描述：现在有七种不同类型的积木，分布在一个长度为width，高度为hight的图中，
积木类型有：      |
type 1  ---->  --0--  特性：可以与上下左右四个方向的积木进行连接
                 |

                 |
type 2  ---->    0    特性：可以与上下两个方向的积木进行连接
                 |

type 3  ---->  --0--  特性：可以与左右两个方向的积木进行连接

type 4  ---->  --0    特性：可以与左和下两个方向的积木进行连接
                 |

type 5  ---->    0--  特性：可以与右和下两个方向的积木进行连接
                 |

                 |
type 6  ---->    0--  特性：可以与右和上两个方向的积木进行连接

                 |
type 7  ---->  --0    特性：可以与左和上两个方向的积木进行连接

在了解积木的类型之后，在一个给定的 width * hight 的图中，给定起始点(i,j)与可走步数，
问从起始点的积木开始，向积木连接方向寻找，每寻找一个新的连接的积木，可走步数-1，
在可走步数走完之后，最多能找到几根积木（算上起始点）。

需要输入的参数：
input:
5 6           //6->width 5->height
(2,1)  3      //(2,1)起始点坐标，3-->可走步数
   0  -----> 5
   y
0x 0 4 0 5 3 4   //0代表此处没有积木 ，1~7代表七种不同的积木
   0 2 3 2 0 2
   3 1 3 1 3 7
   0 6 3 5 0 0
4  0 0 0 0 0 0
数组总结，注意数组横向递增方向与竖向递增方向
output:
10
*/
#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;
//int map[50][100] = { 0 };
int width = 0, height = 0;
int find_num = 0;
struct Node
{
    int x = 0, y = 0;
    int  endstep = 0, type = 0;
}maze[50][100];
int vis[50][100] = { 0 };
int dir[4][2] = {
    {0,1}, //向上
    {0,-1}, //向下
    {-1,0}, //向左
    {1,0} //向右
};
int vaild[7][4] = {
    {1,-1,-1,1},  //上下左右 --type 1
    {1,-1,0,0},   //上下   --type 2
    {0,0,-1,1},  //左右    --type 3
    {1,0,-1,0},  //下左  --type 4
    {1,0,0,1} ,  //下右  --type 5
    {0,-1,0,1},  //上右    --type 6
    {0,-1,-1,0}   //上左   --type 7
};
//上下对x操作，左右对y操作

//C++实现队列
#define Queue_MAXSIZE 20
class Queue
{
private:
    struct Node data[Queue_MAXSIZE]; //存储数据
    int front;//队首指针
    int rear; //队尾指针
    int size; //队列大小
public:
    Queue();
    void addQueue(Node a);
    Node delQueue();
    Node getFront();
    bool isFull();
    bool isEmpty();
    int getSize();
};

Queue::Queue()
{
    front = -1;
    rear = -1;
    size = 0;
}

void Queue::addQueue(Node a)
{
    if (isFull())
    {
        exit(-1);
    }
    rear++;
    rear %= Queue_MAXSIZE;
    size++;
    data[rear] = a;
}
Node Queue::delQueue()
{
    if (isEmpty())
    {
        exit(-1);
    }
    front++;
    front %= Queue_MAXSIZE;
    size--;
    return data[front];
}

Node Queue::getFront()
{
    int index = front + 1;
    return data[index];
}

bool Queue::isFull()
{
    return size == Queue_MAXSIZE;
}
bool Queue::isEmpty()
{
    return size == 0;
}
int Queue::getSize()
{
    return size;
}


bool my_abs(int x, int y)
{
    return x == y ? true : false;
}
//核心代码
/*
分类讨论 横向是否相连，纵向是否相连
*/
bool isVaild(int sx, int sy, int nx, int ny)
{
    //cout << sx << " " << sy << "->" << nx << " " << ny << ",";
    //cout << maze[sx][sy].type - 1 << " " << maze[nx][ny].type - 1 << endl;
    if (!my_abs(sx, nx))
    {
        for (int i1 = 0; i1 < 2; i1++)
            for (int i2 = 0; i2 < 2; i2++)
                if (sx + vaild[maze[sx][sy].type - 1][i1] == nx && nx + vaild[maze[nx][ny].type - 1][i2] == sx)
                    return true;
    }
    if (!my_abs(sy, ny))
    {
        for (int j1 = 2; j1 < 4; j1++)
            for (int j2 = 2; j2 < 4; j2++)
                if (sy + vaild[maze[sx][sy].type - 1][j1] == ny && ny + vaild[maze[nx][ny].type - 1][j2] == sy)
                    return true;
    }
    return false;
}

//判断当前节点是否合法
bool in(int x, int y)
{
    if (x < 0 || y < 0 || x >= height || y >= width||maze[x][y].type == 0)
        return false;
    return true;
}

void BFS(int sx,int sy)
{
    Queue q;
    maze[sx][sy].x = sx;
    maze[sx][sy].y = sy;
    q.addQueue(maze[sx][sy]);
    vis[sx][sy] = 1;
    while (!q.isEmpty())
    {
        Node temp = q.getFront();
        q.delQueue();
        for (int i = 0; i < 4; i++)
        {
            int nx = temp.x + dir[i][0];
            int ny = temp.y + dir[i][1];
            //未越界
            if (in(nx, ny))
            {
                //积木之间可以连接同时未被访问
                if (isVaild(temp.x, temp.y, nx, ny) && vis[nx][ny] == 0)
                {   
                    //停止这个方向遍历的条件
                    if (temp.endstep == 0)
                        continue;
                    maze[nx][ny].x = nx;
                    maze[nx][ny].y = ny;
                    maze[nx][ny].endstep = temp.endstep - 1;
                    find_num++;
                    //设置已访问
                    vis[nx][ny] = 1;
                    cout << temp.x << " " << temp.y << "->" << nx << " " << ny << " ";
                    cout << " ed: " << maze[nx][ny].endstep << " type: " << maze[nx][ny].type << endl;
                    q.addQueue(maze[nx][ny]);
                }
            }
        }
    }
    return;
}

int main()
{
    int sx = 0, sy = 0, endstep = 0;
    cin >> height >> width >> sx >> sy >> endstep;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cin >> maze[i][j].type;


    maze[sx][sy].endstep = endstep;
    cout << "help" << endl;
    BFS(sx, sy);
    cout << find_num +1<< endl;//加1 是因为要加上起始点
    
}

/*
case 1:
input :
5 6 2 1 3
0 4 0 5 3 4
0 2 3 2 0 2
3 1 3 1 3 7
0 6 3 5 0 0
0 0 0 0 0 0
output :10

case 2:
input :
6 7 4 2 4
0 0 0 0 0 0 0
0 3 2 0 0 0 0
0 0 5 7 0 0 0
0 4 2 5 2 0 0
3 1 1 2 0 2 0
0 2 6 1 3 3 7
output: 14

*/