// 03long long关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <climits>

int main()
{
    std::cout << sizeof(long long) << std::endl;
    std::cout << sizeof(__int64) << std::endl;
    std::cout << sizeof(void *) << std::endl;

    std::cout << LLONG_MIN << std::endl;
    std::cout << LLONG_MAX << std::endl;
    std::cout << ULLONG_MAX << std::endl;
}
