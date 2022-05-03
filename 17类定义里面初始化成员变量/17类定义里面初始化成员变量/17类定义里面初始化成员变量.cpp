// 17类定义里面初始化成员变量.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
public:
    A() : i_(1) {
        i_ = 2;
    }
    int i_ = 0;
};

int main()
{
    A a;
    cout << a.i_ << endl;
}
