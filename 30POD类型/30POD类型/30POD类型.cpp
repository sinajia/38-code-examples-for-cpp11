// 30POD类型.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class A {
  A() = default;
  int a_;
  int b_;
};

struct B {
  B() {}
  int b_;
};

class C {
 public:
  C() = default;
  C(int i) : c_(0) { i_ = i; }
  int i_;

 private:
  char c_;
};

int main() {
  std::cout << std::boolalpha;

#pragma region 平凡类型（trivial），可靠的复制
  {
    // 有默认构造函数
    std::cout << std::is_trivial<A>::value << '\n';
    std::cout << std::is_trivial<B>::value << '\n';
    std::cout << std::is_trivial<C>::value << '\n';
  }
#pragma endregion
  cout << endl;
#pragma region 标准布局类型，C语言安全的访问
  {
    // 成员变量访问权限一致
    std::cout << std::is_standard_layout<A>::value << '\n';
    std::cout << std::is_standard_layout<B>::value << '\n';
    std::cout << std::is_standard_layout<C>::value << '\n';
  }
#pragma endregion
  cout << endl;
#pragma region 简单旧数据类型，POD
  {
    std::cout << std::is_pod<A>::value << '\n';
    std::cout << std::is_pod<B>::value << '\n';
    std::cout << std::is_pod<C>::value << '\n';
  }
#pragma endregion
}
