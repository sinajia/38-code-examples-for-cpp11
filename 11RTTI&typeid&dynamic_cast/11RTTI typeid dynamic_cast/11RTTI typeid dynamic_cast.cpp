// 11RTTI typeid dynamic_cast.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>

using namespace std;

class Base1 {
public:
    int i1_;
    virtual void func1() {}
};

class  Base2 {
public:
    int i2_;
    virtual void func2() = 0;
};

class Derived : public Base2, public Base1 {
public:
    int d_;
    
    virtual void func2() override {}

};

int main()
{
    {
        int a;
        assert(typeid(a).name() == typeid(int).name()); // typeid 运行时求值
        // static_assert(typeid(a).name() == typeid(int).name(), "");  // 编译不过
    }
    // dynamic_cast 作用于多态类型
    {
        Base1* pb1 = new Base1{};
        Derived* pd = static_cast<Derived*>(pb1); // 编译期决议，不会报错

        cout << pb1 << endl;
        cout << pd << endl;

        pd = dynamic_cast<Derived*>(pb1); // 没有继承关系，返回0

        cout << pd << endl;
        
        Base2* pb2 = nullptr;
        
        pb2 = dynamic_cast<Base2*>(pb1); // 实际没有继承关系，返回0
        
        {
            // pb2 = static_cast<Base2*>(pb1); // 编译报错
        }

        cout << pb2 << endl;

        cout << endl;


    }

    {
        Derived* pd = new Derived();
        Base1* pb1 = pd;
        Base2 * pb2 = pd;

        cout << pd << "  " << pb1 << "  " << pb2 << endl;

        {
            pb2 = dynamic_cast<Base2*>(pb1);

            {
            // pb2 = static_cast<Base2*>(pb1); // 编译报错
            }

            cout << pb2 << endl;
        }

        {
            pb1 = dynamic_cast<Base1*>(pb2);
            cout << pb1 << endl;
        }

    }


}
