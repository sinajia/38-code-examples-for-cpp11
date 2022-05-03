// 05委托构造函数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

class A {
public:
    // 在构造函数里面调用另外一个构造函数
    A() : A(0, 0, 0) {};
    A(int hour, int min, int sec) : hour_(hour), min_(min), sec_(sec) {}

    std::ostream& operator<<(std::ostream& os) {
        os << hour_ << min_ << sec_;
        return os;
    }

    int hour_;
    int min_;
    int sec_;
};

int main()
{
    A a;
    a << std::cout << std::endl;
}
