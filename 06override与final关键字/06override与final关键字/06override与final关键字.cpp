// 06override与final关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class Base {
public:
    virtual void func() = 0;
    virtual void gen() = 0;
};

class Derived : public Base {
public:
    // 看到override，就知道是重载
    virtual void func() override {
        cout << "Derived::func()" << endl;
    }
    virtual void gen() final {
        cout << "Derived::gen()" << endl;
    }
};

class A : public Derived {
public:
    // 表示重载的最终版本
    virtual void func() final {
        cout << "A::func" << endl;
    }
};

int main()
{
    A* a = new A;
    Base* ptr = a;
    ptr->func();
    ptr->gen();
}
