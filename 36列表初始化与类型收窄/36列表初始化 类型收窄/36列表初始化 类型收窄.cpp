// 36列表初始化 类型收窄.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
public:
	A(int i) : i_(i) {

	}

	int i_;

};

int main()
{
	int i1 = 0.5;
	int i2(0.6);
	int i3 = { 1 };
	int i4{ 2 };
	A a = { 0 };

	short si = 10;
	__int64 i64{ si };

	cout << i1 << endl;
	cout << i2 << endl;

	// 防止隐式类型转换
	// int i3{ 0.9 };
	// int i4 = { 0.9 };
	// A a = { 0.0 };


}
