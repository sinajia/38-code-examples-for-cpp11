// 10auto decltype关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

auto func(int i) {
    if (i > 0) {
        return i;
    }
    else {
        return 9;
    }
}

int main()
{
    // auto代替类型
    auto i = func(5);
    // 推到类型
    decltype(func(1)) i1;
    decltype(i) i2;
    i1 = 100;
    cout << i1 << endl;
}
