// 20外部模板.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "./extern_tmpl.h"

using namespace std;

extern template void gen<int>(int);

int main()
{
   gen(100);
}
