// 29default delete.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

class A {
public:
    A() = default;
    A(int) {}
    // A(const A&) = delete;
};

int main()
{
    A* ptr = new A();
    A a{ *ptr };
}
