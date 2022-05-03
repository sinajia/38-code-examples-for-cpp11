// 21右值引用 移动语义.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

using namespace std;

class A {
public:
    A() {
        i_ = 101;
    }

    ~A() {
        delete ptr_;
    }

    A(const A& a);

    A(A&& a) noexcept {
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = a.ptr_;
        a.ptr_ = nullptr;
    };

    A& operator=(const A& a) {

    }

    A& operator=(A&& a) {

    }

    int i_ = 100;
    int* ptr_ = nullptr;
};

A::A(const A& a) {
    i_ = a.i_;
    if (a.ptr_) {
        ptr_ = new int{ *a.ptr_ };
    }
    
}

A func() {
    A a;
    return a;
}

string func1() {
    string s = "abc";
    // 请勿使用std::move返回局部变量
    // return std::move(s);
    return s;
}

int main()
{
    {
        // 语法作用：提升性能
        A a = func();
        //cout << a.i_ << endl;

        string r = func1();

    }

    {
        string s1 = "abc...";
        string s2 = std::move(s1);
    }

    {
        A a;
        a.ptr_ = new int{ 100 };
        cout << a.ptr_ << "  " << *a.ptr_ << endl;
        A a1{ a };

        cout << a.ptr_ << endl;

        cout << a1.ptr_ << "  " << *a1.ptr_ << endl;

    }
}
