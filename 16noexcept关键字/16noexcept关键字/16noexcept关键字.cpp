// 16noexcept关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

void func() noexcept { // 表示函数不抛出异常，与noexcept(true)意思一样
    throw exception(); // 编译通过，在程序执行过程中，程序会调用terminate以确保遵守不在运行时抛出异常的承诺
}

int main() {
    try {
        func();
    }
    catch (int e) {
        cout << "catch" << endl;
    }

    cout << noexcept(func()) << endl; // 如果func不抛出异常，则为true，否则为false

}

// 析构函数应该声明为noexcept
