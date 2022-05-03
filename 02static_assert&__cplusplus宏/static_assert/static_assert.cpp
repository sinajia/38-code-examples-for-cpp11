// static_assert.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

template<typename T>
class A {
public:
    A() {
        static_assert(sizeof(T) == 4, "sizeof(T) != 4"); // 编译期决议，编译器检查
    }
};

int main()
{
    static_assert(__cplusplus >= 199711LL, "");
    A<int> a;
    std::cout << "Hello World!\n";
}
