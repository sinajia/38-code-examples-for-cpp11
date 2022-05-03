// 19friend友元改进.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class B;

template<typename T>
class A {
private:
    friend T; // 可以是类，也可以是基本类型，基本类型编译器自动忽略friend，用于泛型编程
    void func() {
        cout << typeid(T).name() << endl;
    }
};

class B {
public:
    void func(A<B> a) {
        a.func();
    }
};

int main()
{
    A<B> a;
    B b;
    b.func(a);

    //A<int> a1;

}
