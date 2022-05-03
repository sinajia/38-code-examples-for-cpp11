// 28nullptr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

void func(int) {
    cout << "func(int)" << endl;
}

void func(char*) {
    cout << "func(char*)" << endl;
}

int main()
{
    func(NULL);
    func((char*)NULL);
    func(nullptr);
    cout << (nullptr == 0) << endl;
    return 0;
}
