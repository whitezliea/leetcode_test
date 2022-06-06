#include<iostream>
using namespace std;
/*
// 缓存容量为2
LRUCache Cache = new LRUCache(2);
// cache 理解成一个队列
// 队头 1<---->2 队尾
// 最近使用的排在队头，久未使用的排在队尾
// 圆括号表示键值对（key, value）

cache.put(1,1);
// cache = [(1,1)]

cache.put(2,2)
// cache = [(2,2), (1,1)]

cache.get(1)
// cache = [(1,1), (2,2)]

*/
class Node
{
    public int key, val;
    public Node next, prev;
    public Node(int k ,int v)
    {
        this.key = k;
        this.val = v;
    }
};

class DoubleList
{
    private Node head, tail;
    private int size;

    //
    public DoubleList()
    {
        // 初始化双向链表
        head = new Node(0,0);
        tail = new Node(0,0);
        head.next = tail;
        tial.prev = head;
        size = 0;
    }

    // 在链表尾部添加节点X，时间O(1)
    public void addLast(Node x)
    {
        x.prev = tail.prev;
        x.next = tail;
        tail.prev.next = x;
        tail.prev = x;
        size++;
    }

    // 删除链表中的x节点（x一定存在）
    // 由于是双链表且给的是目标Node节点，时间O(1)
    public void remove(Node x)
    {
        x.prev.next = x.next;
        x.next.prev = x.prev;
    }

    // 删除链表中的第一个节点，并返回这个节点，时间O（1）
    public  Node  removeFirst()
    {
        if (head.next == tail)
            return  null;
        Node first = head.next;
        remove(first);
        return first;
    }

    //返回链表长度 
    public int size()
    {
        return size;
    }

};

class LRUCache
{
    // key -> Node(key, val)
    private HashMap<Integer, Node> map;
    // Node(k1, v1) <-> Node(k2, v2)
    private DoubleList cache;
    // 最大容量
    private int cap;

    public LRUCache(int capacity)
    {
        this.cap = capacity;
        map = new HashMap<>();
        cache = new DoubleList();
    }
}

