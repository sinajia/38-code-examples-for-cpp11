// 37通用属性.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>

using namespace std;

class __declspec(novtable) A {
public:
	virtual	void func() = 0;
};

// 函数不会返回
[[noreturn]] void throwAway() {
	throw "";
}

void func() {
	throwAway();
	cout << "不会执行到这里";
}

int main() {
	abort();
}
