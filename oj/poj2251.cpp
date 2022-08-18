#include <iostream>
#include <stdlib.h>
using namespace std;
char Dun[30][30][30] = {'.'};
bool vis[30][30][30] = {false};
#define MAXSIZE 100
//高 长 宽
int r = 0, l = 0, c = 0;
int sx = 0, sy = 0, sz = 0;
struct Node
{
    int x = 0;
    int y = 0;
    int z = 0;
    int step = 0;
};

class Queue
{
private:
    struct Node data[MAXSIZE];
    int rear;
    int front;
    int size;

public:
    Queue()
    {
        rear = -1;
        front = -1;
        size = 0;
    }
    void add(Node a)
    {
        if (isFull())
            exit(-1);
        rear++;
        rear %= MAXSIZE;
        size++;
        data[rear] = a;
    }
    Node del()
    {
        if (isEmpty())
            exit(-1);
        front++;
        front %= MAXSIZE;
        size--;
        return data[front];
    }
    Node getFront()
    {
        int index = front + 1;
        return data[index];
    }
    int getSize()
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    bool isFull()
    {
        return size == MAXSIZE;
    }
    ~Queue();
};

void BFS()
{
}

int main()
{
    while (1)
    {
        cin >> r >> l >> c;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < l; j++)
            {
                for (int k = 0; i < c; k++)
                {
                    cin >> Dun[i][j][k];
                    if (Dun[i][j][k] == 'S')
                    {
                        sz = i;
                        sx = j;
                        sy = k;
                    }
                }
            }
        }
    }
}