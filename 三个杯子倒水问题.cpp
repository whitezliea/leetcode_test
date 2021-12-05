#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;
// 题型 ：BFS
/* 大      中  小
* 8L(FULL) 5L 3L
* --->how to get 4L water
* 起始状态(8,0,0)
* 终点状态(4,x,y),(x,4,y) 注4+x+y=8;
* 状态改变，六种
* 大 ---> 中  -- 1
* 大 ---> 小  -- 2
* 中 ---> 大  -- 3
* 中 ---> 小  -- 4
* 小 ---> 大  -- 5
* 小 ---> 中  -- 6
*/
#define X 8
#define Y 5
#define Z 3
struct Node
{
	int state[3];
	int step=0;
};
const int capsize[3] = { 8,5,3 };
int find_num = 9999;
int res = 0;
int vis[50][50][50] = { 0 };


#define Queue_MAXSIZE 1000
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

//核心代码，杯子source向destion倒水
void pour(Node *a,int source ,int destion)
{
	//a向b倒水
	int need = capsize[destion] - a->state[destion];
    //当前a的水足够b所需要时 ，a减去需要的水，b增加需要的水（即装满）
	if (need <= a->state[source])
	{
		a->state[destion] += need;
		a->state[source] -= need;
	}
	else // 当前a的水不够b所需要时，将a中所有的水倒向b，a杯子清空
	{
		a->state[destion] += a->state[source];
		a->state[source] = 0;
	}
}

int BFS(Node a)
{
	Queue q;
	Node initnode;
	initnode.state[0] = a.state[0];
	initnode.state[1] = a.state[1];
	initnode.state[2] = a.state[2];
	initnode.step = a.step;
	q.addQueue(initnode);
	//设置已经访问
	vis[initnode.state[0]][initnode.state[1]][initnode.state[2]] = 1;

	while (!q.isEmpty())
	{
		Node tempnode = q.getFront();
		q.delQueue();
        //剪枝操作
		for (int i = 0; i < 3; i++)
			if (tempnode.state[i] < 0||tempnode.state[i] > capsize[i])
				continue;
        //结束条件
		for (int i = 0; i < 3; i++)
			if (tempnode.state[i] == 4)
				return tempnode.step;
		//Node newNode;
        //遍历三个杯子互相倒水的所有情况
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
                //剪枝，去除不合理情况 ,source杯子水不为空，destion杯子不为满
				if (i != j && tempnode.state[i] != 0 && tempnode.state[j] < capsize[j])
				{

					Node newNode = tempnode;
					pour( &newNode,i, j); //深拷贝
					newNode.step = tempnode.step + 1;
                    //如果这种杯子状态没有出现过
					if (vis[newNode.state[0]][newNode.state[1]][newNode.state[2]] == 0)
					{
						cout << "[" << tempnode.state[0] << tempnode.state[1] << tempnode.state[2] << "] -> "
							<< "[" << newNode.state[0] << newNode.state[1] << newNode.state[2] << "] step:"<<newNode.step << endl;
                        //设置这种杯子状态出现过
						vis[newNode.state[0]][newNode.state[1]][newNode.state[2]] = 1;
						q.addQueue(newNode);
					}
				}
			}
		}
	}
	return -1;
}
int main()
{
	int x=8, y=0, z=0;
	//cin >> x>> y>> z;
	Node a;
	a.state[0] = x,a.state[1]=y,a.state[2]=z;
	a.step = 0;
	res = BFS(a);
	cout << res << endl;
	return 0;
}
/*
 刷题总结：
 1、首先是BFS与DFS的选择？
 有些时候BFS与DFS并不是都适用，要清楚DFS与BFS的使用范围
 DFS/回溯算法 ---> 适用于遍历所有情况，穷举起点状态到终点状态可能会出现的所有可能性，类似二叉树的前中后序遍历
 BFS   --->  适用于最短/最优路径的求解，常用于找出起点状态到终点状态的最短/最优路径，但是也可用于穷举遍历，类似二叉树的层次遍历
 //穷举遍历时都要设置结束调教，否则会死循环。
 数组描述状态比字符描述状态方便遍历
*/