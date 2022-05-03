// 14_Pragma操作符.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// https://docs.microsoft.com/zh-cn/cpp/preprocessor/pragma-directives-and-the-pragma-keyword?view=msvc-170

#pragma once
_Pragma("once")

#pragma pack(push, 1)
struct MyStruct1
{
    char c;
    int i;
};
#pragma pack(pop)

_Pragma("pack(push, 1)")
struct MyStruct2
{
    char c;
    int i;
};
_Pragma("pack(pop)")

#define PRAGPUSH(x) PRAGMA(pack(push, x))
#define PRAGMA(x) _Pragma(#x)
#define PRAGPOP _Pragma("pack(pop)")

PRAGPUSH(1)
struct MyStruct3
{
    char c;
    int i;
};
PRAGPOP

struct MyStruct4
{
    char c;
    int i;
};

#include <iostream>

using namespace std;

int main()
{
    cout << sizeof(MyStruct1) << endl;
    cout << sizeof(MyStruct2) << endl;
    cout << sizeof(MyStruct3) << endl;
    cout << sizeof(MyStruct4) << endl;
}
