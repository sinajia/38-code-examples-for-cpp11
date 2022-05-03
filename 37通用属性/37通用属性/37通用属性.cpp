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

// 返回值不应该被丢弃
[[nodiscard]] int func2() {
	return 0;
}

int main() {
	func2(); // 编译器会发出相关warning
	abort();
}

