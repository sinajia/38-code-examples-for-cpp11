// 12强枚举类型.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
public:
    enum  {
        WX,
        QQ
    };
};

class B {
public:
    enum class Type : int 
    {
        WX,
        QQ
    };
};

int main()
{
    cout << A::WX << endl;

    cout << (__int64)B::Type::WX << endl;

    cout << sizeof(B::Type::WX) << endl;

    long i = A::WX;

    // i = B::Type::WX; // 报错
    i = (int)B::Type::WX;
}
