// 27智能指针.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

using namespace std;

class A {
public:
    A() = default;
    void func(int i) {
        cout << "A::func(" << i << ")" << endl;
    }
};

int main()
{
    {
        std::unique_ptr<A> ptr = std::make_unique<A>();
        std::unique_ptr<A> ptr2 = std::move(ptr);
        ptr2->func(0);
    }



    {
        std::shared_ptr<A> ptr = std::make_shared<A>();
        std::shared_ptr<A> ptr2 = ptr;
        ptr->func(0);
        ptr2->func(1);
    }

    {
        std::shared_ptr<A> ptr = std::make_shared<A>();
        std::weak_ptr<A> weakptr{ ptr };
        {
            weakptr.lock()->func(1);
        }
        ptr.reset();
        cout << weakptr.lock().get() << endl;
    }

}
