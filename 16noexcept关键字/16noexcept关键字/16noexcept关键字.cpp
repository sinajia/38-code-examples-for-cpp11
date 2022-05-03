// 16noexcept关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

void func() noexcept {
    // throw 5;
}

int main() {
    try {
        func();
    }
    catch (int e) {
        cout << "catch" << endl;
    }

    cout << noexcept(func()) << endl;

}

// 析构函数应该声明为noexcept
