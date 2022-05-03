// 18非静态成员的sizeof.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
public:
    int i_;
};

int main()
{
    cout << sizeof(A::i_) << endl;
}
