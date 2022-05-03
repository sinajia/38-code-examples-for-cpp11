// 32继承构造函数 using用法.cpp : 此文件包含 "main"
// 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
 public:
  A(int i) {}

 protected:
  void func() {
    cout << this << endl;
    using INT = int;
    // typedef int INT;
    INT i = 100;
  }
};

class A1 {
 public:
  int i_;
};

class B1 : public A {
 public:
  B1(int i) : A(i) {}
};

class B2 : public A1, public A {
 public:
  using A::A;     // 如果B2的构造函数就是为了给A传值
  using A::func;  // 实际调用仍然是A::func，编译器不会写一个新函数
};

int main() {
  B2 b2(100);
  cout << &b2 << endl;
  b2.func();
  cout << static_cast<A*>(&b2) << endl;
}
