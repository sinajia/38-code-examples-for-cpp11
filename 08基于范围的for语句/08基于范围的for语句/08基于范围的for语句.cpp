// 08基于范围的for语句.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>
using namespace std;

// 脚本语言都可以这么用，C++在不断进化

int main()
{
    int arr[] = { 0,1,2,3,4,5,6,7,8,9 };

    for (auto v : arr) {
        cout << v << endl;
    }

    string s = "abc";
    for (char& c : s) {
        ++c;
    }
    cout << s << endl;

    list<int> l = { 0,1,2,3,4,5,6,7,8,9 };
    for (auto& v : l) {
        ++v;
    }
    
    for (const auto &v : l) {
        cout << v << endl;
    }

    for (list<int>::iterator it = l.begin(); it != l.end(); ++it) {
        (*it)++;
    }

    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
        cout << *it << endl;
    }

}
