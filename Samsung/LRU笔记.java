#include<iostream>
using namespace std;
/*
// 缓存容量为2
LRUCache Cache = new LRUCache(2);
// cache 理解成一个队列
// 队头 1<---->2 队尾
// 最近使用的排在队尾，久未使用的排在队头
// 圆括号表示键值对（key, value）

cache.put(1,1);
// cache = [(1,1)]

cache.put(2,2)
// cache = [(1,1), (2,2)]

cache.get(1)
// cache = [(2,2), (1,1)]

尾插法
*/

//-----------------------------------------------------------
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

//------------------------------------------------------------------------
// 在LRU的主方法 get 与 put上增添一层抽象API，避免直接操作map和cache

// 将某个key提升为最近使用的
private void makeRecently(int key)
{
    Node x = map.get(key);
    // 先从链表中删除这个节点
    cache.remove(x);
    // 重新插入到队尾
    cache.addLast(x);
}

// 添加最近使用的元素
private void addRecently(int key,int val)
{
    Node x = new Node(key ,val);
    // 链表尾部就是最近使用的元素
    cache.addLast(x);
    // 别忘了在map中添加key的映射
    map.put(key, x);
}

// 删除某一个Key
private void deleteKey(int key)
{
    Node x = map.get(key);
    // 从链表中删除
    cache.remove(x);
    // 从map中删除
    map.remove(key);
}

// 删除久未使用的元素
private void removeLeastRecently()
{
    // 链表的头部第一个元素就是最久未使用的
    Node deleteNode = cache.removeFirst();
    // 同时别忘了从 map 中删除它的Key
    int deleteKey = deleteKey.key;
    map.remove(deleteKey);
}

//------------------------------------------------------

public int get(int key)
{
    if (!map.containsKey(key))
        return - 1;
    // 将该数据提升为最近使用
    makeRecently(key);
    return map.get(key).val;  //key <--> Node(key, val)
}

public int put(int key, int val)
{
    if (map.containsKey(key))
    {
        // 删除旧的数据
        deleteKey(key);
        // 新插入的数据为最近使用的数据
        addRecently(key, val);
        return ;
    }

    if ( cap == cache.size() )
    {
        // 删除最久未使用的元素
        removeLeastRecently();
    }

    // 添加最近使用的元素
    addRecently(key, val);
}