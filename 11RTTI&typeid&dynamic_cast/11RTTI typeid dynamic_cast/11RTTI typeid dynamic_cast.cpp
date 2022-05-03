// 11RTTI typeid dynamic_cast.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>

using namespace std;

class Base1 {
public:
    int i1_;
    virtual void func() {}
};

class  Base2 {
public:
    int i2_;
    virtual void func() {}
};

class Derived : public Base2, public Base1 {
public:
    int d_;
};

int main()
{
    {
        int a;
        assert(typeid(a).name() == typeid(int).name());
        // static_assert(typeid(a).name() == typeid(int).name(), "");
    }
    
    {
        Base1* pb1 = new Base1{};
        Derived* pd = static_cast<Derived*>(pb1);

        cout << pb1 << endl;
        cout << pd << endl;

        pd = dynamic_cast<Derived*>(pb1);

        cout << pd << endl;
    }

    {
        Derived* pbd = new Derived{};
        cout << pbd << endl;

        {
            Base1* pb1 = static_cast<Base1*>(pbd);
            cout << pb1 << endl;
        }

        {
            Base2* pb2 = dynamic_cast<Base2*>(pbd);
            cout << pb2 << endl;
        }

        {
            Base1* pb1 = static_cast<Base1*>(pbd);
            Base2* pb2 = dynamic_cast<Base2*>(pb1);
            // Base2* pb2 = static_cast<Base2*>(pb1);
            cout << pb2 << endl;
        }



    }

    


}
