#include <map>
#include <string.h>
#include <iostream>
using namespace std;
typedef pair<string, int> PAIR;

// less实现
/*
template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<pair<const Key, T>>>
class map;

template <class T>
struct less : binary_function<T, T, bool>
{
    bool operator()(const T &x, const T &y) const
    {
        return x < y;
    }
};
*/
ostream &operator<<(ostream &out, const PAIR &p)
{
    return out << p.first << "\t" << p.second;
}

struct CmpByKeyLength //姓名按照短到长排序
{
    bool operator()(const string &s1, const string &s2)
    {
        return s1.length() < s2.length();
    }
};

int main()
{
    map<string, int, CmpByKeyLength> ma;
    ma["LiMin"] = 90;
    ma["ZiLinMi"] = 79;
    // ma["BoB"] = 92;
    ma.insert({"BoB", 92});
    ma.insert(make_pair("Bing", 99));
    ma.insert(make_pair("Albert", 86));
    for (map<string, int>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
    {
        cout << *iter << endl;
    }
    cout << "hello world!" << endl;
    system("pause");
    return 0;
}