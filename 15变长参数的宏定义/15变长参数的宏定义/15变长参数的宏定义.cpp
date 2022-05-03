// 15变长参数的宏定义.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

#define LOG(...) { \
    fprintf(stderr,"%s:line %d:\t", "15变长参数的宏定义.cpp", __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
  }
int main()
{
    LOG("%s\n", "hello world");
}
