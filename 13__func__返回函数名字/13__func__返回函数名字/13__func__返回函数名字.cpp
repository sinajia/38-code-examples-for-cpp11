// 13__func__返回函数名字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
public:
    A() {
        cout << __FILE__ << endl;
        cout << __LINE__ << endl;
        cout << __func__ << endl;
        cout << __TIME__ << endl;
    }
};

int main()
{
    A a;
}
