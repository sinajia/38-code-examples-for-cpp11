// 07右尖括号.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct item {
    T t_;
};

int main()
{
    // vs2008编译不过，必须多敲一个空格，小优化，本该如此
    vector<item<int>> v;
    std::cout << "Hello World!\n";
}
