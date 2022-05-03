// 24lambda表达式.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>

using namespace std;

class A {
public:
    A() {
        cout << "A()" << endl;
    };
    A(const A& a) {
        cout << "A(const A&)" << endl;
    }
    A(A&& a) noexcept {
        cout << "A(A&&) noexcept" << endl;
    }
    A& operator=(const A& a) {
        cout << "operator=(const A& a)" << endl;
        return *this;
    }

    A& operator=(A&& a) noexcept {
        cout << "operator=(A&& a) noexcept" << endl;
        return *this;
    }

    int i_ = 100;

};

auto func() {
    A a;
    auto f = (
        [=]() { // = 表示复制一份a，调用的是拷贝构造函数
            cout << "a.i_=" << a.i_ << endl;
        }
    );

    return f;
}

int main()
{
    {
        A a;
        auto f = (
            [&]() { // 以引用的方式使用a
                cout << "a.i_=" << a.i_ << endl;
            }
        );
        f();
        
        cout << endl;
    }

    {
        std::function<void(void)> f = func();
        f();
        cout << endl;
    }

    {
        A a;
        auto lam = [=](int i) mutable -> int {  // 使用mutable表示可以改变变量a的值
            a.i_ = 101; // 修改a的值
            cout << "a.i_=" << a.i_ << endl;
            cout << "i=" << i << endl;
            return 103;
        };
        auto r = lam(102);
        cout << "r=" << r << endl;
    }

}
