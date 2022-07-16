#include<iostream>
#include<stdlib.h>
using namespace std;
#define MAXSIZE 50
char maze[50][50] = { '.' };
int height = 0, width = 0;
int sx = 0, sy = 0, ex = 0, ey = 0;
bool flag = false;
bool visited[50][50] = { false };
//int queue[500][50]={0};
/*
0 y------->9
x
|
|
9
*/
int dirl[4][2] =
{   //顺时针
    {0,-1}, //左0
    {-1,0}, //上1
    {0,1},  //右2
    {1,0},  //下3
};
int dirr[4][2]=
{   //逆时针
    {0,1},    //右0
    {-1,0},  //上1
    {0,-1},   //左2
    {1,0}    //下3
};
struct Node
{
    int x;
    int y;
    int step;
};

class Queue
{
private:
    struct Node data[MAXSIZE];
    int front ;
    int rear ;
    int size  ;
public:
    Queue()
    {
        rear = -1;
        front = -1;
        size = 0;
    }
    void add(Node n)
    {
        if(isFull())
        {
            cout<<"FULL!"<<endl;
            exit(-1);
        }
        rear++;
        rear = rear%MAXSIZE;
        size++;
        data[rear]= n;
    }
    Node del()
    {
        if (isEmpty())
        {
            cout<<"EMPTY"<<endl;
            exit(-1);
        }
        front++;
        front %= MAXSIZE;
        size--;
        return data[front];
    }
    Node getFront()
    {
        int index = front+1;
        return data[index];
    }
    int getSize()
    {
        return size;
    }
    bool isFull()
    {
        return size == MAXSIZE;
    }
    bool isEmpty()
    {
        return size == 0; 
    }
    ~Queue()
    {

    }
};





int my_abs(int a, int b)
{
    return a > b ? a - b : b - a;
}
void DFS(int x, int y, int step, int dirs,int dir[][2])
{
    //cout <<"step: " << step << endl;
    if (x == ex && y == ey)
    {
        flag = true;
        cout << step << " ";
        return;
    }
   // cout<<"pre dir:"<<dirs<<endl;
    if (dirs == 0)
        dirs = 4;
    if (!flag)
    {
        for (int i = dirs-1,j=0; j <= 3  ; j++)
        {   
            i=i%4;
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if (nx < 0 || ny < 0 || nx >= height || ny >= width)
                continue;
            if (!flag && !visited[nx][ny] && maze[nx][ny] != '#' )
            {
                // cout << "方向: " << i << ", ";
               // cout << nx << " " << ny << endl;
                DFS(nx, ny, step + 1, i,dir);
                
            }
            i++;
        }
    }
}

void BFS()
{   
    Queue q;
    Node n;
    n.x=sx,n.y=sy,n.step=0;
    q.add(n);
    visited[sx][sy]=true;
    while (q.getSize()!=0)
    {
        Node temp = q.getFront();
        q.del();
        if (temp.x==ex&&temp.y==ey)
        {
            cout<<temp.step+1<<endl;
            return ;
        }
        for (int i=0;i<4;i++)
        {
            int nx=temp.x+dirl[i][0];
            int ny=temp.y+dirl[i][1];
            if (nx<0||ny<0||nx>=height||ny>=width)
                continue;
            if (!visited[nx][ny]&&maze[nx][ny]!='#')
            {
                visited[nx][ny]=true;
                Node Next;
                Next.x = nx;
                Next.y=ny;
                Next.step=temp.step+1;
                q.add(Next);
            }
        }
    }
    
}

int main()
{
    int t=0;
    cin>>t;
    while (t--)
    {
        for(int i=0;i<50;i++)
            for (int j=0;j<50;j++)
                visited[i][j] = false;
    cin >> width >> height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cin >> maze[i][j];
            if (maze[i][j] == 'S')
                sx = i, sy = j;
            if (maze[i][j] == 'E')
                ex = i, ey = j;
        }
    }
    flag = false;
    //沿着墙壁左走的步数
    for (int i = 0; i < 4; i++)
        if (maze[sx + dirl[i][0]][sy + dirl[i][1]] == '.')
        {
            visited[sx][sy] = true;
            DFS(sx, sy, 1, i,dirl);
            //cout<<endl;
        }
    flag = false;
    //沿着墙壁右走的步数
    for (int i = 0; i < 4; i++)
        if (maze[sx + dirr[i][0]][sy + dirr[i][1]] == '.')
        {
            visited[sx][sy] = true;
            DFS(sx, sy, 1, i,dirr);
            //cout<<endl;
        }
    
    BFS();
    }
    
    return 0;
}
/*
2
8 8
########
#......#
#.####.#
#.####.#
#.####.#
#.####.#
#...#..#
#S#E####
9 5
#########
#.#.#.#.#
S.......E
#.#.#.#.#
#########
*/