// 27智能指针.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

using namespace std;

class A : public std::enable_shared_from_this<A> {
public:
    A() = default;
    ~A() {
        cout << "~A()" << endl;
    }
    void func(int i) {
        cout << "A::func(" << i << ")" << endl;
    }
};

int main()
{
    {
        std::unique_ptr<A> ptr = std::make_unique<A>(); // unique_ptr
        std::unique_ptr<A> ptr2 = std::move(ptr);
        ptr2->func(0);
    }

    cout<<endl;

    {
        std::shared_ptr<A> ptr = std::make_shared<A>(); // shared_ptr
        std::shared_ptr<A> ptr2 = ptr;
        ptr->func(0);
        ptr2->func(1);
    }

    cout << endl;

    {
        // 管理数组
        std::shared_ptr<char> tmpcbuf{ new char[4096], std::default_delete<char[]>() };
    }

    {
        A* ptmp = new A();
        {
            std::shared_ptr<A> ptr(ptmp);
            std::shared_ptr<A> ptr2 = ptmp->shared_from_this(); // 类从继承enable_shared_from_this
            cout << ptr2 << endl;
        }

        // std::shared_ptr<A> ptr2 = ptmp->shared_from_this(); // ptmp已经析构，不能再调用

    }

    cout << endl;

    {
        std::shared_ptr<A> ptr = std::make_shared<A>();
        std::weak_ptr<A> weakptr{ ptr }; // 弱指针
        {
            weakptr.lock()->func(1);
        }
        ptr.reset();
        cout << weakptr.lock().get() << endl;
    }

}
